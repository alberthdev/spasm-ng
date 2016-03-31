#!/usr/bin/env python3
#
# spasm-ng test runner

import logging
import re
import shlex
import subprocess
import sys
import tempfile

class NotImplementedType:
    def __getitem__(cls, x):
        return NotImplemented

def have_typing_module() -> bool:
    (major, minor, _, _, _) = sys.version_info
    return (major == 3 and minor >= 5) or major > 3

if have_typing_module():
    from typing import Tuple, ByteString, Iterable, Sequence
else:
    Tuple = ByteString = Iterable = Sequence = NotImplementedType()

# In case you need more visiblity into what's going on.
#logging.basicConfig(level=logging.DEBUG)

class Checker(object):
    def __init__(self, line_tail):
        raise NotImplementedError

    def __call__(self, binary: ByteString, console: Sequence[str]) -> Tuple[ByteString, Sequence[str]]:
        raise NotImplementedError


class EmitsBytes(Checker):
    def __init__(self, s):
        s = filter_whitespace(s)
        if len(s) % 2 != 0:
            raise ValueError("CHECK values must specify exactly two digits per byte")

        expected = bytearray()
        for i in range(0, len(s), 2):
            expected.append(int(s[i:i+2], 16))
        self.bytes = expected

    def __call__(self, binary, output):
        length = len(self.bytes)
        actual = binary[:length]
        logging.debug('EmitsBytes receives %s, expects %s',
                format_bytes(actual), format_bytes(self.bytes))
        assert actual == self.bytes, "Expected {}, found {}".format(self.bytes, actual)
        return (binary[:length], output)


class SkipBytes(Checker):
    def __init__(self, s):
        self.length = int(filter_whitespace(s), 16)

    def __call__(self, binary, output):
        logging.debug('SkipBytes receives %u, needs %u', len(binary), self.length)
        assert len(binary) >= self.length, "Expected at least {} bytes, got {}".format(self.length, len(binary))
        return (binary[:self.length], output)


class EmitsWarning(Checker): pass
class EmitsError(Checker): pass


CHECK_TYPES = {
    '': EmitsBytes,
    '-SKIP': SkipBytes,
    '-WARN': EmitsWarning,
    '-ERR': EmitsError
}


def find_check_directives(sources: Iterable[str]) -> Sequence[Checker]:
    """
    Scan a test source file for check directives and return the set of
    constraints, among the following:

    * CHECK aa bb cc: assert that the output binary contains the bytes aa, bb
      and cc in exactly that order at the location counter, where byte values
      are specified in hex.
    * CHECK-SKIP nnnn: advance the checker location by nnnn bytes (in hex),
      ignoring the bytes in that region.
    * CHECK-WARN nnn: assert that warning number nnn is raised.
    * CHECK-ERR nnn: assert that error number nnn is raised.
    """
    checkers = []
    for line in sources:
        m = re.match(r'^\s*;\s*CHECK(?P<ty>[^:]*):', line)
        if m:
            ty = m.group('ty')
            if ty not in CHECK_TYPES:
                raise ValueError("Check type '{}' is not recognized".format(ty))
            checkers.append(CHECK_TYPES[ty](line[m.end():]))
    return checkers


def find_assembler_args(sources: Iterable[str]) -> str:
    args = []
    for line in sources:
        m = re.match(r'^\s*;\s*RUN-ARGS:', line)
        if m:
            args.append(line[m.end():].strip())
    return ' '.join(args)


def run_assembler(assembler: str, infile: str, opts: str) -> Tuple[int, ByteString, Sequence[str]]:
    """
    Run the assembler over the given file, with the given command line
    arguments.

    Returns the assembler's return code, the binary emitted from the
    assembler and the lines emitted to the console.
    """
    with tempfile.NamedTemporaryFile('rb') as outfile:
        proc = subprocess.Popen(
                [assembler] + shlex.split(opts) + [infile, outfile.name],
                stdin=subprocess.DEVNULL, stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT, universal_newlines=True)
        pout, perr = proc.communicate()
        binary = outfile.read()
    return (proc.returncode, binary, pout.split('\n'))


def filter_whitespace(s: str) -> str:
    return ''.join(filter(lambda c: not c.isspace(), s))


def format_bytes(b) -> str:
    return '[{}]'.format(', '.join('{:02x}'.format(x) for x in b))


def main(assembler, files: Iterable[str]) -> int:
    passes = failures = errors = 0

    for filename in files:
        print('{} '.format(filename), end='')
        with open(filename, 'r') as infile:
            lines = list(map(lambda s: s.strip(), infile))
        checks = find_check_directives(lines)
        logging.debug('Found {} check(s) in source file'.format(len(checks)))
        args = find_assembler_args(lines)
        logging.debug('File declares assembler args \'{}\''.format(args))

        (status, binary, console) = run_assembler(assembler, filename, args)
        if status != 0:
            print('ERROR exited with code {}'.format(status))
            print('Output:\n{}\n'.format(console))
            continue

        orig_len = len(binary)
        offset = 0
        for (i, check) in enumerate(checks):
            try:
                logging.info('Running checker {} at offset {}'.format(i, offset))
                (binary, console) = check(binary, console)
                passes += 1
                offset = orig_len - len(binary)
                print('PASS')
            except AssertionError as e:
                failures += 1
                print("FAIL at binary offset {}: {}".format(offset, e))
                print("Output:\n{}\n".format(console))

    print("\nCompleted with {} passes, {} failures and {} errors"
            .format(passes, failures, errors))
    return failures + errors


if __name__ == '__main__':
    if len(sys.argv) > 2:
        [assembler_binary, *files] = sys.argv[1:]
        if main(assembler_binary, files) > 0:
            sys.exit(1)
    else:
        print("Usage: {} assembler-exe asm-file...".format(sys.argv[0]), file=sys.stderr)

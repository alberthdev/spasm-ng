spasm-ng
========
SPASM-ng is a z80 assembler with extra features to support development
for TI calculators. 

Requirements
------------
On Windows, you will need the following to build SPASM-ng:

  * Visual Studio with C++ support
    Visual Studio 2012 is recommended, but it may be possible to
    downgrade. See http://stackoverflow.com/a/16196505 for more
    info.

On Linux, Mac OS X, and other *nix, you will need the following to
build SPASM-ng:

  * C/C++ Compiler (GCC, Clang, etc.)
  * GMP Library (found at https://gmplib.org/)
  * OpenSSL Library (found at https://www.openssl.org/)

Note that if you are using Linux, your distribution will likely have
pre-built packages (and development packages) available to install.
You should use these first before attempting to install the above
libraries yourself.

Suggested packages for Ubuntu/Debian:

  * build-essential
  * libssl-dev
  * zlib1g-dev
  * libgmp-dev
  * checkinstall (optional, only if you want to build Debian packages - .deb files)

Building
--------
On Windows, simply build with the included Visual Studio project file.

On Linux, Mac OS X, and other *nix, simply build by running:

    make
    
    # Optional: install SPASM-ng (you may need sudo/su/root):
    make install

For Debian systems, you can run the following to create a Debian
package:

    make debian

Documentation
-------------
The program accepts standard Z80 assembly.

SPASM command line help shown below:

    SPASM Z80 Assembler by Spencer Putt and Don Straney
    
    
    spasm [options] <input file> <output file>
    
    Options:
    -T = Generate code listing
    -C = Code counter mode
    -L = Symbol table mode
    -S = Stats mode
    -O = Don't write to output file
    -I [directory] = Add include directory
    -A = Labels are cAse-sensitive
    -D<name>[=value] = Create a define 'name' [with 'value']
    -N = Don't use colors for messages
    -V <Expression> = Pipe expression directly into assembly

Issues/Bugs
-----------
Report issues/bugs to the issue tracker, found here:

https://github.com/alberthdev/spasm-ng/issues

Copyright/License
-----------------
SPASM-ng was originally from the SPASM project, and was forked to fix a
few bugs. It was originally written by Spencer Putt and Don Straney.

License:

    SPASM-ng - a z80 assembler with extra features to support dev for TI calcs!
    Copyright (C) 2015 Spencer Putt, Don Straney, Chris Shappell, and James Montelongo
    Copyright (C) 2015 Albert Huang (fixes to SPASM)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

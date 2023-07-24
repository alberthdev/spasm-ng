ISWIN = $(or $(findstring Windows,$(OS)),$(findstring mingw,$(CROSS_COMPILE)))
CC = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
STRIP = $(CROSS_COMPILE)strip
CXXFLAGS+= -Wall -DUSE_REUSABLES $(if $(ISWIN),,-DUNIXVER) -DUSE_BUILTIN_FCREATE
LDFLAGS+= -lm

DESTDIR ?= /usr/local

ifdef FORCE_NO_GIT
	FORCE_NO_GIT = 1
endif
export FORCE_NO_GIT

VERSION=$$(./version.sh | head -n 1)
VERSION_DPKG=$$(./version.sh dpkg)
GITREV=$$(./version.sh | grep "Git")

ifdef NO_APPSIGN
	CXXFLAGS += -DNO_APPSIGN
else
	LDFLAGS += -lgmp -lcrypto
endif

export CXXFLAGS
export LDFLAGS

# Suffix Rules
.SUFFIXES: .cpp

.cpp.o:
		$(CC) $(CXXFLAGS) -c $<

.cpp:
		$(CC) $(CXXFLAGS) $< -o $@

SRC = main.cpp opcodes.cpp pass_one.cpp pass_two.cpp utils.cpp export.cpp preop.cpp directive.cpp console.cpp \
expand_buf.cpp hash.cpp list.cpp parser.cpp storage.cpp errors.cpp bitmap.cpp modp_ascii.cpp opcodes_ez80.cpp
OBJ = $(addsuffix .o, $(basename $(SRC)))
OBJ_FILES = $(addsuffix .o, $(basename $(notdir $(SRC))))
EXE = $(if $(ISWIN),spasm.exe,spasm)

$(EXE): version $(OBJ) Makefile
	$(CC) -o $@ $(OBJ_FILES) $(LDFLAGS)
	$(STRIP) $@

debug: CXXFLAGS+= -g
debug: STRIP= :
debug: $(EXE)

debugp: CXXFLAGS+= -g -DDEBUG_PRINT
debugp: STRIP= :
debugp: $(EXE)

prep-special-build:
		$(MAKE) clean
		touch prep-special-build

opt: CXXFLAGS+= -O3
opt: prep-special-build $(OBJ)
		touch opt

static: LDFLAGS+= -static
static: $(EXE)
		touch static

opt-static: opt static

tar: opt-static
		tar czvf spasm-ng_$(VERSION)_binary.tar.gz $(EXE) README.md LICENSE inc/

# This is a fake Debian package builder - it uses checkinstall
# to make this work.
debian: opt $(EXE)
		echo "SPASM-ng is a z80 assembler with extra features to support development for TI calculators." > description-pak
		checkinstall --requires "zlib1g, libssl1.0.0, libgmp10" \
			--pkgname="spasm-ng" --pkgversion="$(VERSION_DPKG)" --pkgrelease="1" \
			--maintainer="alberthdev@users.noreply.github.com" \
			--backup=no --deldoc=yes --deldesc=yes --delspec=yes \
			--install=no --default $(CHECKINSTALL_OPTS)
		rm -f description-pak

install:
		cp $(EXE) $(DESTDIR)/bin/$(EXE)

check: $(EXE)
	$(PYTHON) tests/test-runner.py ./$(EXE)

coverage: CXXFLAGS+=-g -O0 --coverage
coverage: LDFLAGS+=-g -O0 --coverage
coverage: clean check

clean:
		rm -f $(OBJ) $(EXE) description-pak spasm-ng*.deb spasm-ng*.tar.gz
		rm -f opt static prep-special-build
		rm -f *.gcno *.gcda *.gcov version.h

version:
		@./version.sh set
		@echo "The current spasm-ng version is: $(VERSION)"
		@test -n "$(GITREV)" && echo "$(GITREV)" || exit 0

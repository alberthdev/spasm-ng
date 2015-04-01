CC = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
CXXFLAGS+= -DUSE_REUSABLES -DUNIXVER -DUSE_BUILTIN_FCREATE
LDFLAGS+= -lc -lm

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

spasm: $(OBJ) Makefile
		$(CC) -o spasm $(OBJ_FILES) $(LDFLAGS)

prep-special-build:
		$(MAKE) clean
		touch prep-special-build

opt: CXXFLAGS+= -O3
opt: prep-special-build $(OBJ)
		touch opt

static: LDFLAGS+= -static
static: spasm
		touch static

opt-static: opt static

tar: opt-static
		tar czvf spasm-ng_$(VERSION)_binary.tar.gz spasm README.md LICENSE inc/

# This is a fake Debian package builder - it uses checkinstall
# to make this work.	 
debian: opt spasm
		echo "SPASM-ng is a z80 assembler with extra features to support development for TI calculators." > description-pak
		checkinstall --requires "zlib1g, libssl1.0.0, libgmp10" \
			--pkgname="spasm-ng" --pkgversion="$(VERSION_DPKG)" --pkgrelease="1" \
			--maintainer="alberthdev@users.noreply.github.com" \
			--backup=no --deldoc=yes --deldesc=yes --delspec=yes \
			--install=no --default
		rm -f description-pak

install:
		cp spasm /usr/bin/spasm

clean:
		rm -f $(OBJ) spasm description-pak spasm-ng*.deb spasm-ng*.tar.gz
		rm -f opt static prep-special-build

version:
		@./version.sh set
		@echo "The current spasm-ng version is: $(VERSION)"
		@test -n "$(GITREV)" && echo "$(GITREV)" || exit 0

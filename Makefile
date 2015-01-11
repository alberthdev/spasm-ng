CC = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
CXXFLAGS+=  -I.  -DUSE_REUSABLES -DUSE_GMP -DUNIXVER -DUSE_BUILTIN_FCREATE
LDFLAGS+= -lc -lgmp -lm -lcrypto
	 
# Suffix Rules
.SUFFIXES: .cpp
	 
.cpp.o:
		$(CC) $(CXXFLAGS) -c $<
	 
.cpp:
		$(CC) $(CXXFLAGS) $< -o $@

SRC = main.cpp opcodes.cpp pass_one.cpp pass_two.cpp utils.cpp export.cpp preop.cpp directive.cpp console.cpp \
expand_buf.cpp hash.cpp list.cpp parser.cpp storage.cpp errors.cpp bitmap.cpp modp_ascii.cpp
OBJ = $(addsuffix .o, $(basename $(SRC)))
OBJ_FILES = $(addsuffix .o, $(basename $(notdir $(SRC))))
	 
spasm: $(OBJ) Makefile
		$(CC) -o spasm $(OBJ_FILES) $(LDFLAGS)

# This is a fake Debian package builder - it uses checkinstall
# to make this work.	 
debian: spasm
		echo "SPASM-ng is a z80 assembler with extra features to support development for TI calculators." > description-pak
		checkinstall --requires "zlib1g, libssl1.0.0, libgmp10" \
			--pkgname="spasm-ng" --pkgversion="1.0.0" --pkgrelease="1" \
			--maintainer="alberthdev@users.noreply.github.com" --nodoc \
			--backup=no --deldoc=yes --deldesc=yes --delspec=yes \
			--install=no --default
		rm -f description-pak

install:
		cp spasm /usr/bin/spasm

clean:
		rm -f $(OBJ) spasm description-pak spasm-ng*.deb


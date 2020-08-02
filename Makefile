# Minesweeper2
# Górka Mateusz
# Template of Makefile V2.0.0
#

# Configuration --------------------------------------------
PROG_NAME=Minesweeper2.exe
FLAGS=-Iinc -Wall -pedantic -std=c++0x
FILES_LIST= \
	obj/main.o
	# obj/_1_.o \
	# obj/_2_.o \
	# obj/_3_.o \
	# obj/_4_.o \

# Commends: --------------------------------------------------
# Build and start app
__start__: build
	./${PROG_NAME}

# Build app
build: mkobj COMPILE_COMP CONSOLIDATION

# Rebuild app
rebuild: clean build

# Build debug able version
debug: clean mkobj COMPILE_COMP DEGUB_
	gdb ./${PROG_NAME}

# Clean .o files
clean: rmobj
	rm -f ${PROG_NAME}

# Generate documentation
doxygen:
	cd dox; doxygen Doxyfile 2> /dev/null; cd ..;\
	start dox/html/index.html;\

# Remove temporary failes, generated documentation, minfy Doxyfile
MINIMAL:
	rm -fr obj dox/html; \
	rm ${PROG_NAME} doc/linecounter.* dox/index.html; \
	rmcomments dox/Doxyfile &\

# Subcomments: -------------------------------------------------
rmobj:
	rm -f obj/*

COMPILE_COMP: ${FILES_LIST}

CONSOLIDATION:
	g++ ${FLAGS} -o ${PROG_NAME} ${FILES_LIST}

DEGUB_:
	g++ -g ${FLAGS} -o ${PROG_NAME} ${FILES_LIST}

mkobj:
	mkdir -p obj

# Components: ---------------------------------------------------
obj/main.o: src/main.cpp
	g++ -c ${FLAGS} -o obj/main.o src/main.cpp

# obj/_1_.o: src/_1_.cpp inc/_1_.hpp
# 	g++ -c ${FLAGS} -o obj/_1_.o src/_1_.cpp

# obj/_2_.o: src/_2_.cpp inc/_2_.hpp
# 	g++ -c ${FLAGS} -o obj/_2_.o src/_2_.cpp

# obj/_3_.o: src/_3_.cpp inc/_3_.hpp
# 	g++ -c ${FLAGS} -o obj/_3_.o src/_3_.cpp

# obj/_4_.o: src/_4_.cpp inc/_4_.hpp
# 	g++ -c ${FLAGS} -o obj/_4_.o src/_4_.cpp

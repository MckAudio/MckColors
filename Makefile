CXX=g++
CFLAGS=-std=c++20
SRCDIR=./src/
SRCS=${SRCDIR}/main.cpp ${SRCDIR}/MyWindow.cpp
RELFLAGS=${CFLAGS} -O3 -DNDEBUG
DEBFLAGS=${CFLAGS} -O0 -DDEBUG -ggdb3
default: release

release: mkbin
	${CXX} ${RELFLAGS} ${SRCS} -o ./bin/mck-colors `pkg-config gtkmm-4.0 --cflags --libs`

debug: mkbin
	${CXX} ${DEBFLAGS} ${SRCS} -o ./bin/mck-colors `pkg-config gtkmm-4.0 --cflags --libs`

mkbin:
	mkdir -p bin | true
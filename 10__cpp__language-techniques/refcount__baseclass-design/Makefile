# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = main.cpp rcbaseobject.cpp someclass.cpp
HEADERS = rcptr.hpp rcbaseobject.hpp someclass.hpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

refcount.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: refcount.exe

clean:
	${RM} $(OBJECTS) refcount.exe *~ core

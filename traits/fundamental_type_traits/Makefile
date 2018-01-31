# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = fundamentaltraits.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

fundamentaltraits.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: fundamentaltraits.exe

clean:
	${RM} $(OBJECTS) fundamentaltraits.exe *~ core



# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatorstreams.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatorstreams.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatorstreams.exe

clean:
	${RM} $(OBJECTS) operatorstreams.exe operatorstreams.exe.stackdump *~ core



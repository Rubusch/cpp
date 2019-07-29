# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = convert.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

convert.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: convert.exe

clean:
	${RM} $(OBJECTS) convert.exe *~ core



# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  mixin.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

mixin.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: mixin.exe

clean:
	${RM} $(OBJECTS) mixin.exe *~ core



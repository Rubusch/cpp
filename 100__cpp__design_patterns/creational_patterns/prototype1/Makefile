# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  prototype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

prototype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: prototype.exe

clean:
	${RM} $(OBJECTS) prototype.exe *~ core



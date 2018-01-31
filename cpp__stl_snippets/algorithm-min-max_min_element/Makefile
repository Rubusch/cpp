# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = minelement.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

minelement.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: minelement.exe

clean:
	${RM} $(OBJECTS) minelement.exe *~ core



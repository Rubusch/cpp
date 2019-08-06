# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = moveconstructor.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

moveconstructor.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: moveconstructor.exe

clean:
	${RM} $(OBJECTS) moveconstructor.exe *~ core



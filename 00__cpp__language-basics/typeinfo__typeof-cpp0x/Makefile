# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = typeof.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typeof.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typeof.exe

clean:
	${RM} $(OBJECTS) typeof.exe *~ core



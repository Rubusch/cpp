# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = helloworld.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

helloworld.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: helloworld.exe

clean:
	${RM} $(OBJECTS) helloworld.exe *~ core



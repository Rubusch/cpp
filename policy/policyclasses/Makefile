# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  policyclasses.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

policyclasses.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: policyclasses.exe

clean:
	${RM} $(OBJECTS) policyclasses.exe *~ core



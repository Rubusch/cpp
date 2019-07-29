# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  observer.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

observer.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: observer.exe

clean:
	${RM} $(OBJECTS) observer.exe *~ core



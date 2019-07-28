# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = searchn.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

searchn.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: searchn.exe

clean:
	${RM} $(OBJECTS) searchn.exe *~ core



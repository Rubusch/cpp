# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = search.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

search.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: search.exe

clean:
	${RM} $(OBJECTS) search.exe *~ core



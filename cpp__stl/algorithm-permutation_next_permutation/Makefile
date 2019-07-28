# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = nextpermutation.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

nextpermutation.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: nextpermutation.exe

clean:
	${RM} $(OBJECTS) nextpermutation.exe *~ core



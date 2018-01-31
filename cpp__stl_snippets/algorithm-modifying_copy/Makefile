# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = copy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

copy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: copy.exe

clean:
	${RM} $(OBJECTS) copy.exe *~ core



# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = remove.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

remove.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: remove.exe

clean:
	${RM} $(OBJECTS) remove.exe *~ core



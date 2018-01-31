# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = typeinfo.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typeinfo.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typeinfo.exe

clean:
	${RM} $(OBJECTS) typeinfo.exe *~ core



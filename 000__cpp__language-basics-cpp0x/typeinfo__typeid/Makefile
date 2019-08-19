# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = typeinfotypeid.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typeinfotypeid.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typeinfotypeid.exe

clean:
	${RM} $(OBJECTS) typeinfotypeid.exe *~ core



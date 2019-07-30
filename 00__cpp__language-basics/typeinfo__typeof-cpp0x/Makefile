# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = typeinfotypeof.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typeinfotypeof.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typeinfotypeof.exe

clean:
	${RM} $(OBJECTS) typeinfotypeof.exe *~ core



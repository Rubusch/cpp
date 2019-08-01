# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = stackheapneverclass.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

stackheapneverclass.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: stackheapneverclass.exe

clean:
	${RM} $(OBJECTS) stackheapneverclass.exe *~ core



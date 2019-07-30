# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatornewanddeletefreelist.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatornewanddeletefreelist.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatornewanddeletefreelist.exe

clean:
	${RM} $(OBJECTS) operatornewanddeletefreelist.exe *~ core



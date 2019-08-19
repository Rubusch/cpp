# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatornewanddelete.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall 
RM = rm -f 

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatornewanddelete.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatornewanddelete.exe

clean:
	${RM} $(OBJECTS) operatornewanddelete.exe *~ core



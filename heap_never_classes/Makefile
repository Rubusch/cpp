# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = heapnever.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

heapnever.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: heapnever.exe

clean: 
	${RM} $(OBJECTS) heapnever.exe *~ core



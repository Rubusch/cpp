# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = heaponly.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

heaponly.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: heaponly.exe

clean: 
	${RM} $(OBJECTS) heaponly.exe *~ core



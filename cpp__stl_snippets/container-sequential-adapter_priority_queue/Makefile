# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = priorityqueueusage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

priorityqueueusage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: priorityqueueusage.exe

clean: 
	${RM} $(OBJECTS) priorityqueueusage.exe *~ core



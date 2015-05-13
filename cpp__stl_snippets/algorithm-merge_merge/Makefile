# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = merge.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

merge.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: merge.exe

clean: 
	${RM} $(OBJECTS) merge.exe *~ core



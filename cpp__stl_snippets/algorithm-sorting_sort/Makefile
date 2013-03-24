# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = sort.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

sort.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: sort.exe

clean: 
	${RM} $(OBJECTS) sort.exe *~ core



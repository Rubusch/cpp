# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = abstractclass.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

abstractclass.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: abstractclass.exe

clean: 
	${RM} $(OBJECTS) abstractclass.exe *~ core



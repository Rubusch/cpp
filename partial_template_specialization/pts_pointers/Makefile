# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = pts_pointers.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

pts_pointers.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pts_pointers.exe

clean: 
	${RM} $(OBJECTS) pts_pointers.exe *~ core



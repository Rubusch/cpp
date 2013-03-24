# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = pts.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

pts.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pts.exe

clean: 
	${RM} $(OBJECTS) pts.exe *~ core



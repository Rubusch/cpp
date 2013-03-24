# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = pts_polymorphism.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

pts_polymorphism.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pts_polymorphism.exe

clean: 
	${RM} $(OBJECTS) pts_polymorphism.exe *~ core



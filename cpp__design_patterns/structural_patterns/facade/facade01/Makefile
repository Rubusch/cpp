# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = facade.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

facade.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: facade.exe

clean: 
	${RM} $(OBJECTS) facade.exe *~ core



# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = templates.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

templates.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: templates.exe

clean: 
	${RM} $(OBJECTS) templates.exe *~ core



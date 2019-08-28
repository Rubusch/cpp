# Makefile (simple)
#
# @author Lothar Rubusch
#
# use -O, -O1, -O2 for optimization


SOURCE = binderfunctorbinder.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

binderfunctorbinder.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: binderfunctorbinder.exe

clean:
	${RM} $(OBJECTS) binderfunctorbinder.exe *~ core



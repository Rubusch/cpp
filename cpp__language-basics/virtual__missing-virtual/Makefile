# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = missingvirtual.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

missingvirtual.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: missingvirtual.exe

clean:
	${RM} $(OBJECTS) missingvirtual.exe *~ core



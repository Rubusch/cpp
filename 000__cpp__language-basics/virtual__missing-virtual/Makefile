# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = virtualmissingvirtual.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

virtualmissingvirtual.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: virtualmissingvirtual.exe

clean:
	${RM} $(OBJECTS) virtualmissingvirtual.exe *~ core



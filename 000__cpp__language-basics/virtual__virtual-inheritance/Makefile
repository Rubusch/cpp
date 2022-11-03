# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = virtualvirtualinheritance.cpp
OBJECTS = ${SOURCE:.cpp=.o}
TARGET = ${SOURCE:.cpp=.elf}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

${TARGET}: ${OBJECTS}
	${CC} -o $@ ${OBJECTS}

all: ${TARGET}

clean:
	${RM} $(OBJECTS) ${TARGET} *~



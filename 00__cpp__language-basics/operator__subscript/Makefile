# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatorsubscript.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatorsubscript.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatorsubscript.exe

clean:
	${RM} $(OBJECTS) operatorsubscript.exe operatorsubscript.exe.stackdump *~ core



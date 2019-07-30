# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatornewanddeletememorypool.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatornewanddeletememorypool.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatornewanddeletememorypool.exe

clean:
	${RM} $(OBJECTS) operatornewanddeletememorypool.exe *~ core



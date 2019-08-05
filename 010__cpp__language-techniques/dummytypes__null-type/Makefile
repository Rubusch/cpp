# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = dummytypesnulltype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

dummytypesnulltype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: dummytypesnulltype.exe

clean:
	${RM} $(OBJECTS) dummytypesnulltype.exe *~ core



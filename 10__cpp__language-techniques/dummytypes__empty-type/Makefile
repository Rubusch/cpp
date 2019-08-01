# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = dummytypesemptytype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g 
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

dummytypesemptytype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: dummytypesemptytype.exe

clean:
	${RM} $(OBJECTS) dummytypesemptytype.exe *~ core



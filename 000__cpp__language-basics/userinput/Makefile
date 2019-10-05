# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = userinput.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

userinput.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: userinput.exe

clean:
	${RM} $(OBJECTS) userinput.exe *~ core



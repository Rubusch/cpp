# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = copy_constructor.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

copy_constructor.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: copy_constructor.exe

clean:
	${RM} $(OBJECTS) copy_constructor.exe *~ core



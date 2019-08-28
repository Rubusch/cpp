# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = typeinfotypeinfowrapper.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

typeinfotypeinfowrapper.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: typeinfotypeinfowrapper.exe

clean:
	${RM} $(OBJECTS) typeinfotypeinfowrapper.exe *~ core



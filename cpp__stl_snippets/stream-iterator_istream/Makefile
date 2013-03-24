# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = istreamiterator.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

istreamiterator.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: istreamiterator.exe

clean: 
	${RM} $(OBJECTS) istreamiterator.exe *~ core



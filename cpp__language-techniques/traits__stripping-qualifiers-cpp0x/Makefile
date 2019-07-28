# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = strippingtraits.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

strippingtraits.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: strippingtraits.exe

clean:
	${RM} $(OBJECTS) strippingtraits.exe *~ core



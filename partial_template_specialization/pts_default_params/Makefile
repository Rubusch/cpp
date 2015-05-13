# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = pts_defaultparams.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

pts_defaultparams.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pts_defaultparams.exe

clean: 
	${RM} $(OBJECTS) pts_defaultparams.exe *~ core



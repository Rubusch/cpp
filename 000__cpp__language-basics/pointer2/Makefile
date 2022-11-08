SOURCE	= pointer2.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -funsigned-char
RM		= rm -f
MV		= mv -f
CP		= cp -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

pointer2.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS}

all: pointer2.exe

clean:
	-${RM} pointer2.exe *.o

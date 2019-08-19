# Makefile for C++ Class
SOURCE	= templatetemplateintemplateclass.cpp
HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -funsigned-char
RM		= rm -f
MV		= mv -f
CP		= cp -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

templatetemplateintemplateclass.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: templatetemplateintemplateclass.exe

clean:
	-${RM} templatetemplateintemplateclass.exe *.o core

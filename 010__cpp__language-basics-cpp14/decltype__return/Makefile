# Makefile for C++ Class
TARGET = decltypereturn.exe
SOURCE	= decltypereturn.cpp
OBJECTS	= ${SOURCE:.cpp=.o}
.PREFIXES	= .cpp .o
CC		= g++
CPPFLAGS	= -g -Wall -Wno-return-local-addr -Wno-unused-variable -Werror -std=c++14
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

$(TARGET): ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: $(TARGET)

clean:
	-${RM} $(TARGET) $(OBJECTS) core *~

.PHONY: clean

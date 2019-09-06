# Makefile for C++ Class
TARGET = alias.exe
SOURCE	= alias.cpp
OBJECTS	= $(SOURCE:.cpp=.o)

.PREFIXES	= .cpp .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -Wno-unused-local-typedefs
RM		= rm -f

.c.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) -lm

all: $(TARGET)

clean:
	-$(RM) $(TARGET) $(OBJECTS) core *~

.PHONY: clean

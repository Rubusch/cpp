# Makefile for C++ Class
TARGET = ruleofbigfive.exe
SOURCE	= ruleofbigfive.cpp
OBJECTS	= $(SOURCE:.cpp=.o)
.PREFIXES	= .cpp .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	$(CC) -c $(CPPFLAGS) $<

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) -lm

all: $(TARGET)

clean:
	-$(RM) $(TARGET) $(OBJECTS) core

.PHONY: clean

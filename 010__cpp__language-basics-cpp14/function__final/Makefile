# Makefile for C++ Class
SOURCE = final.cpp
TARGET = $(SOURCE:.cpp=.exe)
OBJECTS	= $(SOURCE:.cpp=.o)
.PREFIXES = .cpp .o
CC = g++
CPPFLAGS = -g -Wall -Werror -pedantic
RM = rm -f

.c.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) -lm

all: $(TARGET)

clean:
	-$(RM) $(TARGET) $(OBJECTS) core *~

.PHONY: clean

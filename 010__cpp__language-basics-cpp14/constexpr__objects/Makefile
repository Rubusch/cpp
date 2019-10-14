# Makefile for C++ Class

SOURCE	= constexpr.cpp
TARGET = $(SOURCE:.cpp=.exe)
OBJECTS	= $(SOURCE:.cpp=.o)
.PREFIXES	= .cpp .o
CC		= g++
CPPFLAGS	= -g -Wall -pedantic -Werror -Wno-unused-variable
RM		= rm -f

.c.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) -lm

all: $(TARGET)

clean:
	-$(RM) $(TARGET) $(OBJECTS) core *~

.PHONY: clean

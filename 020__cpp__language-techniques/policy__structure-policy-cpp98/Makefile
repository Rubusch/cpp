# Makefile (simple)
#
# use -O, -O1, -O2 for optimization

SOURCE = policy.cpp
TARGET = $(SOURCE:.cpp=.exe)
OBJECTS = $(SOURCE:.cpp=.o)
.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall -Werror -pedantic -std=c++98
RM = rm -f

.cpp.o:
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) -lm

all: $(TARGET)

clean:
	$(RM) $(OBJECTS) $(TARGET) *~ core



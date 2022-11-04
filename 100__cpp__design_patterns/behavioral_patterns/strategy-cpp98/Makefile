# Makefile (simple)
#
# use -O, -O1, -O2 for optimization

SOURCE = strategy.cpp
TARGET = $(SOURCE:.cpp=.elf)
OBJECTS = $(SOURCE:.cpp=.o)
.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall -Werror -pedantic -std=c++98
RM = rm -f

.cpp.o:
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

all: $(TARGET)

clean:
	$(RM) $(OBJECTS) $(TARGET) *~

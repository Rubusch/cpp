## compiles:
## $ g++ -o Test__CBasicMath.exe CBasicMath.cpp Test__CBasicMath.cpp -lcppunit
##
CXX ?= g++
#INC = ./
CXXFLAGS ?= -g -Wall $(INC)
SRC = CBasicMath.cpp
OBJ = $(SRC:.cpp=.o)
LDFLAGS += -lcppunit
TARGET ?= Test__$(SRC:.cpp=.exe)
XML = Test__$(SRC:.cpp=.xml)

$(TARGET): Test__CBasicMath.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ Test__CBasicMath.cpp $(OBJ) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *~ $(TARGET) $(OBJ) $(XML)

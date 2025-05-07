CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
SRC = Demo.cpp Game.cpp Player.cpp \
      Role/Governor.cpp Role/Spy.cpp Role/Baron.cpp Role/General.cpp Role/Judge.cpp Role/Merchant.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = demo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)

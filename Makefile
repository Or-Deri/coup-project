CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

SRC = Demo.cpp Game.cpp Player.cpp \
      Governor.cpp Spy.cpp Baron.cpp General.cpp Judge.cpp Merchant.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = demo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

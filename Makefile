#orderi429@gmail.com
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -g
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

SRC_MAIN=main.cpp Game.cpp Player.cpp PlayerFactory.cpp Governor.cpp Baron.cpp General.cpp Judge.cpp Merchant.cpp Spy.cpp
SRC_GUI= GUI.cpp Game.cpp Player.cpp PlayerFactory.cpp Governor.cpp Baron.cpp General.cpp Judge.cpp Merchant.cpp Spy.cpp
SRC_TEST=test.cpp Game.cpp Player.cpp PlayerFactory.cpp Governor.cpp Baron.cpp General.cpp Judge.cpp Merchant.cpp Spy.cpp

Main: $(SRC_MAIN)
	$(CXX) $(CXXFLAGS) $(SRC_MAIN) -o main $(LDFLAGS)

gui: $(SRC_MAIN)
	$(CXX) $(CXXFLAGS) $(SRC_GUI) -o gui $(LDFLAGS)


test: $(SRC_TEST)
	$(CXX) $(CXXFLAGS) $(SRC_TEST) -o test $(LDFLAGS)
	

valgrind_main: Main
	valgrind --leak-check=full --track-origins=yes ./main

valgrind_gui: gui
	valgrind --leak-check=full --track-origins=yes ./gui

valgrind_test: test
	valgrind --leak-check=full --track-origins=yes ./test

clean:
	rm -f *.o gui test main 

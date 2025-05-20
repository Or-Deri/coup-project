#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Game.hpp"
#include "Governor.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"

using namespace coup;

TEST_CASE("Gather") {
    Game game;
    Governor governor(game, "A");
    Merchant merchant(game, "B");

    
    game.currentPlayer()->startTurn(); // A - governor
    game.currentPlayer()->gather();
    game.nextTurn();
    CHECK(governor.coins() == 1);

    game.currentPlayer()->startTurn(); // B -merchant
    game.currentPlayer()->gather();
    CHECK(merchant.coins() == 1); 
}
TEST_CASE("Tax") {
    Game game;
    Merchant merchant(game, "A");
    Judge judge(game,"B");

    game.currentPlayer()->startTurn(); // A-merchant
    game.currentPlayer()->tax();
    game.nextTurn();
    CHECK(merchant.coins() == 2);

    game.currentPlayer()->startTurn(); // B-judge
    game.currentPlayer()->tax();
    CHECK(judge.coins() == 2);   
}

TEST_CASE("Bribe") {
    Game game;
    Governor governor(game,"A");

    governor.addCoins(4);
    game.currentPlayer()->startTurn(); // A-governor
    game.currentPlayer()->bribe();

    CHECK(governor.coins() == 0);
    CHECK(governor.getExtraTurns() == 2);
}

TEST_CASE("Arrest") {
    Game game;
    Governor governor(game, "A");
    Baron baron(game,"B");
    
    governor.addCoins(2);
    baron.addCoins(2);

    game.currentPlayer()->startTurn(); // A - governor
    game.currentPlayer()->arrest(baron);
    game.nextTurn();

    CHECK(governor.coins() == 3);
    CHECK(baron.coins() == 1);

    game.currentPlayer()->startTurn(); // B- baron
    game.currentPlayer()->arrest(governor);
    game.nextTurn();

    CHECK(governor.coins() == 2);
    CHECK(baron.coins() == 2);
    
    game.currentPlayer()->startTurn(); // A - governor
    CHECK_THROWS(game.currentPlayer()->arrest(baron));
}

TEST_CASE("Arrest twice on same player throws") {
    Game game;
    Governor governor(game, "A");
    Spy spy(game, "B");


    governor.addCoins(2);
    spy.addCoins(2);

    game.currentPlayer()->startTurn(); // A - governor
    game.currentPlayer()->arrest(spy);
    game.nextTurn();

    game.currentPlayer()->startTurn(); // B -spy
    game.currentPlayer()->gather();
    game.nextTurn();

    game.currentPlayer()->startTurn();
    CHECK_THROWS(game.currentPlayer()->arrest(spy)); // A - governor
}

TEST_CASE("Arrest player without coins throws") {
    Game game;
    Governor governor(game, "A");
    Merchant merchant(game, "B");

    governor.addCoins(2);      
    merchant.addCoins(1);      

    game.currentPlayer()->startTurn(); //A - governor
    CHECK_THROWS(governor.arrest(merchant));
}

TEST_CASE("Sanction") {
    Game game;
    Baron baron(game, "A");
    Merchant merchant(game, "B");

    baron.addCoins(3);
    merchant.addCoins(3);

    game.currentPlayer()->startTurn(); // A - baron
    game.currentPlayer()->sanction(merchant);
    game.nextTurn();

    game.currentPlayer()->startTurn(); // B- merchant
    
    CHECK_THROWS(merchant.gather());
    CHECK_THROWS(merchant.tax());
    CHECK(merchant.isSanctionBlocked());
    CHECK(baron.coins() == 0);

    game.currentPlayer()->sanction(baron); //stil B- merchant
    game.nextTurn();


    game.currentPlayer()->startTurn(); // A - baron
    game.currentPlayer()->arrest(merchant);
    game.nextTurn();

    game.currentPlayer()->startTurn(); // B- merchant
    game.currentPlayer()->gather();
    CHECK(merchant.coins() == 1);
}

TEST_CASE("Coup") {
    Game game;
    Baron baron(game, "A");
    Judge judge(game, "B");
    
    baron.addCoins(7);

    game.currentPlayer()->startTurn(); // A - baron
    game.currentPlayer()->coup(judge);

    CHECK_FALSE(judge.isInGame());
    CHECK(baron.coins() == 0);
}

TEST_CASE("Tax by Governor") {
    Game game;
    Governor governor(game, "A");

    game.currentPlayer()->startTurn(); //A governor
    game.currentPlayer()->tax();
    CHECK(governor.coins() == 3);
}

TEST_CASE("Undo Tax by Governor") {
    Game game;
    Merchant merchant(game, "A");
    Governor governor1(game, "B");
    Governor governor2(game, "C");
    
    game.currentPlayer()->startTurn();
    game.currentPlayer()->tax();        // A - merchant
    game.nextTurn();
    CHECK(merchant.coins() == 2);

    governor2.undo(merchant);
    CHECK(merchant.coins() == 0);
    
    game.currentPlayer()->startTurn(); // B - governor1
    game.currentPlayer()->tax();
    game.nextTurn();
    CHECK(governor1.coins() == 3);

    governor2.undo(governor1);
    CHECK(governor1.coins() == 0);
}

TEST_CASE("Spy blocks arrest") {
    Game game;
    Spy spy(game, "A");
    General general(game, "B");

    game.currentPlayer()->startTurn();  // A-spy 
    Spy* s = dynamic_cast<Spy*>(game.currentPlayer());
    s->blockArrest(general);
    game.currentPlayer()->gather();
    game.nextTurn();
    CHECK(general.isArrestBlocked());

    game.currentPlayer()->startTurn();  // B -general
    CHECK_THROWS(game.currentPlayer()->arrest(spy));
}

TEST_CASE("Baron invest") {
    Game game;
    Baron baron(game, "A");

    baron.addCoins(3);

    baron.startTurn();
    baron.invest();
    CHECK(baron.coins() == 6);
}
TEST_CASE("Baron invest with not enough coins") {
    Game game;
    Baron baron(game, "A");

    baron.addCoins(2);

    baron.startTurn();
    CHECK_THROWS(baron.invest());
}
TEST_CASE("Baron under sanction"){
    Game game;
    Governor governor(game, "A");
    Baron baron(game, "B");

    governor.addCoins(3);

    game.currentPlayer()->startTurn();  //A-governor
    game.currentPlayer()->sanction(baron);
    game.nextTurn();
    CHECK(baron.isSanctionBlocked());

    game.currentPlayer()->startTurn();
    game.currentPlayer()->tax();
    game.nextTurn();

    CHECK(baron.coins() == 1);
    CHECK_FALSE(baron.isSanctionBlocked());
}

TEST_CASE("Undo coup by General") {
    Game game;
    Baron baron(game, "A");
    General general(game, "B");
    
    baron.addCoins(7);
    general.addCoins(5);

    game.currentPlayer()->startTurn();  // A- baron
    game.currentPlayer()->coup(general);
    CHECK_FALSE(general.isInGame());

    general.undo(*game.getLastTarget()); // B- general
    CHECK(baron.isInGame());
    CHECK(baron.coins() == 0);
    CHECK(general.coins() == 0);
}
TEST_CASE("Undo coup with not enough coins") {
    Game game;
    Baron baron(game, "A");
    General general(game, "B");

    baron.addCoins(7);
    
    game.currentPlayer()->startTurn();  // A- baron
    game.currentPlayer()->coup(general);
    CHECK_FALSE(general.isInGame());

    CHECK_THROWS(general.undo(baron));
}
TEST_CASE("Arrest General") {
    Game game;
    Baron baron(game, "A");
    General general(game, "B");
    
    baron.addCoins(2);
    general.addCoins(2);

    baron.startTurn();
    baron.arrest(general);

    CHECK(baron.coins() == 2);
    CHECK(general.coins() == 2);
}

TEST_CASE("Sanction Judge") {
    Game game;
    Baron baron(game, "A");
    Judge judge(game, "B");

    baron.addCoins(4);
    game.currentPlayer()->startTurn();
    game.currentPlayer()->sanction(judge);
    
    game.nextTurn();

    CHECK_THROWS(judge.gather());
    CHECK(judge.isSanctionBlocked());
    CHECK(baron.coins() == 0);
}

TEST_CASE("Undo bribe by judge"){
    Game game;
    Baron baron(game, "A");
    Judge judge(game, "B");
    
    baron.addCoins(4);

    baron.startTurn();
    baron.bribe();
    CHECK(baron.getExtraTurns() == 2);

    judge.undo(baron);
    CHECK(baron.getExtraTurns() == 0);
    CHECK(baron.coins() == 0);
}

TEST_CASE("Merchant receives bonuses"){
    Game game;
    Merchant merchant(game,"A");

    merchant.addCoins(3);
    merchant.startTurn();
    
    CHECK(merchant.coins() == 4);
}

TEST_CASE("Merchant arrest"){
    Game game;
    General general(game, "A");
    Merchant merchant(game,"B");

    general.addCoins(2);
    merchant.addCoins(2);

    general.startTurn();
    general.arrest(merchant);

    CHECK(general.coins() == 2);
    CHECK(merchant.coins() == 0);
}

TEST_CASE("Coup not enough coins") {
    Game game;
    General general(game, "A");
    Judge judge(game, "B");

    general.startTurn();
    CHECK_THROWS(general.coup(judge));
}



TEST_CASE("Action when not your turn ") {
    Game game;
    Spy spy(game, "A");
    Judge judge(game, "B");

    CHECK_THROWS(judge.startTurn());
}

TEST_CASE("Turn rotation skips inactive players") {
    Game game;
    Governor governor(game, "A");
    Baron baron(game, "B");
    Merchant merchant(game, "C");
    
    
    baron.addCoins(7);

    game.currentPlayer()->startTurn();  // A -governor
    game.currentPlayer()->gather();
    game.nextTurn();

    game.currentPlayer()->coup(merchant); // B- baron
    game.nextTurn();

    CHECK(game.turn() == "A");
} 

//orderi429@gmail.com
#include <iostream>
#include <vector>
#include "Game.hpp"
#include "PlayerFactory.hpp"
#include "Governor.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"

using namespace std;
using namespace coup;

// Print active player name and bakances
void printPlayers(const vector<Player*>& players) {
    cout << "Active players and balances: ";
    for (auto p : players) {
        if(p->getInGame()){
            cout << p->getName() << "(" << p->coins() << "),   ";
        }
    }
    cout << endl;
}

int main() {
    Game game;

    // Create one player of each role
    Governor governor(game, "Governor");
    Merchant merchant(game, "Merchant");
    Spy spy(game, "Spy");
    Baron baron(game, "Baron");
    Judge judge(game, "Judge");
    General general(game, "General");

    //Everyone does tax 3 times
    for (int i = 0; i < 3; ++i) {
        governor.tax();    
        game.nextTurn();

        merchant.tax(); 
        game.nextTurn();

        spy.tax();
        game.nextTurn();

        baron.tax();    
        game.nextTurn();

        judge.tax();    
        game.nextTurn();

        general.tax();    
        game.nextTurn();
    }
    
    printPlayers(game.getPlayersList());


    // Governor arrest on spy
    cout << "\nTurn: " << game.turn() << endl;
    governor.arrest(spy);
    cout << "Governor arrest on spy" << endl;
    printPlayers(game.getPlayersList());
    game.nextTurn();

    // Merchant sanction on baron
    cout << "\nTurn: " << game.turn() << endl;
    merchant.sanction(baron);
    cout << "Merchant sanction on baron" << endl;
    printPlayers(game.getPlayersList());
    game.nextTurn();

    //Spy blocked arrest on Merchant
    cout << "\nTurn: " << game.turn() << endl;
    spy.blockArrest(merchant);
    cout << "Spy blocked arrest on Merchant" << endl;
    printPlayers(game.getPlayersList());
    game.nextTurn();

    //Baron invest
    cout << "\nTurn: " << game.turn() << endl;
    baron.invest();
    cout << "Baron invest" << endl;
    printPlayers(game.getPlayersList());
    game.nextTurn();

    //judge performed bribe and tax ,gather
    cout << "\nTurn: " << game.turn() << endl;
    judge.bribe();
    game.nextTurn();
    cout << "judge performed bribe" << endl;
    judge.tax();
    game.nextTurn();
    cout << "Judge tax" << endl;
    judge.gather();
    game.nextTurn();
    cout << "Judge gather" << endl;
    printPlayers(game.getPlayersList());

    // general sanctions Baron for 3 coins
    cout << "\nTurn: " << game.turn() << endl;
    general.sanction(baron);
    cout << "general sanctioned Baron" << endl;
    printPlayers(game.getPlayersList());
    game.nextTurn();

    //  Governor calls a coup on General 
    cout << "\nTurn: " << game.turn() << endl;
    governor.coup(general);
    cout << "Governor performed coup on General" << endl;
    printPlayers(game.getPlayersList());

    return 0;
}

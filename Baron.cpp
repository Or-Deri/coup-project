#include "Baron.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>



namespace coup {

    Baron::Baron(Game& game, const std::string& name) : Player(game, name){}



    void Baron::invest(){
        
        if (game->turn() != getName()) {
            throw std::runtime_error("Not baron's turn");
        }
        
        if (coins() < 3){
            throw std::runtime_error ("Not enough coins to invest");
        }

        subCoins(3);
        addCoins(6);


        game->setLastAction("invest");
        game->setLastPlayer(this);
        game->nextTurn();
    }



    
    void Baron::gather(){
        if (game->turn() != getName()) {
            throw std::runtime_error(std::string("Not ")+typeid(*this).name()+std::string("'s turn")); //---------------------??
        }

        addCoins(1);

        lastIBlockedArrest = nullptr;

        game->setLastAction("gather");
        game->setLastPlayer(this);
        game->nextTurn();

    }

    void Baron::tax(){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        if(sanctionBlocked){
            addCoins(1);
        }
        else{
            addCoins(2);
        }

        lastIBlockedArrest = nullptr;

        game->setLastAction("tax");
        game->setLastPlayer(this);
        game->nextTurn();

    }



}
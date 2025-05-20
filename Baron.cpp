#include "Baron.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>
#include <iostream>


namespace coup {

    Baron::Baron(Game& game, const std::string& name) : Player(game, name){}


    void Baron::invest(){
        
        if (game->turn() != getName()) {
            throw std::runtime_error("Not baron's turn");
        }
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }
        
        if (coins() < 3){
            throw std::runtime_error ("Not enough coins to invest");
        }

        subCoins(3);
        addCoins(6);

        setLastTargetArrest(nullptr);

        game->setLastAction("invest");
        game->setLastPlayer(this);
    }


    void Baron::gather(){
        if (game->turn() != getName()) {
            throw std::runtime_error(std::string("Not ")+typeid(*this).name()+std::string("'s turn")); //---------------------??
        }
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        addCoins(1);

        setLastTargetArrest(nullptr);

        game->setLastAction("gather");
        game->setLastPlayer(this);
    }

    void Baron::tax(){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        if(sanctionBlocked){
            addCoins(1);
        }
        else{
            addCoins(2);
        }

        setLastTargetArrest(nullptr);
        game->setLastAction("tax");
        game->setLastPlayer(this);
    }
}
#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include <stdexcept>


namespace coup {


    Player::Player (Game& game , const std::string& name){
        this->game = &game;
        this->name = name; 
        this->balance = 0;
        this->inGame = true;
        game.addPlayer(this);
        this->arrestBlocked = false;
        this->sanctionBlocked = false;
        this->lastBlockedBySanction = nullptr;
        this->extraTurns = 0;
    }


    std::string Player::getName() const{
        return name;
    }


    int Player::coins() const{
        return balance;
    }

    void Player::addCoins(int x){
        balance += x;
    }

    void Player::subCoins(int x){
        balance -= x;
    }

    bool Player::isInGame() const{
        return inGame;
    }

    void Player::setInGame(bool x){
        inGame = x;
    }

    
    int Player::getExtraTurns(){
        return extraTurns;
    }
    void Player::subExtraTurns(){
        extraTurns--;
    }

    void Player::setArrestBlocked(bool x){
        arrestBlocked = x;
    }
    bool Player::isArrestBlocked() const{
        return arrestBlocked;
    }

    void Player::setSanctionBlocked(bool x){
        sanctionBlocked = x;
    }
    bool Player::isSanctionBlocked(){
        return sanctionBlocked ;
    }

    // void Player::setExtraTurns(int x){
    //     extraTurns = x;
    // }

    Player* Player::getLastIBlockedArrest() const{
        return lastIBlockedArrest;
    }
    void Player::setLastIBlockedArrest(Player& target){
        lastIBlockedArrest = &target;
    }


    void Player::startTurn(){    // רק SPY ו merchant דורסות את הפונקציה הזאת 
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        //If a player was blocked by sanction in the previous turn, the block is removed
        if (lastBlockedBySanction != nullptr){
            lastBlockedBySanction->setSanctionBlocked(false);
            lastBlockedBySanction = nullptr;
        }
        
    }

    void Player::gather(){
        if (game->turn() != getName()) {
            throw std::runtime_error(std::string("Not ")+typeid(*this).name()+std::string("'s turn"));
        }

        if(sanctionBlocked){
            throw std::runtime_error("You are blocked by sanction");
        }

        addCoins(1);

        lastIBlockedArrest = nullptr;

        game->setLastAction("gather");
        game->setLastPlayer(this);
        game->nextTurn();
    }

    void Player::tax(){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        if(sanctionBlocked){
            throw std::runtime_error("You are blocked by sanction");
        }

        addCoins(2);

        lastIBlockedArrest = nullptr;

        game->setLastAction("tax");
        game->setLastPlayer(this);
        game->nextTurn();
    }

    void Player::bribe(){
        
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        if (coins() < 4) {
            throw std::runtime_error("Not enough coins to bribe");
        }
    
        subCoins(4);
        extraTurns = 1;    
        
        lastIBlockedArrest = nullptr;

        game->setLastAction("bribe");
        game->setLastPlayer(this);
    }

    void Player::arrest(Player& target){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        if (arrestBlocked) {
            arrestBlocked = false; 
            throw std::runtime_error("You have been blocked , You can't do arrest");
        }

        //It is impossible to do 2 consecutive turns on the same player
        if(&target == lastIBlockedArrest){
            throw std::runtime_error("In the previous turn you did it on the same player");
        }
        

        // If a merchant is attacked by a arrest, he Losing 2 coins instead of  pay 1 to the attacking player
        Merchant* merchant = dynamic_cast<Merchant*>(&target);
        General* general = dynamic_cast<General*>(&target);
        if(merchant){
            merchant->attackedByArrest();
            game->setLastAction("arrest");
            game->setLastPlayer(this);
            game->nextTurn();
            return;
        }
        else if(general){ // Nothing is happening
            
        }
        else{    
            target.subCoins(1);
            addCoins(1);
            // לממש את זה שאסור לעשות את הפעולה על אותו שחקן 2 תורות רצוף (האם רצוף מאותו שחקן או מכול השחקנים ??) 
        }

        setLastIBlockedArrest(target);

        game->setLastAction("arrest");
        game->setLastPlayer(this);
        game->nextTurn();
    }

    void Player::sanction(Player& target){
        
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        Judge* judge = dynamic_cast<Judge*>(&target);
        if(judge){
            if(coins() < 4){
                throw std::runtime_error("Not enough coins to sanction");
            }
            subCoins(4);
        }
        else{
            if(coins() < 3){
                throw std::runtime_error("Not enough coins to sanction");
            }
            subCoins(3);
        }

        target.setSanctionBlocked(true); 

        lastIBlockedArrest = nullptr;

        game->setLastAction("sanction");
        game->setLastPlayer(this);
        game->nextTurn();
    }

    void Player::coup(Player& target){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        if (coins() < 7) {
            throw std::runtime_error("Not enough coins to coup");
        }
    
        subCoins(7);


        game->setLastAction("coup");
        game->setLastPlayer(this);
        // game->lastTarget = &target;
    
            
        target.setInGame(false);
        lastIBlockedArrest = nullptr;

        game->nextTurn();
    }
    
}
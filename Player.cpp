#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include <stdexcept>
#include <iostream>


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
        this->lastTargetArrest = nullptr;
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

    void Player::setExtraTurns(int x){
        extraTurns = x;
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



    Player* Player::getLastTargetArrest() const{
        return lastTargetArrest;
    }
    void Player::setLastTargetArrest(Player* target){
        lastTargetArrest = target;
    }



    void Player::startTurn(){   
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        //If a player was blocked by sanction in the previous turn, the block is removed
        if (lastBlockedBySanction != nullptr){
            lastBlockedBySanction->setSanctionBlocked(false);
            lastBlockedBySanction = nullptr;
        }
    }

    void Player::pass() {
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        game->setLastAction("pass");
        game->setLastPlayer(this);
        game->setLastTarget(nullptr);
        game->nextTurn();
    }

    void Player::gather(){
        if (game->turn() != getName()) {
            throw std::runtime_error(std::string("Not ")+typeid(*this).name()+std::string("'s turn"));
        }

        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        if(sanctionBlocked){
            throw std::runtime_error("You are blocked by sanction");
        }

        addCoins(1);

        setLastTargetArrest(nullptr);
        game->setLastAction("gather");
        game->setLastPlayer(this);
    }

    void Player::tax(){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        if(sanctionBlocked){
            throw std::runtime_error("You are blocked by sanction");
        }

        addCoins(2);

        setLastTargetArrest(nullptr);
        game->setLastAction("tax");
        game->setLastPlayer(this);
        game->setLastTarget(this);
    }

    void Player::bribe(){

        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        if (coins() < 4) {
            throw std::runtime_error("Not enough coins to bribe");
        }
    
        subCoins(4);
        setExtraTurns(2);  
        
        setLastTargetArrest(nullptr);
        game->setLastAction("bribe");
        game->setLastPlayer(this);
        game->setLastTarget(this);
    }

    void Player::arrest(Player& target){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        if (arrestBlocked) {
            arrestBlocked = false; 
            throw std::runtime_error("You have been blocked , You can't do arrest");
        }

        //It is impossible to do 2 consecutive turns on the same player
        if(&target == getLastTargetArrest()){
            throw std::runtime_error("In the previous turn you did it on the same player");
        }
        
        if(target.coins() < 1){
            throw std::runtime_error("The player target has no enough coins");
        }

        // If a merchant is attacked by a arrest, he Losing 2 coins instead of  pay 1 to the attacking player
        Merchant* merchant = dynamic_cast<Merchant*>(&target);
        General* general = dynamic_cast<General*>(&target);
        if(merchant){
            
            if(target.coins() < 2){
                throw std::runtime_error("The player target has no enough coins");
            }
            merchant->attackedByArrest();
        }
        else if(general){ // Nothing is happening
            
        }
        else{    
            target.subCoins(1);
            addCoins(1);
        }

        setLastTargetArrest(&target);
        game->setLastAction("arrest");
        game->setLastPlayer(this);
    }

    void Player::sanction(Player& target){
        
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
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
        setLastTargetArrest(nullptr);

        lastBlockedBySanction = &target;
        game->setLastTarget(&target);
        game->setLastAction("sanction");
        game->setLastPlayer(this);
    }

    void Player::coup(Player& target){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        
        if (coins() < 7) {
            throw std::runtime_error("Not enough coins to coup");
        }
        
        subCoins(7);
        target.setInGame(false);

        setLastTargetArrest(nullptr);
        game->setLastTarget(&target);
        game->setLastAction("coup");
        game->setLastPlayer(this);
    }

}
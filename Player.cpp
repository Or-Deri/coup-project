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

    void Player::lost(){
        inGame = false;
    }

    void Player::startTurn(){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
    }

    void Player::gather(){
        if (game->turn() != getName()) {
            throw std::runtime_error(std::string("Not ")+typeid(*this).name()+std::string("'s turn"));
        }

        addCoins(1);

        game->lastAction = "gather";
        game->lastActor = this;
    }

    void Player::tax(){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        addCoins(2);

        game->lastAction = "tax";
        game->lastActor = this;
    }

    void Player::bribe(){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        if (coins() < 3) {
            throw std::runtime_error("Not enough coins to bribe.");
        }
    
        // לסיים
        
        subCoins(4);
        // לממש 2 תורים ברציופות       
        
        
        game->lastAction = "bribe";
        game->lastActor = this;
    }

    void Player::arrest(Player& target){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        // If a merchant is attacked by a arrest, he Losing 2 coins instead of  pay 1 to the attacking player
        Merchant* merchant = dynamic_cast<Merchant*>(&target);
        if(merchant){
            merchant->attackedByArrest();
            return;
        }
        else{    
            target.subCoins(1);
            addCoins(1);
            // לממש את זה שאסור לעשות את הפעולה על אותו שחקן 2 תורות רצוף (האם רצוף מאותו שחקן או מכול השחקנים ??) 
        }


        game->lastAction = "arrest";
        game->lastActor = this;
        game->nextTurn();
    }

    void Player::sanction(Player& target){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        //השחקן בוחר שחקן אחר ומונע ממנו להשתמש בפעולות כלכליות (gather, tax) עד לתורו הבא. עלות פעולה זו היא 3 מטבעות.

        subCoins(3);


        game->lastAction = "sanction";
        game->lastActor = this;
    }

    void Player::coup(Player& target){
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        General* general = dynamic_cast<General*>(&target);
        if(general){// גנרל יכול לבטל את הפעולה
            
            if (general->isCoupUndo()){
                general->setUndo(false);
                // ממשיך לתור הבא 
                return;
            }
        }

        subCoins(7);
        target.lost();

        game->lastAction = "coup";
        game->lastActor = this;
    }
    
}
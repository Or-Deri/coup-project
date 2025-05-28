//orderi429@gmail.com
#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include <iostream>

namespace coup {

    Game::Game(){
        playerTurn = 0;
        playersList.clear();

    }

    void Game::addPlayer(Player* p){
        
        if(playersList.size() >= 6) {
            throw std::runtime_error("Maximum 6 players in game");
        }
        
        for (auto* existing : playersList) {
            if (existing->getName() == p->getName()) {
                throw std::runtime_error("Player name '" + p->getName() + "' already exists");
            }
        }
        playersList.push_back(p);
    }

    std::vector<Player*> Game::getPlayersList(){
        return playersList;
    }
    
    std::string Game::getLastAction(){
        return lastAction;
    }    
    void Game::setLastAction(const std::string& name){
        lastAction = name;
    }
    Player* Game::getLastPlayer(){
        return lastPlayer;
    }
    void Game::setLastPlayer(Player* p){
        lastPlayer = p;
    }

    Player* Game::getLastTarget(){
        return lastTarget;
    }
    void Game::setLastTarget(Player* p){
        lastTarget = p;
    }

    Player* Game::currentPlayer(){
        return playersList.at(playerTurn);
    }


    void Game::nextTurn(){

        Player* current = currentPlayer();

        if (current->getExtraTurns() > 0) {
            current->subExtraTurns();
            current->startTurn();
            return;
        }
    
        int n = playersList.size();
    
        for (int step = 1; step <= n; ++step) {
            int idx = (playerTurn + step) % n;
            if (playersList[idx]->getInGame()) {
                playerTurn = idx;
                playersList[playerTurn]->startTurn();
                return;
            }
        }
        throw std::runtime_error("No active players");
    }



    std::string Game::turn(){
        std::string PlayerName =  playersList.at(playerTurn)->getName();
        return PlayerName;
    }


    std::vector <std::string> Game::players() const{
        std::vector <std::string> names;
        for(Player* p : playersList){
            
            if(p->getInGame()){
                names.push_back(p->getName());
            }
        }
        return names;
    }

    std::string Game::winner() {
        std::string last;
        
        if(playersInTheGame() != 1){
            throw std::runtime_error("The game is not finisd");
        }
        
        for(Player* p : playersList) {
            
            if(p->getInGame()){
                last = p->getName();
                break;
            }
        }
        return last;
    }

    int Game::playersInTheGame(){
        int ans = 0;
        for(Player* p : playersList){    
            if(p->getInGame()){
                ans++;
            }
        }
        return ans;
    }
}
#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>


namespace coup {

    Game::Game(){
        playerTurn = 0;
        playersList.clear();

    }

    void Game::addPlayer(Player* p){
        
        if(playersList.size() >= 6) {
            throw std::runtime_error("Maximum 6 players in game");
        }

        playersList.push_back(p);
    }

    Player* Game::currentPlayer(){
        return playersList.at(playerTurn);
    }

    void Game::nextTurn(){
        int current = playerTurn;
        playerTurn = (playerTurn + 1) % players().size();

        while(!playersList.at(playerTurn)->isInGame()){

            playerTurn = (playerTurn + 1) % players().size();
            
            if(current == playerTurn){
                throw std::runtime_error("No active players");
            }
        }

        playersList.at(playerTurn)->startTurn();
    }

    std::string Game::turn(){
        std::string PlayerName =  playersList.at(playerTurn)->getName();
        return PlayerName;
    }

    std::vector <std::string> Game::players() const{
        
        std::vector <std::string> names;

        for(Player* p : playersList){
            
            if(p->isInGame()){
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
            
            if(p->isInGame()){
                last = p->getName();
                break;
            }
        }
        return last;
    }

    int Game::playersInTheGame(){

        int ans = 0;

        for(Player* p : playersList){    
            if(p->isInGame()){
                ans++;
            }
        }
        return ans;
    }


}
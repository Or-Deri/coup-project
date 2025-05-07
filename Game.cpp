#include "Game.hpp"
#include "Player.hpp"

namespace coup {

    Game::Game(){
        PlayerTurn = 0;
    }

    void Game::addPlayer(Player* p){
        
        if(players_list.size() >= 6) {
            throw std::runtime_error("Maximum 6 players in game");
        }

        PlayersList.push_back(p);
    }

    Player* Game:: currentPlayer(){
        return Players[PlayerTurn];
    }

    void Game::nextTurn(){
        int current = PlayerTurn;
        PlayerTurn = (PlayerTurn + 1) % Players.size();

        while(!Players[currentPlayer].isInGame){

            PlayerTurn = (PlayerTurn + 1) % Players.size();
            
            if(current == PlayerTurn){
                throw std::runtime_error("No active players");
            }
        }

        PlayersList[PlayerTurn]->startTurn();
    }

    std::string turn() const{
        std::string PlayerName =  players_list.at(PlayerTurn)->getName();
        return PlayerName;
    }

    sts::vector <std::string> Game::players() const{
        
        std::vector <std::string> names;

        for(Player p : PlayersList){
            
            if(p->isInGame()){
                names.push_back(p->getName());
            }
        }
        return names;
    }

    std::string winner() const{

        std::string last;
        
        if(playersInTheGame != 1){
            throw std::runtime_error("The game is not finisd");
        }
        
        for(Player* p : PlayersList){
            
            if(p->isInGame()){
                last = p->getName();
                break;
            }
        }
        return last;
    }

    int playersInTheGame() const{

        int ans = 0;

        for(Player* p : PlayersList){    
            if(p->isInGame()){
                ans++;
            }
        }
        return ans;
    }


}
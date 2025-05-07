#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>


namespace coup {

    Game::Game(){
        PlayerTurn = 0;
        
    }

    void Game::addPlayer(Player* p){
        
        if(PlayersList.size() >= 6) {
            throw std::runtime_error("Maximum 6 players in game");
        }

        PlayersList.push_back(p);
    }

    Player* Game:: currentPlayer(){
        return players().at(PlayerTurn);
    }

    void Game::nextTurn(){
        int current = PlayerTurn;
        PlayerTurn = (PlayerTurn + 1) % players().size();

        while(!players().at(currentPlayer()).isInGame()){

            PlayerTurn = (PlayerTurn + 1) % players().size();
            
            if(current == PlayerTurn){
                throw std::runtime_error("No active players");
            }
        }

        PlayersList.at(PlayerTurn()).startTurn();
    }

    std::string turn(){
        std::string PlayerName =  PlayersList.at(PlayerTurn()).getName();
        return PlayerName;
    }

    std::vector <std::string> Game::players() const{
        
        std::vector <std::string> names;

        for(Player p : PlayersList){
            
            if(p.isInGame()){
                names.push_back(p.getName());
            }
        }
        return names;
    }

    std::string winner() {

        std::string last;
        
        if(this.playersInTheGame() != 1){
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

    int playersInTheGame(){

        int ans = 0;

        for(Player* p : PlayersList){    
            if(p->isInGame()){
                ans++;
            }
        }
        return ans;
    }


}
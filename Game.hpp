#include <vector>
#include <string>


class Game{
    
    private:
        
        std::vector <Player*> Players;
        int Turn;
        
    public:
        Game();
        void addPlayer();
        Player* currentPlayer();
        void nextTurn();


        

}
    
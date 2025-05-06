#include "Spy.hpp"
#include "Player.hpp"
#include "Game.hpp"



namespace coup {

    Spy::Spy(Game& game, const std::string& name){
        this.game = game;
        this.name = name;
    }
    void startTurn(){}

    void Spy::ability (Game& game, Player& self, Player* target){
        

        std::cout << name
        // יכול לראות את כמות המטבעות של שחקן אחר ולמנוע ממנו להשתמש בפעולת מעצר (arrest) בתורו הבא. פעולה זו אינה עולה מטבעות ואינה נחשבת לתור


        std::cout << // מדפיס את שמות השחקנים וכמה יש לכול אחד 
    }    
}
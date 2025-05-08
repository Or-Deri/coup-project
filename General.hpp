#pragma once
#include "Player.hpp"

namespace coup {

    class General : public Player {
    
    private:
        bool undoTheCoup = false;
    
    public:
        General(Game& game, const std::string& name);
        bool isCoupUndo() const;
        void setUndo(bool x);
        void ReturnsCoin(Player& target);
        void undo(Player& target); 
    };

}

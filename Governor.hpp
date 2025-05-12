#pragma once
#include "Player.hpp"

namespace coup {

    class Governor : public Player {

        private:
        
            bool undoTheTax = false;
        
        public:
        
            Governor(Game& game, const std::string& name);
        
            void setUndo(bool x);
            bool isTaxUndo() const;
            void undo(Player& target);
            void tax() override;
    };

}
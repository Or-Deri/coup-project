#pragma once
#include "Player.hpp"



namespace coup {

    class Judge : public Player {
        
        private:
        bool undoTheBribe = false;
            
        public:
            Judge(Game& game, const std::string& name);
            
            bool isBribeUndo();
            void setUndo(bool x);
            void undoBribe();
        };
}
#pragma once
#include "Player.hpp"


class Baron : public Player{

    public:
    
        std::string name() const override {
            return "Baron";
        }

        void ability (Game& game, Player& self) override;


};
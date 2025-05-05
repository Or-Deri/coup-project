#pragma once
#include "Player.hpp"


class Governor : public Player {

    public:
    
        std::string name() const override {
            return "Governor";
        }

        void ability (Game& game, Player& self) override;


};
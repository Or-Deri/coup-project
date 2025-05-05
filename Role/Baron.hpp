#pragma once
#include "Role.h"


class Baron : public Role {

    public:
    
        std::string name() const override {
            return "Baron";
        }

        void ability (Game& game, Player& self) override;


};
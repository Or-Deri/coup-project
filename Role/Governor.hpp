#pragma once
#include "Role.h"


class Governor : public Role {

    public:
    
        std::string name() const override {
            return "Governor";
        }

        void ability (Game& game, Player& self) override;


};
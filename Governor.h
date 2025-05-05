#pragma once
#include "Role.hpp"


class Governor : public Role {

    public:
    
        std::string name() const override {
            return "Governor";
        }

        void ability (Game& game, Player& self) override;


};
#pragma once
#include <string>
#include "Player.hpp"


class Spy : public Player {

    public:
    
        std::string name() const override{
            return "Spy";
        }


        
}
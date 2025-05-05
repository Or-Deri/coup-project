#pragma once
#include <string>


class Role {                   // Strategy interface
    public:
        
        virtual std::string name() = 0;
        virtual void ability (Game& game, Player& self, Player* target) = 0;
        virtual ~Role () ;

};
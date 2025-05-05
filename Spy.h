#pragma once
#include <string>

class Spy : public Role{

    public:
    
        std::string name() const override{
            return "Spy";
        }

        void ability (Game& game, Player& self, Player* target)override;    



        


}
#pragma once
#include "Player.hpp"
#include "Game.hpp"
#include <string>
#include <memory>

namespace coup {

    class PlayerFactory {
    public:
        
        static Player* createPlayer(Game& game,const std::string& name, const std::string& roleName);

        static Player* createRandomPlayer(Game& game,const std::string& name);
    };

}

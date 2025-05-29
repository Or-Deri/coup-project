//orderi429@gmail.com
#pragma once
#include "Player.hpp"
#include "Game.hpp"
#include <string>
#include <memory>

namespace coup {

    class PlayerFactory {
    public:
        /**
        * @brief Creates a new player with a random role. 
        * This method randomly selects one of the six available roles and returns
        * a dynamically allocated Player object of that role.
        * 
        * @param game Reference to the game instance the player will be part of.
        * @param name The name of the new player.
        * @return Pointer to the newly created Player-derived object.
        * @throws std::runtime_error If an unexpected value is generated.
        */
        static Player* createRandomPlayer(Game& game,const std::string& name);
    };

}

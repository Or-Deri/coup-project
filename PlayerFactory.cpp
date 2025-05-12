#pragma once
#include "Game.hpp"
#include "Spy.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Baron.hpp"
#include "Governor.hpp"
#include "Merchant.hpp"
#include <random>
#include <string>
#include <stdexcept>


namespace coup {

    class PlayerFactory {
    public:
        static Player* createRandomPlayer(Game& game, const std::string& name) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> dist(0, 5); // 6 roles

            int choice = dist(gen);

            switch (choice) {
                case 0: return new Spy(game, name);
                case 1: return new General(game, name);
                case 2: return new Judge(game, name);
                case 3: return new Baron(game, name);
                case 4: return new Governor(game, name);
                case 5: return new Merchant(game, name);
                default: throw std::runtime_error("Invalid role assignment");
            }
        }
    };

}

#include "Game.hpp"
#include "Player.hpp"
#include "Spy.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Baron.hpp"
#include "Governor.hpp"
#include "Merchant.hpp"
#include "PlayerFactory.hpp"
#include <random>
#include <string>
#include <stdexcept>
#include <memory> 



namespace coup {

    //אולי למחוק 
    Player* PlayerFactory::createPlayer(Game& game,const std::string& name, const std::string& roleName) {
        if (roleName == "Governor") {
            return new Governor(game, name);
        } else if (roleName == "General") {
            return new General(game, name);
        } else if (roleName == "Judge") {
            return new Judge(game, name);
        } else if (roleName == "Spy") {
            return new Spy(game, name);
        } else if (roleName == "Baron") {
            return new Baron(game, name);;
        } else if (roleName == "Merchant") {
            return new Merchant(game, name);
        } else {
            throw std::invalid_argument("Unknown role");
        }
    }

    Player* PlayerFactory::createRandomPlayer(Game& game, const std::string& name) {
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
}

#include "Governor.hpp"
#include "Player.hpp"
#include "Game.hpp"

void Governor::ability(Game& game, Player& self) {
    self.add_coins(3); 
}

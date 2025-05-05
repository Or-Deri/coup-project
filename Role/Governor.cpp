#include "Governor.h"
#include "Player.h"
#include "Game.h"

void Governor::ability(Game& game, Player& self) {
    self.add_coins(3); 
}

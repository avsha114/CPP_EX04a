#include "Player.hpp"
#include <string>

using namespace std;

namespace pandemic
{
    Player& Player::drive(City){return *this;}
    Player& Player::fly_direct(City){return *this;}
    Player& Player::fly_charter(City){return *this;}
    Player& Player::fly_shuttle(City){return *this;}
    Player& Player::build(){return *this;}
    Player& Player::discover_cure(Color){return *this;}
    Player& Player::treat(City){return *this;}
    string Player::role(){return "Hi";}
    Player & Player::take_card(City){return *this;}
}
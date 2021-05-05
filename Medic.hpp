#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{
    class Medic: public Player
    {
        public:
            Medic(Board& gameBoard, City city)
                            : Player(gameBoard, city, "Medic") {}
            Player& treat(City);
    };
}
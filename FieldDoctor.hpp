#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{
    class FieldDoctor: public Player
    {
        public:
            FieldDoctor(Board& gameBoard, City city)
                            : Player(gameBoard, city, "FieldDoctor") {}
            Player& treat(City);
    };
}
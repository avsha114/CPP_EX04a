#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{
    class Dispatcher: public Player
    {
        public:
            Dispatcher(Board& gameBoard, City city)
                            : Player(gameBoard, city, "Dispatcher") {}
            Player& fly_direct(City);
    };
}
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{
    class OperationsExpert: public Player
    {
        public:
            OperationsExpert(Board& gameBoard, City city)
                            : Player(gameBoard, city, "OperationsExpert") {}
            Player& build();
    };
}
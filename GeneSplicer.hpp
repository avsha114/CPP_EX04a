#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{
    class GeneSplicer: public Player
    {
        public:
            GeneSplicer(Board& gameBoard, City city)
                            : Player(gameBoard, city, "GeneSplicer") {}
            Player& discover_cure(Color);
    };
}
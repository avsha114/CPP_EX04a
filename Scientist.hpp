#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{
    class Scientist: public Player
    {
        int n;

        public:
            Scientist(Board& gameBoard, City city, int number)
                            : Player(gameBoard, city, "Scientist"), n(number){}
            Player& discover_cure(Color);
    };
}
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{
    class Researcher: public Player
    {
        public:
            Researcher(Board& gameBoard, City city)
                            : Player(gameBoard, city, "Researcher") {}
            Player& discover_cure(Color);
    };
}
#include "Board.hpp"

namespace pandemic
{
    int a=0;
    int & Board::operator[](City c){return a;}
    bool Board::is_clean(){return true;}

    std::ostream& operator<<(std::ostream& out, Board& b){return out;}
}
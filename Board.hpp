#pragma once
#include <map>
#include <set>
#include "City.hpp"

namespace pandemic
{
    class Board
    {
        static std::map<City, std::set<City>> connections;
        std::map<City, int> diseaseLevels;
        std::set<City> researchStations;

        public:
            Board(){};

            int &operator[](City);
            bool is_clean();
            void remove_cures(){}

            friend std::ostream& operator<<(std::ostream&, Board&);
    };
}
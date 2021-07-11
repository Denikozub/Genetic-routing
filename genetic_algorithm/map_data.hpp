#ifndef MAP_DATA_HPP
#define MAP_DATA_HPP

#include <vector>
#include "../geometry/point.hpp"
#include "../geometry/polygon.hpp"

class MapData {
public:
    std::vector<std::pair<Polygon, int>> obstacles;
    Point start, end;
    std::vector<Point> pts;
    MapData(const std::vector<std::pair<Polygon, int>>&, const Point&, const Point&);
};

#endif
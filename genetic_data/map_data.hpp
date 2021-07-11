#ifndef MAP_DATA_HPP
#define MAP_DATA_HPP

#include "data.hpp"
#include "../geometry/point.hpp"
#include "../geometry/polygon.hpp"

struct MapData : Data{
    std::vector<std::pair<Polygon, int>> obstacles;
    Point start, end;
    std::vector<Point> pts;
    MapData(const std::vector<std::pair<Polygon, int>>&, const Point&, const Point&);
    size_t get_range() const override;
    double fitness(const std::vector<size_t>&) const override;
};

#endif
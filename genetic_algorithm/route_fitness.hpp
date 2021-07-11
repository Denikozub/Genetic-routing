#ifndef ROUTE_FITNESS_HPP
#define ROUTE_FITNESS_HPP

#include "fitness.hpp"
#include <vector>
#include "../geometry/point.hpp"
#include "../geometry/polygon.hpp"

class RouteFitness : Fitness {
    std::vector<std::pair<Polygon, int>> obstacles;
    Point start, end;
    std::vector<Point> pts;
public:
    RouteFitness(const std::vector<std::pair<Polygon, int>>&, const Point&, const Point&);
    void set_start(const Point&);
    void set_end(const Point&);
    double eval(const Gene&) const override;
};

#endif

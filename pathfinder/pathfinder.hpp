#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "../geometry/point.hpp"
#include <vector>
using std::vector;

class Pathfinder {
public:
    virtual void set_start(const Point&) = 0;
    virtual void set_end(const Point&) = 0;
    virtual vector<Point> find_path(size_t, size_t, size_t, size_t,
        size_t, double, double, int, int, int, bool=false) const = 0;
};

#endif
#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "point.hpp"
#include "polygon.hpp"
#include "gene.hpp"
#include <vector>
using std::vector;

class Pathfinder {
    vector<Polygon> obstacles;
    Point start, end;
    vector<Point> pts;
    friend class Gene;
public:
    Pathfinder(const vector<Polygon>&, const Point&, const Point&);
    void set_start(const Point&);
    void set_end(const Point&);
    void find_path(int, int);
};

#endif
#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "point.hpp"
#include "polygon.hpp"
#include "gene.hpp"
#include "polygon.hpp"
#include "point.hpp"
#include <vector>
using std::vector;
using std::pair;

class Pathfinder {
    vector<pair<Polygon, int>> obstacles;
    Point start, end;
    vector<Point> pts;
    void init_population(vector<Gene>&) const;
    void sort_population(vector<Gene>&) const;
    void cross_population(vector<Gene>&, double) const;
    void select_population(vector<Gene>&, size_t) const;
public:
    Pathfinder(const vector<pair<Polygon, int>>&, const Point&, const Point&);
    void set_start(const Point&);
    void set_end(const Point&);
    vector<Point> find_path(size_t, size_t, size_t, double, bool=false) const;
};

#endif
#ifndef GENE_HPP
#define GENE_HPP

#include "point.hpp"
#include "polygon.hpp"
#include <vector>
using std::vector;
using std::pair;

class Gene {
    void remove_duplicates();
public:
    size_t len = 0;
    vector<size_t> gene;
    double value = 0;

    Gene() = default;
    void init(size_t);
    void update_value(const vector<Point>&, const vector<pair<Polygon, int>>&, const Point&, const Point&);
    friend pair<Gene, Gene> one_point_cross(const Gene&, const Gene&);
    friend Gene one_point_mutate(const Gene&, size_t);
};

#endif
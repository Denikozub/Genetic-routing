#ifndef GENE_HPP
#define GENE_HPP

#include "point.hpp"
#include "polygon.hpp"
#include <vector>
using std::vector;
using std::pair;

class Gene {
public:
    Gene() = default;
    size_t len = 0;
    vector<size_t> gene;
    double value = 0;
    void init(size_t);
    void update_value(const vector<Point>&, const vector<pair<Polygon, int>>&, const Point&, const Point&);
    friend pair<Gene, Gene> cross(Gene&, Gene&);
};

#endif
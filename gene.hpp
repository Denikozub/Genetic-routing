#ifndef GENE_HPP
#define GENE_HPP

#include "point.hpp"
#include "polygon.hpp"
#include <vector>
using std::vector;
using std::pair;

class Gene {
public:
    Gene(size_t);
    size_t len;
    vector<size_t> gene;
    double value = 0;
    void update_value(const vector<Point>&, const vector<pair<Polygon, int>>&, const Point&, const Point&);
};

#endif
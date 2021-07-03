#ifndef GENE_HPP
#define GENE_HPP

#include "point.hpp"
#include <vector>
using std::vector;

class Gene {
    const vector<Point>* pts_p;
public:
    vector<int> gene;
    Gene(const vector<Point>*, int);
    double value(int mult);
};

#endif
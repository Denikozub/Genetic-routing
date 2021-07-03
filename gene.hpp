#ifndef GENE_HPP
#define GENE_HPP

#include "point.hpp"
#include <vector>
using std::vector;

class Gene {
    const vector<Point>* pts_p;
    const Point* start, * end;
public:
    int len;
    vector<int> gene;
    Gene(const vector<Point>*, const Point*, const Point*);
    double value(int mult);
};

#endif
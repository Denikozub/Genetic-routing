#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"
#include "segment.hpp"
#include <vector>
using std::vector;

class Iterator {
    vector<Point>::const_iterator pts_it;
public:
    Iterator(vector<Point>::const_iterator);
    Segment operator* () const;
    Iterator& operator++ ();
    bool operator== (const Iterator&);
    bool operator!= (const Iterator&);
};

class Polygon {
    vector<Point> pts;
public:
    Polygon(const vector<Point>&);
    Iterator begin();
    Iterator end();
};

#endif
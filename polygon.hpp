#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"
#include "segment.hpp"
#include <vector>
using std::vector;

class Iterator {
    vector<Point>::const_iterator pts_it, pts_end;
public:
    Iterator(vector<Point>::const_iterator, vector<Point>::const_iterator);
    const Segment operator* () const;
    Iterator& operator++ ();
    bool operator== (const Iterator&) const;
    bool operator!= (const Iterator&) const;
};

class Polygon {
public:
    vector<Point> pts;
    Polygon(const vector<Point>&);
    Iterator begin() const;
    Iterator end() const;
    bool is_node(const Point&) const;
    friend ostream& operator<< (ostream&, const Polygon&);
};

#endif
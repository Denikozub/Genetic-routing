/*
Polygon class:
- constructor takes vector of Point objects
- first and last elements of vector must be equal
- can be const-iterated over segments (returning Segment object)
*/

#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "point.hpp"
#include "segment.hpp"
#include <vector>

class Iterator {
    std::vector<Point>::const_iterator pts_it, pts_end;
public:
    Iterator(std::vector<Point>::const_iterator, std::vector<Point>::const_iterator);
    const Segment operator* () const;
    Iterator& operator++ ();
    bool operator== (const Iterator&) const;
    bool operator!= (const Iterator&) const;
};

class Polygon {
    std::vector<Point> pts;
public:
    Polygon(const std::vector<Point>&);
    const std::vector<Point>& geometry() const;
    Iterator begin() const;
    Iterator end() const;
    bool contains(const Point&) const;
    friend std::ostream& operator<< (std::ostream&, const Polygon&);
};

#endif
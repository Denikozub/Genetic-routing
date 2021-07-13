/*
Segment class:
constuctor takes Point and Point
crosses template method works with Polygon and Segment
currently only convex polygons are 
second parameter defines if touches and overlays are considered as an intersection
*/

#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "point.hpp"
#include <iostream>

class Segment {
    Point a, b;
public:
    Segment(const Point&, const Point&);
    double len();
    template <typename T> bool crosses(const T&, bool=false);
    friend std::ostream& operator<< (std::ostream&, const Segment&);
};

#endif
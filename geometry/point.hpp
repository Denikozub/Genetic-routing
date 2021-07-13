/*
Point class
- constructor takes x, y coordinates
- comparison done with 1e-8 precision
*/

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point {
public:
    double x, y;
    Point(double, double);
    friend bool operator== (const Point&, const Point&);
    friend bool operator!= (const Point&, const Point&);
    friend std::ostream& operator<< (std::ostream&, const Point&);
};

#endif

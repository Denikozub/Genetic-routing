#include "polygon.hpp"
#include <stdexcept>


/*=========================================== Iterator ==========================================*/

Iterator::Iterator(std::vector<Point>::const_iterator it,
    std::vector<Point>::const_iterator end) : pts_it(it), pts_end(end) {}

const Segment Iterator::operator* () const {
    return Segment(*pts_it, *(pts_it + 1));
}


Iterator& Iterator::operator++ () {
    if (pts_it == pts_end) {
        throw std::out_of_range("Iterator is already at end!");
    }
    ++pts_it;
    return *this;
}


bool Iterator::operator== (const Iterator& it) const {
    return pts_it == it.pts_it;
}


bool Iterator::operator!= (const Iterator& it) const {
    return !operator==(it);
}


/*=========================================== Polygon ===========================================*/

Polygon::Polygon(const std::vector<Point>& set_pts) : pts(set_pts) {
    if (pts.size() < 4) {
        throw std::invalid_argument("Polygon consists minimum of 3 points");
    }
    if (*(pts.begin()) != *(pts.end() - 1)) {
        throw std::invalid_argument("First and last points of polygon must be equal");
    }
}


const std::vector<Point>& Polygon::geometry() const {
    return pts;
}


Iterator Polygon::begin() const {
    return Iterator(pts.cbegin(), pts.cend() - 1);
}


Iterator Polygon::end() const {
    return Iterator(pts.cend() - 1, pts.cend() - 1);
}


bool Polygon::contains(const Point& point) const {
    for (const Point& p : pts) {
        if (p == point) {
            return true;
        }
    }
    return false;
}


std::ostream& operator<< (std::ostream& out, const Polygon& polygon) {
    out << "{ ";
    if (polygon.pts.size() >= 1) {
        out << polygon.pts[0];
    }
    for (auto i = polygon.pts.begin() + 1; i != polygon.pts.end(); ++i) {
        out << ", " << *i;
    }
    out << " }";
    return out;
}
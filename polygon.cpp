#include "polygon.hpp"
#include <stdexcept>
#include <algorithm>
using std::out_of_range;
using std::invalid_argument;
using std::find;

Iterator::Iterator(vector<Point>::const_iterator it,
    vector<Point>::const_iterator end) : pts_it(it), pts_end(end) {}

const Segment Iterator::operator* () const {
    return Segment(*pts_it, *(pts_it + 1));
}

Iterator& Iterator::operator++ () {
    if (pts_it == pts_end) {
        throw out_of_range("Iterator is already at end!");
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

Polygon::Polygon(const vector<Point>& set_pts) : pts(set_pts) {
    if (*pts.begin() != *(pts.end() - 1)) {
        throw invalid_argument("First and last points of polygon must be equal");
    }
}

Iterator Polygon::begin() const {
    return Iterator(pts.cbegin(), pts.cend() - 1);
}

Iterator Polygon::end() const {
    return Iterator(pts.cend() - 1, pts.cend() - 1);
}

bool Polygon::is_node(const Point& p) const {
    return find(pts.begin(), pts.end(), p) != pts.end();
}

ostream& operator<< (ostream& out, const Polygon& p) {
    out << "{ ";
    if (p.pts.size() >= 1) {
        out << p.pts[0];
    }
    for (auto i = p.pts.begin() + 1; i != p.pts.end(); ++i) {
        out << ", " << *i;
    }
    out << " }";
    return out;
}
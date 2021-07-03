#include "polygon.hpp"

Iterator::Iterator(vector<Point>::const_iterator it) : pts_it(it) {}

Segment Iterator::operator* () const {

}

Iterator& Iterator::operator++ () {
    ++pts_it;
}

bool Iterator::operator== (const Iterator& it) {
    return pts_it == it.pts_it;
}

bool Iterator::operator!= (const Iterator& it) {
    return !operator==(it);
}

Polygon::Polygon(const vector<Point>&) {

}

Iterator Polygon::begin() {

}

Iterator Polygon::end() {

}
#include "gene.hpp"
#include <cstdlib>
#include <ctime>

Gene::Gene(const vector<Point>* set_pts_p, const Point* set_start,
        const Point* set_end) : pts_p(set_pts_p), start(set_start), end(set_end) {
    std::srand(std::time(nullptr));
    len = rand() % (pts_p->size() + 1);
    gene = vector<int>(len);
    for (auto &i : gene) {
        i = rand() % (pts_p->size() + 1);
    }
}

double Gene::value(int mult) {
    return 0;
}
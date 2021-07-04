#include "gene.hpp"
#include <random>
#include <algorithm>
using std::random_device;
using std::generate;

void Gene::init(size_t point_number) {
    random_device r;
    len = r() % point_number;
    gene = vector<size_t>(len);
    generate(gene.begin(), gene.end(), [&] {return r() % point_number; });
}

void Gene::update_value(const vector<Point>& pts,
        const vector<pair<Polygon, int>>& obstacles, const Point& start, const Point& end) {
    double path_length = 0;
    Segment segment({ start, end });
    for (size_t i = 0; i < len + 1; i++) {
        if (len > 0 && i == 0) {
            segment = { start, pts[gene[0]] };
        } else if (len > 0 && i == len) {
            segment = { pts[gene[len - 1]], end };
        } else if (len > 0) {
            segment = { pts[gene[i - 1]], pts[gene[i]] };
        }
        double cross_value = segment.len();
        for (const auto& polygon_info : obstacles) {
            if (segment.crosses(polygon_info.first)) {
                cross_value += segment.len() * polygon_info.second;
            }
        }
        path_length += cross_value;
    }
    value = path_length;
}

pair<Gene, Gene> cross(Gene& parent1, Gene& parent2) {
    random_device r;
    size_t parent1_cross = parent1.len > 1 ? r() % (parent1.len - 1) + 1 : 0;
    size_t parent2_cross = parent2.len > 1 ? r() % (parent2.len - 1) + 1 : 0;
    Gene child1, child2;
    child1.gene = { parent1.gene.begin(), parent1.gene.begin() + parent1_cross };
    child2.gene = { parent2.gene.begin(), parent2.gene.begin() + parent2_cross };
    child1.gene.insert(child1.gene.end(), parent2.gene.begin() + parent2_cross, parent2.gene.end());
    child2.gene.insert(child2.gene.end(), parent1.gene.begin() + parent1_cross, parent1.gene.end());
    return { child1, child2 };
}
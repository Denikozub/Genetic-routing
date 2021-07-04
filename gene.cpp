#include "gene.hpp"
#include <random>
#include <algorithm>
using std::random_device;
using std::generate;

Gene::Gene(size_t point_number) {
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
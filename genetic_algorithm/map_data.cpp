#include "map_data.hpp"


MapData::MapData(const std::vector<std::pair<Polygon, int>>& set_obstacles, const Point& set_start,
    const Point& set_end) : obstacles(set_obstacles), start(set_start), end(set_end) {
    for (const auto& polygon : obstacles) {
        for (auto it = polygon.first.geometry().begin(); it != polygon.first.geometry().end() - 1; ++it) {
            pts.push_back(*it);
        }
    }
}


size_t MapData::get_range() const {
    return pts.size();
}


double MapData::fitness(const std::vector<size_t>& gene) const {
    double path_length = 0;
    Segment segment({ start, end });
    size_t len = gene.size();
    for (size_t i = 0; i < len + 1; i++) {
        if (len > 0 && i == 0) {
            segment = { start, pts[gene[0]] };
        }
        else if (len > 0 && i == len) {
            segment = { pts[gene[len - 1]], end };
        }
        else if (len > 0) {
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
    return path_length;
}
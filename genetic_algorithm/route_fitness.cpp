#include "route_fitness.hpp"


RouteFitness::RouteFitness(const std::vector<std::pair<Polygon, int>>& set_obstacles, const Point& set_start,
    const Point& set_end) : obstacles(set_obstacles), start(set_start), end(set_end) {
    for (const auto& polygon : obstacles) {
        for (auto it = polygon.first.geometry().begin(); it != polygon.first.geometry().end() - 1; ++it) {
            pts.push_back(*it);
        }
    }
}


void RouteFitness::set_start(const Point& set_start) {
    start = set_start;
}


void RouteFitness::set_end(const Point& set_end) {
    end = set_end;
}


double RouteFitness::eval(const Gene& ggg) const {
    double path_length = 0;
    Segment segment({ start, end });
    for (size_t i = 0; i < ggg.len + 1; i++) {
        if (ggg.len > 0 && i == 0) {
            segment = { start, pts[ggg.gene[0]] };
        }
        else if (ggg.len > 0 && i == ggg.len) {
            segment = { pts[ggg.gene[ggg.len - 1]], end };
        }
        else if (ggg.len > 0) {
            segment = { pts[ggg.gene[i - 1]], pts[ggg.gene[i]] };
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
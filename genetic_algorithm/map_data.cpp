#include "map_data.hpp"


MapData::MapData(const std::vector<std::pair<Polygon, int>>& set_obstacles, const Point& set_start,
    const Point& set_end) : obstacles(set_obstacles), start(set_start), end(set_end) {
    for (const auto& polygon : obstacles) {
        for (auto it = polygon.first.geometry().begin(); it != polygon.first.geometry().end() - 1; ++it) {
            pts.push_back(*it);
        }
    }
}
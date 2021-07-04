#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "polygon.hpp"
#include "point.hpp"
#include "pathfinder.hpp"
using namespace std;

int main()
{
    try {
        Polygon p1({ { 0, 0 }, { 0, 2 }, { 2, 2 }, { 2, 0 }, { 0, 0 } }),
                p2({ { 2, -1 }, { 2, -2 }, { -2, -2 }, { -2, -1 }, { 2, -1 } });
        vector<pair<Polygon, int>> obstacles({ {p1, 100}, {p2, 50} });
        Point start({ -1, -3 }), end({ 1, 3 });

        Pathfinder pa(obstacles, start, end);
        size_t population_size = 50;
        size_t epoch_number = 300;
        size_t valueless_epoch_number = 15;
        double cross_percent = 0.5;

        const auto& path = pa.find_path(population_size, epoch_number, valueless_epoch_number, cross_percent, true);
        cout << "Path found: " << start << " -> ";
        for (const auto& point : path) {
            cout << point << " -> ";
        }
        cout << end << endl;
    }
    catch (std::exception& e) {
        std::cerr << typeid(e).name() << ": " << e.what() << std::endl;
    }
    
    return 0;
}
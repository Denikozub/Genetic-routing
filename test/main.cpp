#include <iostream>
#include "../geometry/polygon.hpp"
#include "../geometry/point.hpp"
#include "../genetic_algorithm/genetic_algo.hpp"
#include "../genetic_data/map_data.hpp"
using namespace std;

int main()
{
    try {
        Polygon p1({ { 1, 0 }, { 2, 0 }, { 2, 4 }, { 1, 4 }, { 1, 0 } }),
                p2({ { 3, 3 }, { 3, 4 }, { 5, 4 }, { 5, 3 }, { 3, 3 } }),
                p3({ { 6, 0 }, { 7, 0 }, { 7, 4 }, { 6, 4 }, { 6, 0 } }),
                p4({ { 4, 5 }, { 4, 6 }, { 8, 6 }, { 8, 5 }, { 4, 5 } }),
                p5({ { 0, 5 }, { 0, 7 }, { 3, 7 }, { 3, 5 }, { 0, 5 } }),
                p6({ { 3, 7 }, { 3, 8 }, { 7, 8 }, { 7, 7 }, { 3, 7 } });
        vector<pair<Polygon, int>> obstacles({ {p1, 100}, {p2, 100}, {p3, 100}, {p4, 100}, {p5, 100}, {p6, 100} });
        Point start({ 4, 2 }), end({ 4, 10 });

        MapData data (obstacles, start, end);
        GeneticAlgo pathfinder;

        size_t population_size = 30;
        size_t epoch_number = 300;
        size_t valueless_epoch_number = 15;
        size_t preserve_best = 3;
        size_t preserve_worst = 3;
        double cross_percent = 0.5;
        double mutate_percent = 0.5;
        int cross_mode = 0;
        int mutate_mode = 0;
        int select_mode = 0;

        const auto& path = pathfinder.find_path(&data, population_size, epoch_number,
                valueless_epoch_number, preserve_best, preserve_worst, cross_mode,
                mutate_mode, select_mode, cross_percent, mutate_percent, true);
        cout << "Path found: " << start << " -> ";
        for (const auto& point : path) {
            cout << data.pts[point] << " -> ";
        }
        cout << end << endl;
    }
    catch (std::exception& e) {
        std::cerr << typeid(e).name() << ": " << e.what() << std::endl;
    }
    
    return 0;
}
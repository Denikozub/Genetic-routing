#include <iostream>
#include "polygon.hpp"
#include "segment.hpp"
#include "gene.hpp"
using namespace std;

int main()
{
    try {
        Polygon p1({ { 0, 0 }, { 0, 2 }, { 2, 2 }, { 2, 0 }, { 0, 0 } }), p2({ { 2, -1 }, { 2, -2 }, { -2, -2 }, { -2, -1 }, { 2, -1 } });
        vector<pair<Polygon, int>> obstacles({ {p1, 100}, {p2, 50} });
        vector<Point> pts = { { 0, 0 }, { 0, 2 }, { 2, 2 }, { 2, 0 }, { 2, -1 }, { 2, -2 }, { -2, -2 }, { -2, -1 } };
        vector<Gene> population (10, 1);
        for (auto& g : population) {
            g = Gene(pts.size());
            for (auto i : g.gene)
                cout << i << " ";
            g.update_value(pts, obstacles, { -1, -3 }, { 1, 3 });
            cout << endl << "value: " << g.value << endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << typeid(e).name() << ": " << e.what() << std::endl;
    }
    
    return 0;
}
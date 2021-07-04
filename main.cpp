#include <iostream>
#include "polygon.hpp"
#include "segment.hpp"
#include "gene.hpp"
using namespace std;

int main()
{
    try {
        Polygon p({ { 0, 0 }, { 0, 2 }, { 2, 2 }, { 2, 0 }, { 0, 0 } });
        vector<Point> pts = { { 0, 0 }, { 0, 2 }, { 2, 2 }, { 2, 0 }, { 0, 0 } };
    }
    catch (std::exception& e) {
        std::cerr << typeid(e).name() << ": " << e.what() << std::endl;
    }
    
    return 0;
}
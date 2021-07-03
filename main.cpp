#include <iostream>
#include "polygon.hpp"
#include "segment.hpp"
using namespace std;

int main()
{
    try {
        Polygon p({ { 0, 0 }, { 0, 2 }, { 2, 2 }, { 2, 0 }, { 0, 0 } });
        Segment s({ { -2, 0 }, { 2, 4 } });
        cout << s.crosses(p, true) << endl;
    }
    catch (std::exception& e) {
        std::cerr << typeid(e).name() << ": " << e.what() << std::endl;
    }
    
    return 0;
}
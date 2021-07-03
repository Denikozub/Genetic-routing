#include <iostream>
#include "segment.hpp"
using namespace std;

int main()
{
    Segment a({ 0, 0 }, { 0, 1 }), b({ 0, 1 }, { 1, 1 });

    cout << (a.crosses(b));
    return 0;
}
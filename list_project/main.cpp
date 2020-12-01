
#include "list.h"

bool is_even(int _arg) { return _arg % 2 == 0; }
bool sort_even(int _arg1, int _arg2) { return _arg1 % 3 < _arg2 % 4; }
#include <fstream>
bool ss(int x, int y) { return x > y; }
using namespace nonstl;

int main()
{
    std::ifstream in("input.txt");
    std::ofstream ou("output.txt");
    list lst{};
    int _res{};
    while (in >> _res && _res != EOF)
        lst.push_back(_res);
    
    lst.remove_if([](int x) {return x < 10000; });
    // or
    lst.remove_if(is_even);
    lst.print(ou, ' ');
    
    lst.sort([](int x, int y) {return x > y; });
    // or
    lst.sort(sort_even);
    /* and etc */
}
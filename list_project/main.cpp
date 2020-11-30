
#include <iostream>
#include "list.h"

//using namespace lists;

#include <list>



bool is_even(int _arg) { return _arg % 2 == 0; }

template <class function>
bool is_smf(int _x, function func)
{
    return func(_x);
}
#include <fstream>
bool ss(int x, int y) { return x > y; }
#include <algorithm> 
int main()
{
    list::list l;
    l.push_back(777);
    l.push_back(333);
    l.push_back(555);
    l.push_back(111);
    
    //TODO: erase + sort + "="
     
    l.print(std::cout, " ");
    std::cout << "\n";

    //int p = 10;
    //std::cout << is_smf(p, [](int _x) { return _x < 10; });
    l.remove_if([](int x) { return (x < 333); });
    l.print(std::cout, " ");
    //std::cout << "here'";
    
    
    
}
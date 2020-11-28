
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
int main()
{
    list::list l;
    l.push_back(222);
    l.push_back(333);
    l.push_back(444);
    
    l.insert_before(l.head->next, 111);
    
    l.print(std::cout,'\n');
    
    //int p = 10;
    //std::cout << is_smf(p, [](int _x) { return _x < 10; });
    //x.remove_if([](int x) { return (x > 5); });
    //std::cout << "here'";
    
    
    
}
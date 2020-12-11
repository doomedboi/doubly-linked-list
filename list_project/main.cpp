
#include "list.h"
#include <fstream>
bool is_even(int _arg) { return _arg % 2 == 0; }

using namespace nonstl;
#include <iostream>
using std::cout;
int main()
{      
    auto print = [&](list<int> lst) { lst.print(cout, ' '); cout << '\n'; };
    // 1 3 4 2 5 6 8 7 9 10 11 13 12 14 15 0
    std::ifstream in("input.txt");
    nonstl::list<int> lst;
    for (auto x : lst)
        cout << x;
    int _input{};
    while (in >> _input && _input != in.eof())
        lst.push_back(_input);
   
    print(lst);
    cout << "list's size: " << lst.size() << '\n';
    
    cout << lst.front() << ' ' << lst.back() << '\n';
    for (auto it = std::begin(lst); it != std::end(lst); ++it)
        lst.insert_before(it, 666);
    print(lst);

    lst.remove(666);
    print(lst);

    lst.sort([](int x, int y) {return x > y; });
    print(lst);
    //let's remove all elemets greatest than sup
    const int sup = 10;
    lst.remove_if([&](int _Elem) {return _Elem > sup; });
    print(lst);

    lst.push_front(-1);
    lst.pop_back();
    print(lst);
    lst.pop_front();
    print(lst);
    //find and delete 5 by iterator
    lst.erase( lst.find(5) );
    print(lst);
    
    //let's change head
    lst.front() = -666;
    print(lst);
    lst.insert(std::begin(lst), -777);
    print(lst);
    // we can remove some vector of elements like this:
    lst.erase(lst.find(8), lst.find(3));
    print(lst);  

    list<int> lst2 = lst;
    
    lst.clear();
    lst.print(cout, ' ');
    print(lst);
    
    print(lst2);
    lst2.remove_after(std::begin(lst2));
    lst2.remove_before(std::begin(lst2));
    lst2.remove_before(lst2.find(1));
    print(lst2);

    //remove even elents
    lst2.remove_if(is_even);
    print(lst2);

    //remove list
    lst2.clear();
    print(lst2);
}

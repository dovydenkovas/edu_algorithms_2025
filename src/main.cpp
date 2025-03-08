#include <iostream>
#include "algo/list.h"
#include "algo/sort.h"
// #include "algo/ustring.h"

list<double> foo() {
   list<double> lst;

   for (int i = 0; i < 100; i++)
     lst.push_back(i);

   return lst;
 }

int main()
{
    list<double> lst(foo());

    for (int i = 0; i < 25; ++i)
      lst.erase(++lst.begin());

    for (auto &a : lst) {
      std::cout << a << " ";
    }
    std::cout << std::endl;

    list<double> lst2;
    lst2 = lst;
    lst2.insert(++lst.begin(), 2.0);

    sort(lst2.begin(), lst2.end());
    for (auto &a : lst2) {
       std::cout << a << " ";
    }
    std::cout << std::endl;

    std::cout << lst2.size() << std::endl;
}

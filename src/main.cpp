#include <iostream>
#include "algo/vector.h"


int main() 
{
  vector<double> arr;
  
  for (int i=0; i<100; i++) {
    arr.push_back(i);
    std::cout << arr[i] << std::endl;
  }
}

/*
  The right way to overload operator<< and operator>>
  Alexandr Poltavsky
*/

#include <vector>
#include <iostream>

template<class T0, class T1> std::vector<T0>& operator<<( std::vector<T0>& vec, T1&& value ) {
  vec.push_back( std::forward<T1>( value ) );
  return vec;
}

template<class T0, class T1> std::vector<T0>& operator>>( std::vector<T0>& vec, T1& value ) {
  value = vec.back();
  vec.pop_back();
  return vec;
}

int main() {
  std::vector<int> v{1,2,3};
  
  for(auto i : v) std::cout << i <<" ";
  std::cout << std::endl;

  v << 4 << 5;

  for(auto i : v) std::cout << i <<" ";
  std::cout << std::endl;
  
  int i{}; 
  v >> i;
  std::cout << "i = " << i << std::endl;
  
  for(auto i : v) std::cout << i <<" ";
  std::cout << std::endl;
  
}


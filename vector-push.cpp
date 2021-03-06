/*
  That's how operator<< and >> should've been overloaded. 
  Alexandr Poltavsky
*/

#include <vector>
#include <iostream>

template<class T0, class T1> auto& operator<<( std::vector<T0>& vec, T1&& value ) {
  vec.push_back( std::forward<T1>( value ) );
  return vec;
}

template<class T0, class T1> auto& operator>>( std::vector<T0>& vec, T1& value ) {
  value = vec.back();
  vec.pop_back();
  return vec;
}

int main() {

  std::vector<int> v{1,2,3};
  int i{};
  
  for(auto i : v) std::cout << i <<" ";
  std::cout << std::endl;

  v << 4 << 5;

  for(auto i : v) std::cout << i <<" ";
  std::cout << std::endl;
  
  v >> i;
  std::cout << "i = " << i << std::endl;
  
  for(auto i : v) std::cout << i <<" ";
  std::cout << std::endl;
  
}


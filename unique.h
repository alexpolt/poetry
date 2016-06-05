/*

unique wrapper
Blog post: http://alexpolt.github.io/unique.html

Alexandr Poltavsky
*/


template<typename T0> struct unique {

  unique( T0 handle ) : handle{ std::move( handle ) } { }
  
  unique( unique const &) = delete; //no copy
  unique& operator=( unique const & ) = delete; //no assignment
  
  unique( unique&& r ) : handle{} { //moving is okay
    using std::swap;
    swap( handle, r.handle );
  }
  
  unique& operator=( unique&& r ) {
    ~unique();
    using std::swap;
    swap( handle, r.handle );
    return *this;
  }
  
  ~unique(); //specialize to get desired behaviour
  
  T0 handle;
}


/*
example:

template<> unique<FILE*>::~unique() {
  fclose( handle );
}

*/


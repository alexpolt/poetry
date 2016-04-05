/*

Macro kung fu to have code like this:

#define FAILED( args ) ...

$checkall( FAILED, f1(), f2(), f3() ) 

Alexandr Poltavsky

*/


//number of arguments to a function macro 
#define $numargs_( $1, $2, $3, N, ... ) N
#define $numargs( ... ) $numargs_( __VA_ARGS__, 3, 2, 1 )

#define $paste_( $0, $1 ) $0 ## $1
#define $paste( $0, $1 ) $paste_( $0, $1 )

//maximum is 3 arguments
//easy to get more
#define $check1( $macro, $1 ) $macro( $1 );
#define $check2( $macro, $1, $2 ) $check1( $macro, $1 ) $check1( $macro, $2 )
#define $check3( $macro, $1, $2, $3 ) $check2( $macro, $1, $2 ) $check1( $macro, $3 )

//using $numargs and $paste to get the correct macro name
#define $checkall_( $macro, $check, ... ) $check( $macro, __VA_ARGS__ )
#define $checkall( $macro, ... ) $checkall_( $macro, $paste( $check, $numargs(__VA_ARGS__) ), __VA_ARGS__ )



/*

Print-format a 32-bit float by exploiting exponent.
Blog post: http://alexpolt.github.io/print-fp.html

Alexandr Poltavsky

*/

#include <cstdio>
#include <cmath>

int main() {

    union {
        float d;
        int u;
    };

    d = -0.00594;

    printf("%.10f\n", d); //original numer

    bool minus = u >> 31; //store sign
    u = u & ~(1 << 31); //clear sign
    double exp = (u >> 23) - 127; //extract exponent
    double exp10 = exp / log2( 10.0 ); //compute base-10

    //adjust the number
    u = (u & ~(0xFF << 23)) | (127 << 23);
    double d2 = double(d) * pow( 10.0, exp10 - int(exp10) ); 
    if( d2 >= 10.0 ) { d2 = d2 / 10.0; exp10+=1.0; }
    if( d2 < 1.0 ) { d2 = d2 * 10.0; exp10-=1.0; }

    //print sign
    if( minus ) printf("-");

    //print integer part
    int i = int( d2 );
    printf("%.1d.", i);
    d2 = d2 - i;

    //print the rest
    int digits = 10; 

    while( digits-- ) { 
        d2 = d2 * 10.0;
        int i = int( d2 );
        printf("%.1d", i);
        d2 = d2 - i;
    }

    //print exponent part
    printf("e%d", int(exp10));

}


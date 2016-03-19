/*

Print-format a 32-bit float by exploiting exponent
Blog post: http://alexpolt.github.io/print-fp.html

Alexandr Poltavsky

*/

#include <cstdio>
#include <cmath>

void print_fp( float number, int digits ) {
    union {
        float d;
        int u;
    };
    
    d = number;

    //deal with sign
    bool minus = u >> 31; 
    u = u & ~(1 << 31); 
    
    //calculate base-10 exponent
    double exp = (u >> 23) - 127;
    double exp10 = exp / log2( 10.0 );

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

    //print fractional part
    while( digits-- ) { 
        d2 = d2 * 10.0;
        int i = int( d2 );
        printf("%.1d", i);
        d2 = d2 - i;
    }

    //print exponent part
    printf("e%d\n", int(exp10));
}

int main() {

    double d;

    //the two doubles below are special, in that a float can't distinguish between them
    //taken from Bruce Dawson post "Float Precision–From Zero to 100+ Digits"

    d = 8.589973e9;
    printf("%.10f\n", d);
    print_fp( d , 10 );

    d = 8.589974e9;
    printf("%.10f\n", d);
    print_fp( d , 10 );

}


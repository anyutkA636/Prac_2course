// 6_14_A
/* Описать в виде структуры
a) точку на плоскости;
b) цветную точку на плоскости;
c) комплексное число;
d) рациональное число.
*/
#include <stdio.h>

// a)
struct usual_point {  
    int x; 
    int y;
};

// b)
enum colour {red, blue, green};
struct colour_point {  
    usual_point p;
    colour c;
};

// c)
struct complex_point {  
    int a; // (a + i * b)
    int b; 
};

// d)
struct rational_point {  
    int a; 
    unsigned short b; 
};


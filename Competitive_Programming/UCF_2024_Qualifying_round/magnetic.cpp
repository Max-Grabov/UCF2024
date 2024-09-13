#include <iostream>
#include <math.h>
using namespace std;
int main(){
    double s1, s2, x1, x2, y1, y2;
    cin >> s1 >> x1 >> y1 >> s2 >> x2 >> y2;
    y2 -= y1;
    x2 -= x1;
    printf("%0.6lf",(((s1*x2*x2 + s1*y2*y2)/(s2-s1)) + (x2*x2*s1*s1/((s2-s1)*(s2-s1))) + (y2*y2*s1*s1/((s2-s1)*(s2-s1))))*3.1415926535397932384626);
}
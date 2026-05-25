#include <stdio.h>

int main() {
    double v, t, s;

    printf("Enter v: ");
    scanf("%lf", &v);

    printf("Enter t: ");
    scanf("%lf", &t);

    s = 2 * t * v;

    printf("S = %.2lf\n", s);

    return 0;
}

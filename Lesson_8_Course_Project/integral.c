#include "integral.h"
#include <math.h>

double integral(double (*f)(double), double a, double b, double eps) {
    int n = 2;
    double h = (b - a) / n;
    double current = 0.0, prev;
    do {
        prev = current;
        current = 0.0;
        for (int i = 0; i < n; i++) {
            double x0 = a + i * h;
            double x1 = x0 + h;
            current += (f(x0) + 4 * f((x0 + x1)/2) + f(x1)) * h / 6;
        }
        n *= 2;
        h /= 2;
    } while (fabs(current - prev) > eps);
    return current;
}

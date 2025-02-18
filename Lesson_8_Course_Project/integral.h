#ifndef INTEGRAL_H
#define INTEGRAL_H

// Вычисление интеграла функции f(x) на [a,b] методом Симпсона
// с адаптивным выбором шага до достижения точности eps
double integral(
    double (*f)(double), // Интегрируемая функция
    double a,            // Нижний предел
    double b,            // Верхний предел
    double eps           // Точность
);

#endif

#ifndef ROOT_H
#define ROOT_H

// Поиск корня уравнения f(x) = g(x) на [a,b] методом Ньютона
// Возвращает найденный корень или NAN при ошибке
double root(
    double (*f)(double),   // Функция f(x)
    double (*g)(double),   // Функция g(x)
    double (*df)(double),  // Производная f'(x)
    double (*dg)(double),  // Производная g'(x)
    double a,              // Левая граница отрезка
    double b,              // Правая граница отрезка
    double eps,            // Точность
    int *iter_count        // Счётчик итераций (выходной параметр)
);

#endif

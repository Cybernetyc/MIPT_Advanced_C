#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"
#include "root.h"
#include "integral.h"
#include "tests.h"

#define MAX_POINTS 6

///< Структура для хранения точек пересечения
typedef struct {
  double x;          ///< Координата X пересечения
  int f_id1;         ///< ID первой функции
  int f_id2;         ///< ID второй функции
  int iterations;    ///< Количество итераций для поиска
} IntersectionPoint;

int compare(const void *a, const void *b) {  ///< Функция сравнения для сортировки точек
  const IntersectionPoint *pa = (const IntersectionPoint *)a;
  const IntersectionPoint *pb = (const IntersectionPoint *)b;
  return (pa->x > pb->x) - (pa->x < pb->x);
  ///< Сравнение по координате X
}

double max3(double a, double b, double c) {  ///< Максимальное из трёх
  double max = a;
  if (b > max) max = b;
  if (c > max) max = c;
  return max;
}

double min3(double a, double b, double c) {  ///< Минимальное из трёх
  double min = a;
  if (b < min) min = b;
  if (c < min) min = c;
  return min;
}

void print_help() {                         ///< Функция вывода справки
  printf("Usage: program [options]\n");
  printf("Options:\n");
  printf("  --help          Display this help message\n");
  printf("  --test          Run tests\n");
  printf("  --print-roots   Print intersection points\n");
  printf("  --print-iters   Print iteration counts\n");
}

///< Основная логика программы

int main(int argc, char **argv)
{
  ///< 1. Обработка аргументов командной строки
  int print_roots = 0;
  int print_iters = 0;
  int test_mode = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      print_help();
      return 0;
    } else if (strcmp(argv[i], "--test") == 0) {
      test_mode = 1;
    } else if (strcmp(argv[i], "--print-roots") == 0) {
      print_roots = 1;
    } else if (strcmp(argv[i], "--print-iters") == 0) {
      print_iters = 1;
    }
  }

  if (test_mode) {
    run_tests();
    return 0;
  }

  ///< 2. Поиск точек пересечений функций
  const double eps1 = 1e-6;
  const double eps2 = 1e-6;

  IntersectionPoint points[MAX_POINTS];
  int num_points = 0;

  ///< Поиск пересечений между функцией f1 и f2
  int iter;
  double x = root(f1, f2, df1, df2, 3.0, 4.0, eps1, &iter);
  if (!isnan(x)) {
    points[num_points++] = (IntersectionPoint){x, 1, 2, iter};
  }

  ///< Поиск пересечений между функцией f1 и f3
  x = root(f1, f3, df1, df3, 0.5, 1.5, eps1, &iter);
  if (!isnan(x)) {
    points[num_points++] = (IntersectionPoint){x, 1, 3, iter};
  }

  ///< Поиск пересечений между функцией f2 и f3
  x = root(f2, f3, df2, df3, 2.0, 3.0, eps1, &iter);
  if (!isnan(x)) {
    points[num_points++] = (IntersectionPoint){x, 2, 3, iter};
  }

  ///< 3. Сортировка точек по Х
  qsort(points, num_points, sizeof(IntersectionPoint), compare);

  if (print_roots) {
    printf("Intersection points:\n");
    for (int i = 0; i < num_points; i++) {
      printf("x = %lf (f%d and f%d)\n", points[i].x, points[i].f_id1, points[i].f_id2);
    }
  }

  if (print_iters) {
    printf("Iteration counts:\n");
    for (int i = 0; i < num_points; i++) {
      printf("%d iterations for x = %lf\n", points[i].iterations, points[i].x);
    }
  }


  ///< 4. Вычисление площади между кривыми
  double total_area = 0.0;
  for (int i = 0; i < num_points - 1; i++) {
    double a = points[i].x;
    double b = points[i+1].x;
    double mid = (a + b) / 2;
    double v1 = f1(mid);
    double v2 = f2(mid);
    double v3 = f3(mid);

    double upper = max3(v1, v2, v3);
    double lower = min3(v1, v2, v3);

    double (*upper_func)(double) = NULL;
    double (*lower_func)(double) = NULL;

    if (v1 == upper) upper_func = f1;
    else if (v2 == upper) upper_func = f2;
    else if (v3 == upper) upper_func = f3;

    if (v1 == lower) lower_func = f1;
    else if (v2 == lower) lower_func = f2;
    else if (v3 == lower) lower_func = f3;

    if (upper_func && lower_func) {
      double area = integral(upper_func, a, b, eps2) - integral(lower_func, a, b, eps2);
      total_area += fabs(area);
    }
  }
  ///< 5. Вывод результатов
  printf("Total area: %lf\n", total_area);

  return 0;
}
#include "functions.h"
#include <math.h>

double f1(double x) ///< f1(x) = 0.6x + 3 (Уравнение прямой линии)
{
  return 0.6 * x + 3;
}

double df1(double x) ///< Производная f1'(x) = 0.6 (параметр x не используется)
{
   (void)x;          ///< Явное указание на неиспользование параметра
   return 0.6;
}

double f2(double x)  ///< f2(x) = (x-2)^3 - 1  (Кубическая парабола)
{
  return pow(x - 2, 3) - 1;
}


double df2(double x)  ///< Производная f2: 3(x-2)^2
 {
  return 3 * pow(x - 2, 2);
}

double f3(double x)   ///< f3(x) = 3 / x (гипербола)
{
  return 3 / x;
}

double df3(double x)  ///< Производная f3: -3/x^2
{
  return -3 / (x * x);
}

#include <stdio.h>
#include <math.h>
#include "tests.h"
#include "functions.h"
#include "root.h"
#include "integral.h"

static void test_root(void)   ///< Тестирование функции root() на известном пересечении f1 и f3
 {                        ///< Проверка совпадения с аналитическим решением
    int iter;
    double x = root(f1, f3, df1, df3, 0.5, 1.5, 1e-6, &iter);
    double expected = (sqrt(16.2) - 3) / 1.2; // Аналитическое решение
    if (fabs(x - expected) < 1e-6) {
        printf("Test root(f1, f3) passed.\n");
    } else {
        printf("Test root(f1, f3) failed. Got %lf, expected %lf\n", x, expected);
    }
}

static void test_integral(void) ///< Тестирование функции integral() на линейной функции
 {
    double result = integral(f1, 0, 1, 1e-6);
    if (fabs(result - 3.3) < 1e-6) {            ///< Сравнение с точным значением интеграла
        printf("Test integral(f1) passed.\n");
    } else {
        printf("Test integral(f1) failed. Got %lf, expected 3.3\n", result);
    }
}

void run_tests(void) ///< Запуск всех тестов
 {
    test_root();
    test_integral();
}

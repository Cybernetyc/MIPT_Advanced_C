/* Сколько раз встречается максимум.
 * На стандартном потоке ввода задаётся натуральное число N (N > 0),
 * после которого следует последовательность из N целых чисел.
 * На стандартный поток вывода напечатайте, сколько раз в этой последовательности встречается максимум.
 * Указание: использовать массивы запрещается.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int N = 0;                ///< Количество чисел
  scanf("%d", &N);

  int counter_for_max = 1;        ///< Одно число но будет максимальным
  int first_var_for_compare = 0;  ///< Первая переменная для временного хранения
  int second_var_for_compare = 0; ///< Вторая переменная для временного хранения
  for (int i = 0; i < N; ++i) {
    if (i == 0) {
      scanf("%d", &first_var_for_compare); ///< Считали первое число единожды
      continue;
    }

    scanf("%d", &second_var_for_compare);  ///< Если дошло, то читаем второе число

    if (second_var_for_compare > first_var_for_compare){ ///< Если нашли число больше
      counter_for_max = 1;                               ///< Счётчик максимальных в 1
      first_var_for_compare = second_var_for_compare;    ///< Перезаписали числа
      continue;
    }

    if (first_var_for_compare == second_var_for_compare)  ///< Если нашли такое же
      counter_for_max++;                                  ///< Увеличили счётчик

  }

  printf("%d", counter_for_max);

  return EXIT_SUCCESS;
}
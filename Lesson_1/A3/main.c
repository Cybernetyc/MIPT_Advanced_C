/**
 * На вход программе подается беззнаковое 32-битное целое число N и натуральное число K
 * (1 ≤ K ≤ 31).
 * Требуется взять K младших битов числа N и вывести полученное таким образом число.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
  uint32_t N = 0;
  uint16_t K = 0;
  scanf("%i%hu", &N, &K);

  uint32_t mask_1 = 1; ///< Маска для установления бита
  uint32_t var = 0;    ///< Переменная для значения после наложения маски

  for (int i = 0; i < K; ++i) {
    var |= (1 << i);
  }

  var = var & N;
  printf("%u", var); ///< Вывели число в поток
  return EXIT_SUCCESS;
}
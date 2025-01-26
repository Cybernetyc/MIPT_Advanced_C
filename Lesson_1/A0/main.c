#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int N = 0;                ///< Переменная согласно условия
  scanf("%d", &N);

  int max = 0;
  int var = 0;
  int counter_for_max = 0;
  for (int i = 0; i < N; ++i) {

    scanf("%d", &var);
    if (var > max) {
      max = var;
      counter_for_max = 1;
      continue;
    }

    if(var == max)
      counter_for_max++;
  }

  printf("%d", counter_for_max);

  return EXIT_SUCCESS;
}
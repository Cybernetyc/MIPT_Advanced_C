/**
 * @file main.c
 * @brief Поиск длины наибольшего префикса первой строки, который является суффиксом второй строки.
 *
 * @author Черкашин Дмитрий
 */

#include <stdio.h>
#include <string.h>

/**
 * @brief Функция для поиска длины наибольшего префикса первой строки, который является суффиксом второй строки.
 *
 * @param[in] str1 Строка 1
 * @param[in] str2 Строка 2
 *
 * @return Длина наибольшего префикса первой строки, который является суффиксом второй строки. Если не найдено соответствие, возвращается 0.
 */
int find_prefix_suffix_length(const char *str1, const char *str2) {
  /**
   * @brief Длины строк str1 и str2
   */
  int len1 = strlen(str1);
  int len2 = strlen(str2);

  /**
   * @brief Максимальная возможная длина префикса/суффикса
   */
  int max_len = (len1 < len2) ? len1 : len2;

  /**
   * @brief Цикл по возможным длинам префиксов/суффиксов
   */
  for (int l = max_len; l > 0; l--) {
    /**
     * @brief Сравниваем префикс str1 длины l с суффиксом str2 длины l
     */
    if (strncmp(str1, str2 + len2 - l, l) == 0) {
      return l;
    }
  }

  /**
   * @brief Если не найдено соответствие, возвращаем 0
   */
  return 0;
}

/**
 * @brief Функция для поиска длины наибольшего суффикса первой строки, который является префиксом второй строки.
 *
 * @param[in] str1 Строка 1
 * @param[in] str2 Строка 2
 *
 * @return Длина наибольшего суффикса первой строки, который является префиксом второй строки. Если не найдено соответствие, возвращается 0.
 */
int find_suffix_prefix_length(const char *str1, const char *str2) {
  /**
   * @brief Длины строк str1 и str2
   */
  int len1 = strlen(str1);
  int len2 = strlen(str2);

  /**
   * @brief Максимальная возможная длина префикса/суффикса
   */
  int max_len = (len1 < len2) ? len1 : len2;

  /**
   * @brief Цикл по возможным длинам префиксов/суффиксов
   */
  for (int l = max_len; l > 0; l--) {
    /**
     * @brief Сравниваем суффикс str1 длины l с префиксом str2 длины l
     */
    if (strncmp(str1 + len1 - l, str2, l) == 0) {
      return l;
    }
  }

  /**
   * @brief Если не найдено соответствие, возвращаем 0
   */
  return 0;
}

/**
 * @brief Основная функция программы.
 *
 * @return 0, если программа завершена успешно.
 */
int main() {
  /**
   * @brief Хранилища строк str1 и str2
   */
  char str1[10005], str2[10005];

  /**
   * @brief Считываем две строки
   */
  scanf("%s", str1);
  scanf("%s", str2);

  /**
   * @brief Находим длины префикс-суффикса и суффикс-префикса
   */
  int prefix_suffix_len = find_prefix_suffix_length(str1, str2);
  int suffix_prefix_len = find_suffix_prefix_length(str1, str2);

  /**
   * @brief Выводим результат
   */
  printf("%d %d\n", prefix_suffix_len, suffix_prefix_len);

  return 0;
}
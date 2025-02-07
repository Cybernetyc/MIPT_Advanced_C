

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @def MAX_STACK_SIZE
 * @brief Максимальная размерность стека (10000 элементов)
 */
#define MAX_STACK_SIZE 10000

/**
 * @var stack
 * @brief Стек для хранения чисел.
 *
 * @size MAX_STACK_SIZE
 */
int stack[MAX_STACK_SIZE];

/**
 * @var top
 * @brief Текущий индекс вершины стека (инициализируется -1).
 */
int top = -1;

/**
 * @fn push(int value)
 * @brief Добавляет значение в стек.
 *
 * @param[in] value Значение для добавления в стек.
 *
 * @return Ничего не возвращает, но может вызывать исключения при переполнении стека.
 */
void push(int value) {
  /**
   * @brief Проверка на переполнение стека
   */
  if (top >= MAX_STACK_SIZE - 1) {
    exit(1); // Переполнение стека
  }

  /**
   * @brief Добавление значения в стек
   */
  stack[++top] = value;
}

/**
 * @fn pop()
 * @brief Извлекает значение из вершины стека.
 *
 * @return Значение, которое было на вершине стека перед вызовом функции.
 *
 * @throws 1 (exit) при недостатке элементов в стеке.
 */
int pop() {
  /**
   * @brief Проверка на отсутствие элементов в стеке
   */
  if (top < 0) {
    exit(1); // Недостаточно элементов
  }

  /**
   * @brief Извлечение значения из вершины стека
   */
  return stack[top--];
}

/**
 * @fn is_operator(const char *token)
 * @brief Проверяет, является ли токен оператором.
 *
 * @param[in] token Токен для проверки.
 *
 * @return true, если токен является оператором; false в противном случае.
 */
int is_operator(const char *token) {
  /**
   * @brief Сравнение токена с поддерживаемыми операторами
   */
  return (strcmp(token, "+") == 0 ||
          strcmp(token, "-") == 0 ||
          strcmp(token, "*") == 0 ||
          strcmp(token, "/") == 0);
}

/**
 * @fn main()
 * @brief Основная функция программы.
 *
 * @return 0 при успешном завершении программы.
 */
int main() {
  /**
   * @var input
   * @brief Хранилище вводимой строки.
   */
  char input[100000];

  /**
   * @brief Чтение всей строки из стандартного входа
   */
  fgets(input, sizeof(input), stdin); // Чтение всей строки

  /**
   * @var dot
   * @brief Указатель на точку в строке.
   */
  char *dot = strchr(input, '.');

  /**
   * @brief Удаление точки в конце строки
   */
  if (dot != NULL) *dot = '\0';

  /**
   * @var token
   * @brief Токен из строки.
   */
  char *token = strtok(input, " ");

  /**
   * @brief Разбиение строки на токены и выполнение операций
   */
  while (token != NULL) {
    /**
     * @brief Проверка, является ли токен числом
     */
    if (isdigit(token[0])) {
      /**
       * @brief Добавление числа в стек
       */
      push(atoi(token));
    } else if (is_operator(token)) {
      /**
       * @brief Выполнение операции с числами из стека
       */
      int b = pop();
      int a = pop();

      switch (token[0]) {
        case '+':
          push(a + b); break;
        case '-':
          push(a - b); break;
        case '*':
          push(a * b); break;
        case '/':
          /**
           * @brief Проверка на деление на ноль
           */
          if (b == 0) exit(1); // Деление на ноль

          push(a / b);
          break;
      }
    }

    token = strtok(NULL, " ");
  }

  /**
   * @brief Вывод результата из стека
   */
  printf("%d\n", pop());

  return 0;
}
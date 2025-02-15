#include <stdio.h>
#include <stdlib.h>

void btUpView(tree *root) {
  if (!root) return;

  // Структура для узла очереди BFS
  typedef struct {
    tree *node;
    int hd; // Горизонтальное расстояние
  } QueueItem;

  QueueItem *queue = malloc(10000 * sizeof(QueueItem));
  int front = 0, rear = 0;
  int min_hd = 0, max_hd = 0;

  // Первый проход: определяем диапазон горизонтальных расстояний
  queue[rear++] = (QueueItem){root, 0};
  while (front < rear) {
    QueueItem current = queue[front++];
    if (current.hd < min_hd) min_hd = current.hd;
    if (current.hd > max_hd) max_hd = current.hd;

    if (current.node->left)
      queue[rear++] = (QueueItem){current.node->left, current.hd - 1};
    if (current.node->right)
      queue[rear++] = (QueueItem){current.node->right, current.hd + 1};
  }

  // Второй проход: сохраняем первые узлы для каждого HD
  int size = max_hd - min_hd + 1;
  int *visited = calloc(size, sizeof(int));
  int *result = malloc(size * sizeof(int));

  front = rear = 0;
  queue[rear++] = (QueueItem){root, 0};
  while (front < rear) {
    QueueItem current = queue[front++];
    int adjusted_hd = current.hd - min_hd; // Нормализуем HD

    if (!visited[adjusted_hd]) {
      visited[adjusted_hd] = 1;
      result[adjusted_hd] = current.node->key;
    }

    if (current.node->left)
      queue[rear++] = (QueueItem){current.node->left, current.hd - 1};
    if (current.node->right)
      queue[rear++] = (QueueItem){current.node->right, current.hd + 1};
  }

  // Вывод результата
  for (int i = 0; i < size; i++) {
    if (visited[i]) printf("%d ", result[i]);
  }
  printf("\n");

  free(queue);
  free(visited);
  free(result);
}
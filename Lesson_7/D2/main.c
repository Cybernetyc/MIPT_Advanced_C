#include <stdlib.h>

// Структура tree УЖЕ ОПРЕДЕЛЕНА в системе:

// Вспомогательная функция для поиска узла по ключу
static tree* findNode(tree* node, int key) {
  if (!node) return NULL;
  if (node->key == key) return node;
  tree* left = findNode(node->left, key);
  return left ? left : findNode(node->right, key);
}

// Основная функция поиска брата
tree* findBrother(tree *root, int key) {
  tree* target = findNode(root, key);
  if (!target || !target->parent) return NULL; // Нет узла или это корень

  tree* parent = target->parent;
  return (parent->left == target) ? parent->right : parent->left;
}
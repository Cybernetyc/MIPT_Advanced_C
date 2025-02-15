#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
    char word[20];
    struct list *next;
};


// Добавляет новое слово в конец списка
struct list* add_to_list(struct list *tail, const char *word) {
    struct list *new_node = (struct list*)malloc(sizeof(struct list));
    strcpy(new_node->word, word);
    new_node->next = NULL;
    if (tail) tail->next = new_node;
    return new_node;
}

// Меняет местами содержимое двух узлов
void swap_elements(struct list *a, struct list *b) {
    char temp[20];
    strcpy(temp, a->word);
    strcpy(a->word, b->word);
    strcpy(b->word, temp);
}

// Выводит элементы списка через пробел
void print_list(struct list *head) {
    while (head) {
        printf("%s", head->word);
        if (head->next) printf(" ");
        head = head->next;
    }
    printf("\n");
}

// Рекурсивно удаляет список
void delete_list(struct list *head) {
    if (!head) return;
    delete_list(head->next);
    free(head);
}

// Сортировка списка пузырьком
void sort_list(struct list *head) {
    int swapped;
    struct list *ptr;
    struct list *last = NULL;

    if (!head) return;

    do {
        swapped = 0;
        ptr = head;
        while (ptr->next != last) {
            if (strcmp(ptr->word, ptr->next->word) > 0) {
                swap_elements(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);
}

int main() {
    char input[10000];
    fgets(input, 10000, stdin);

    // Удаляем точку и перенос строки
    char *p = strchr(input, '.');
    if (p) *p = '\0';
    p = strchr(input, '\n');
    if (p) *p = '\0';

    struct list *head = NULL, *tail = NULL;
    char *word = strtok(input, " ");

    // Строим список
    while (word) {
        if (!head) {
            head = add_to_list(NULL, word);
            tail = head;
        } else {
            tail = add_to_list(tail, word);
        }
        word = strtok(NULL, " ");
    }

    // Сортируем и выводим
    sort_list(head);
    print_list(head);
    delete_list(head);
    return 0;
}
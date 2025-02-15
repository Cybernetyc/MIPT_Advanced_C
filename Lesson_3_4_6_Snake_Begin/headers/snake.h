#pragma once
#include "config.h"

typedef enum {live, death} health_t;
typedef enum {left, up, right, down} vector_t;

typedef struct {
  int x;
  int y;
  char symb;
} body_part_t;

typedef struct{
  vector_t vector;
  int body_lenght;
  body_part_t body[(WEIGHT-2)*(HEIGHT-2)];
}snake_t;

vector_t control (char c, vector_t direction);
int check_for_death (snake_t * snake);
void init_snake (snake_t * snake);
void charge_python (snake_t * snake);
void print_snake (snake_t * snake, int display);
void change_direction(snake_t * snake , vector_t direction);
void snake_boost(snake_t * snake);
int is_empty_space (snake_t * snake, int x, int y);
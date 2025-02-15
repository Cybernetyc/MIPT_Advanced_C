#pragma once
#include "snake.h"

typedef struct{
  int x_coord;
  int y_coord;
  char symb;
  int live_time;
} food_t;

void print_food (food_t * food , int display);

void place_food (food_t * food, snake_t * snake);

void rotting_food (food_t * food);




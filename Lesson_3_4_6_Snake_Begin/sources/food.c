#include <stdlib.h>
#include <ncurses.h>
#include "config.h"
#include "food.h"
#include "snake.h"


void print_food (food_t * food , int display)
{
  if (display) {
    mvaddch(food->y_coord, food->x_coord, food->symb );
  } else {
    mvaddch(food->y_coord, food->x_coord, ' ');
  }
}

void place_food (food_t * food, snake_t * snake)
{
  do
  {
    food->x_coord = (rand() % (WEIGHT - 3)) + 1;
    food->y_coord = (rand() % (HEIGHT - 3)) + 1;
  }
  while (is_empty_space(snake, food->x_coord, food->y_coord) == 0);

  food->symb = '+';
  food->live_time = 50;
  print_food(food, 1);
}

void rotting_food (food_t * food)
{
  print_food(food, 0);
  food->x_coord = 0;
  food->y_coord = 0;
}



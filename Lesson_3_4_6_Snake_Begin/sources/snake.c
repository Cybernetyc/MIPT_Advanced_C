#include "snake.h"
#include "config.h"
#include <ncurses.h>

void snake_boost(snake_t * snake)
{
  snake -> body[snake->body_lenght].x = snake -> body[snake->body_lenght-1].x;
  snake -> body[snake->body_lenght].y = snake -> body[snake->body_lenght-1].y;
  snake -> body[snake->body_lenght].symb = 'o';
  snake -> body_lenght ++;
  print_snake(snake, 1);
}

int check_for_death(snake_t * snake)
{
  int x_head = snake->body[0].x;
  int y_head = snake->body[0].y;
  if ((x_head < 1) || (x_head > WEIGHT-1)) ///< Collision with left or right wall
    return death;
  if ((y_head < 1) || (y_head > HEIGHT-1)) ///< Collision with top or bottom wall
    return death;
  for(int i = 1; i < snake->body_lenght; ++i)
    if ((x_head == snake->body[i].x) && (y_head == snake->body[i].y)) ///< Collision with a part of the snake's body
      return death;
  return live;
}
vector_t control(char key, vector_t direction)
{
  switch (key) {
    case 's':
    case 'S': ///< Key 's' or 'S' for down direction
      return down;
    case 'w':
    case 'W': ///< Key 'w' or 'W' for up direction
      return up;
    case 'a':
    case 'A': ///< Key 'a' or 'A' for left direction
      return left;
    case 'd':
    case 'D': ///< Key 'd' or 'D' for right direction
      return right;
  }
  return direction;
}

void change_direction(snake_t * snake , vector_t direction)
{
  if ((snake->vector + direction) % 2 != 0) ///< Check for even number of cells
    snake->vector = direction; ///< Update the direction of the snake
}

void print_snake (snake_t * snake, int display)
{

  for (int i=(snake->body_lenght - 1); i >= 0; --i){

    if (display)
      mvaddch(snake->body[i].y , snake->body[i].x , snake->body[i].symb ); ///< Print the symbol
    else
      mvaddch(snake->body[i].y , snake->body[i].x , ' '); ///< Hide the symbol
  }
}

void init_snake (snake_t * snake)
{
  snake -> vector = left;
  snake -> body_lenght = 2;

  for(int i = 0; i < (snake -> body_lenght); i++){
    if (i == 0){ ///< First cell (head) is at the center of the screen
      snake -> body[i].x = (WEIGHT/2-2);
      snake -> body[i].y = (HEIGHT/2-2);
      snake -> body[i].symb = '@';
      continue; ///< Move to the next iteration
    }
    snake -> body[i].x = snake -> body[i-1].x+1;
    snake -> body[i].y = snake -> body[i-1].y;
    snake -> body[i].symb = 'o';
  }
  print_snake(snake, 1);
}

void charge_python (snake_t * snake)
{
  print_snake(snake, 0);
  for (int i = snake -> body_lenght ; i > 0 ; --i){
    snake->body[i].x = snake->body[i-1].x;
    snake->body[i].y = snake->body[i-1].y;
  }
  switch (snake-> vector) {
    case left: ///< If the snake is moving left, decrement x-coordinate
      snake->body[0].x -= 1;
      break;
    case right: ///< If the snake is moving right, increment x-coordinate
      snake->body[0].x += 1;
      break;
    case up: ///< If the snake is moving up, decrement y-coordinate
      snake->body[0].y -= 1;
      break;
    case down: ///< If the snake is moving down, increment y-coordinate
      snake->body[0].y += 1;
      break;
  }
  print_snake(snake, 1);
}

int is_empty_space (snake_t * snake, int x, int y)
{
  for(int i = 0; i < snake->body_lenght; ++i)
    if ((snake->body[i].x == x) && (snake->body[i].y == y))
      return 0;

  return 1;
}

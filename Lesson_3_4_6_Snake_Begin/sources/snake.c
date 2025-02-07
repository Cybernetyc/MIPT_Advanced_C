#include "snake.h"
#include "config.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>


/**
 * @brief Boosts the snake.
 *
 * This function increases the length of the snake's body by 1 and moves the last element as the new head.
 *
 * @param snake A pointer to the snake structure.
 */
void snake_boost(snake_t * snake)
{
  /**
   * @brief The new head of the snake gets the coordinates of the last element in the body.
   */
  snake -> body[snake->body_lenght].x = snake -> body[snake->body_lenght-1].x;
  snake -> body[snake->body_lenght].y = snake -> body[snake->body_lenght-1].y;

  /**
   * @brief The new head of the snake becomes a symbol 'o'.
   */
  snake -> body[snake->body_lenght].symb = 'o';

  /**
   * @brief The length of the snake's body increases by 1.
   */
  snake -> body_lenght ++;

  /**
   * @brief Prints the snake in the terminal with the updated head position.
   */
  print_snake(snake, 1);
}


/**
 * @brief Checks for death.
 *
 * This function checks whether the head of the snake has collided with a wall or its own body.
 *
 * @param snake A pointer to the snake structure.
 *
 * @return An integer indicating the status:
 *         - death: The snake has died (i.e., it has hit a wall or itself).
 *         - live: The snake is still alive.
 */
int check_for_death(snake_t * snake)
{
  /**
   * @brief Gets the coordinates of the head of the snake.
   */
  int x_head = snake->body[0].x;
  int y_head = snake->body[0].y;

  /**
   * @brief Checks for collision with walls.
   */
  if ((x_head < 1) || (x_head > WEIGHT-1)) ///< Collision with left or right wall
    return death;
  if ((y_head < 1) || (y_head > HEIGHT-1)) ///< Collision with top or bottom wall
    return death;

  /**
   * @brief Checks for collision with the snake's own body.
   */
  for(int i = 1; i < snake->body_lenght; ++i)
    if ((x_head == snake->body[i].x) && (y_head == snake->body[i].y)) ///< Collision with a part of the snake's body
      return death;

  /**
   * @brief If no collision is detected, the snake is still alive.
   */
  return live;
}



/**
 * @brief Controls the movement of the snake.
 *
 * This function takes a key input and returns the corresponding direction to move the snake.
 *
 * @param key The key input by the user (case-insensitive).
 * @param direction The current direction of the snake.
 *
 * @return A vector indicating the new direction of the snake:
 *         - up, down, left or right.
 */
vector_t control(char key, vector_t direction)
{
  /**
   * @brief Uses a switch statement to determine the direction based on the input key.
   */
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

  /**
   * @brief If the input key is not recognized, returns the current direction.
   */
  return direction;
}

/**
 * @brief Changes the direction of the snake.
 *
 * This function updates the direction of the snake to a new value if it is different from the current direction
 * and if moving in that direction would result in an even number of cells.
 *
 * @param snake A pointer to the snake structure.
 * @param direction The new direction of the snake.
 */
void change_direction(snake_t * snake , vector_t direction)
{
  /**
   * @brief Checks if moving in the new direction would result in an even number of cells.
   */
  if ((snake->vector + direction) % 2 != 0) ///< Check for even number of cells
    snake->vector = direction; ///< Update the direction of the snake
}

/**
 * @brief Prints the snake on the screen.
 *
 * This function prints the current state of the snake's body on the terminal screen, hiding or showing it as specified.
 *
 * @param snake A pointer to the snake structure.
 * @param display Whether to show (1) or hide (0) the snake.
 */
void print_snake (snake_t * snake, int display)
{
  /**
   * @brief Iterates over the body of the snake in reverse order.
   */
  for (int i=(snake->body_lenght - 1); i >= 0; --i){
    /**
     * @brief Prints the symbol representing each cell in the snake's body, hiding it if display is 0.
     */
    if (display)
      mvaddch(snake->body[i].y , snake->body[i].x , snake->body[i].symb ); ///< Print the symbol
    else
      mvaddch(snake->body[i].y , snake->body[i].x , ' '); ///< Hide the symbol
  }
}


/**
 * @brief Initializes the snake.
 *
 * This function sets up the initial state of the snake, including its direction, length and position on the screen.
 *
 * @param snake A pointer to the snake structure.
 */
void init_snake (snake_t * snake)
{
  /**
   * @brief Sets the initial direction of the snake as left.
   */
  snake -> vector = left;

  /**
   * @brief Sets the initial length of the snake to 2 cells.
   */
  snake -> body_lenght = 2;

  /**
   * @brief Initializes the position and symbol of each cell in the snake's body.
   */
  for(int i = 0; i < (snake -> body_lenght); i++){
    if (i == 0){ ///< First cell (head) is at the center of the screen
      /**
       * @brief Sets the x-coordinate of the head as (WEIGHT/2-2).
       */
      snake -> body[i].x = (WEIGHT/2-2);

      /**
       * @brief Sets the y-coordinate of the head as (HEIGHT/2-2).
       */
      snake -> body[i].y = (HEIGHT/2-2);

      /**
       * @brief Sets the symbol representing the head as '@'.
       */
      snake -> body[i].symb = '@';

      continue; ///< Move to the next iteration
    }

    /**
     * @brief Sets the position of each subsequent cell in the snake's body based on the previous cell.
     */
    snake -> body[i].x = snake -> body[i-1].x+1;
    snake -> body[i].y = snake -> body[i-1].y;

    /**
     * @brief Sets the symbol representing each cell in the snake's body as 'o'.
     */
    snake -> body[i].symb = 'o';
  }

  /**
   * @brief Prints the initial state of the snake on the screen.
   */
  print_snake(snake, 1);
}

/**
 * @brief Charges the snake.
 *
 * This function simulates a move of the snake on the screen by updating its position and then printing it.
 *
 * @param snake A pointer to the snake structure.
 */
void charge_python (snake_t * snake)
{
  /**
   * @brief Hides the current state of the snake on the screen.
   */
  print_snake(snake, 0);

  /**
   * @brief Updates the position of each cell in the snake's body by shifting it one cell to the left.
   */
  for (int i = snake -> body_lenght ; i > 0 ; --i){
    /**
     * @brief Copies the position of the previous cell to the current cell.
     */
    snake->body[i].x = snake->body[i-1].x;
    snake->body[i].y = snake->body[i-1].y;
  }

  /**
   * @brief Updates the position of the head (first cell) based on the current direction of the snake.
   */
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

  /**
   * @brief Prints the updated state of the snake on the screen.
   */
  print_snake(snake, 1);
}

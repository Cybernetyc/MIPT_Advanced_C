#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "config.h"
#include "food.h"

/**
 * @brief Prints the food on the screen.
 *
 * This function prints or hides the current state of the food based on the display parameter.
 *
 * @param food A pointer to the food structure.
 * @param display Whether to show (1) or hide (0) the food.
 */
void print_food (food_t * food , int display)
{
  if (display) {
    /**
     * @brief Prints the symbol representing the food at its current position on the screen.
     */
    mvaddch(food->y_coord, food->x_coord, food->symb );
  } else {
    /**
     * @brief Hides the food by printing a space at its current position.
     */
    mvaddch(food->y_coord, food->x_coord, ' ');
  }
}

/**
 * @brief Places new food on the screen.
 *
 * This function randomly generates a position for the food within the boundaries of the screen and updates its state.
 *
 * @param food A pointer to the food structure.
 */
void place_food (food_t * food)
{
  /**
   * @brief Randomly selects an x-coordinate for the food, ensuring it is at least 1 cell away from any edge.
   */
  food->x_coord = (rand() % (WEIGHT - 3))+1;

  /**
   * @brief Randomly selects a y-coordinate for the food, ensuring it is at least 1 cell away from any edge.
   */
  food->y_coord = (rand() % (HEIGHT - 3))+1;

  /**
   * @brief Sets the symbol representing the food to '+'.
   */
  food->symb = '+';

  /**
   * @brief Initializes the live time of the food to a maximum value.
   */
  food->live_time = 35;

  /**
   * @brief Prints the newly placed food on the screen.
   */
  print_food(food, 1);
}

/**
 * @brief Simulates the rotting process of the food.
 *
 * This function updates the state of the food by hiding it and resetting its position to the origin (0,0).
 *
 * @param food A pointer to the food structure.
 */
void rotting_food (food_t * food)
{
  /**
   * @brief Hides the food on the screen.
   */
  print_food(food, 0);

  /**
   * @brief Resets the x-coordinate of the food to 0.
   */
  food->x_coord = 0;

  /**
   * @brief Resets the y-coordinate of the food to 0.
   */
  food->y_coord = 0;
}



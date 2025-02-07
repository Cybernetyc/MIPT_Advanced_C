/**
 * @file food.h
 *
 * @brief Structure and functions for the food in the game.
 */

#pragma once

/**
 * @typedef food_t
 * @brief A structure representing a piece of food on the screen.
 */
typedef struct{
/**
 * @var x_coord
 * @brief The x-coordinate of the food's position on the screen.
 */
int x_coord;

/**
 * @var y_coord
 * @brief The y-coordinate of the food's position on the screen.
 */
int y_coord;

/**
 * @var symb
 * @brief The symbol used to represent the food on the screen.
 */
char symb;

/**
 * @var live_time
 * @brief The remaining time before the food rots.
 */
int live_time;
} food_t;

/**
 * @brief Prints the food on the screen.
 *
 * This function prints or hides the current state of the food based on the display parameter.
 *
 * @param food A pointer to a food structure.
 * @param display Whether to show (1) or hide (0) the food.
 */
void print_food (food_t * food , int display);

/**
 * @brief Places new food on the screen.
 *
 * This function randomly generates a position for the food within the boundaries of the screen and updates its state.
 *
 * @param food A pointer to a food structure.
 */
void place_food (food_t * food);

/**
 * @brief Simulates the rotting process of the food.
 *
 * This function updates the state of the food by hiding it and resetting its position to the origin (0,0).
 *
 * @param food A pointer to a food structure.
 */
void rotting_food (food_t * food);


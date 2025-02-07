/**
 * @file snake.h
 *
 * @brief Structure and functions for the snake in the game.
 */

#pragma once
#include "config.h"

/**
 * @typedef health_t
 * @brief An enumeration representing the state of a cell in the game: alive or dead.
 */
typedef enum {live, death} health_t;

/**
 * @typedef vector_t
 * @brief An enumeration representing the direction of movement for the snake.
 */
typedef enum {left, up, right, down} vector_t;

/**
 * @typedef body_part_t
 * @brief A structure representing a single part of the snake's body.
 */
typedef struct {
/**
 * @var x
 * @brief The x-coordinate of the cell occupied by this part of the snake's body.
 */
int x;

/**
 * @var y
 * @brief The y-coordinate of the cell occupied by this part of the snake's body.
 */
int y;

/**
 * @var symb
 * @brief The symbol used to represent this part of the snake's body on the screen.
 */
char symb;
} body_part_t;

/**
 * @typedef snake_t
 * @brief A structure representing the entire snake in the game, including its direction and length.
 */
typedef struct{
/**
 * @var vector
 * @brief The current direction of movement for the snake.
 */
vector_t vector;

/**
 * @var body_lenght
 * @brief The total number of cells occupied by the snake's body.
 */
int body_lenght;

/**
 * @var body
 * @brief An array of structures representing each part of the snake's body, in order from head to tail.
 */
body_part_t body[(WEIGHT-2)*(HEIGHT-2)];
}snake_t;

/**
 * @brief Updates the direction of movement for the snake based on user input.
 *
 * This function takes into account the current direction and any new direction entered by the user,
 * returning a value indicating whether the direction has been successfully updated.
 *
 * @param c The user's input character, which may be an arrow key or other valid direction.
 * @param direction The current direction of movement for the snake.
 * @return A vector_t value representing the updated direction of movement for the snake.
 */
vector_t control (char c, vector_t direction);

/**
 * @brief Checks if a collision with the snake's body has occurred, causing death.
 *
 * This function iterates over each part of the snake's body and checks for collisions with the game field or the snake itself,
 * returning a value indicating whether a collision has been detected.
 *
 * @param snake A pointer to the snake structure.
 * @return An integer value (1) if a collision has occurred, or 0 otherwise.
 */
int check_for_death (snake_t * snake);

/**
 * @brief Initializes the snake's properties and position at the start of the game.
 *
 * This function sets up the snake with its initial direction, length, and body parts,
 * ready for the game to begin.
 *
 * @param snake A pointer to the snake structure.
 */
void init_snake (snake_t * snake);

/**
 * @brief Updates the snake's position and properties based on user input.
 *
 * This function uses the control() function to determine the new direction of movement for the snake,
 * then updates its body parts accordingly, taking care not to overlap with itself or escape the game field.
 *
 * @param snake A pointer to the snake structure.
 */
void charge_python (snake_t * snake);

/**
 * @brief Prints the snake on the screen in its current state.
 *
 * This function uses the print_snake() function to display each part of the snake's body on the screen,
 * taking into account whether the snake should be displayed or hidden.
 *
 * @param snake A pointer to the snake structure.
 * @param display A boolean value indicating whether the snake should be visible (1) or hidden (0).
 */
void print_snake (snake_t * snake, int display);

/**
 * @brief Updates the snake's direction based on user input and changes its position accordingly.
 *
 * This function uses the control() function to determine the new direction of movement for the snake,
 * then updates its body parts accordingly, taking care not to overlap with itself or escape the game field.
 *
 * @param snake A pointer to the snake structure.
 * @param direction The new direction of movement for the snake.
 */
void change_direction(snake_t * snake , vector_t direction);

/**
 * @brief Boosts the length of the snake by one cell, allowing it to grow and move faster.
 *
 * This function updates the snake's body parts accordingly, taking care not to overlap with itself or escape the game field.
 *
 * @param snake A pointer to the snake structure.
 */
void snake_boost(snake_t * snake);
/**
 * @file field_of_game.h
 *
 * @brief Function for initializing the game field.
 */

#pragma once

/**
 * @brief Initializes the game field with the given width and height.
 *
 * This function sets up the ncurses library to display a window of the specified size, ready for drawing the game.
 *
 * @param w The desired width of the game field in characters.
 * @param h The desired height of the game field in characters.
 */
void init_field_of_game(int w, int h);
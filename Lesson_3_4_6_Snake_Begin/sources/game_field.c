#include "config.h"
#include "game_field.h"
#include "ncurses.h"

/**
 * @file game_field.c
 *
 * @brief Function for initializing the game field.
 */

void init_field_of_game(int w, int h)
{
  // Draw horizontal line across top of field
  for (int x = 0; x <= w; x++) {
    /**
     * @brief Prints a '-' character at the specified position on the screen,
     * creating a horizontal line along the top of the game field.
     */
    mvaddch(0, x, '-');
  }

  // Draw vertical lines along left and right edges
  for (int y = 1; y < h - 1; y++) { // Exclude last row to avoid duplicates
    /**
     * @brief Prints a '|' character at the specified position on the screen,
     * creating a vertical line along the left edge of the game field.
     */
    mvaddch(y, 0, '|');

    /**
     * @brief Prints another '|' character at the same height but different x-coordinate,
     * creating a vertical line along the right edge of the game field.
     */
    mvaddch(y, w - 1, '|'); // Exclude last column to avoid duplicates
  }

  // Draw horizontal line across bottom of field
  for (int x = 0; x <= w; x++) {
    /**
     * @brief Prints a '-' character at the specified position on the screen,
     * completing the horizontal line along the bottom of the game field.
     */
    mvaddch(h - 1, x, '-');
  }
}

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "game_field.h"
#include "snake.h"
#include "food.h"
#include "time.h"

/**
 * @file main.c
 *
 * @brief The entry point for the game program.
 */

#include "config.h"
#include "game_field.h"
#include "ncurses.h"

/**
 * @brief The main function of the program, where the game loop is implemented.
 *
 * This function initializes the ncurses library and sets up the game field,
 * then enters a loop that continues until the user quits or the game ends.
 *
 * @return EXIT_SUCCESS on successful execution of the program.
 */
int main (void)
{

  // Initialize the ncurses library to handle input/output operations
  initscr();

  // Clear the screen and prepare for drawing the game field
  clear();

  // Disable line buffering and echo input characters to the terminal
  raw();
  noecho();

  // Hide the cursor on the screen
  curs_set(0);

  // Set a timeout of 0 seconds, meaning that getch() will block indefinitely
  timeout(0);

  // Seed the random number generator with the current time for generating random numbers
  srand(time(NULL));

  // Initialize the game field and draw it on the screen
  init_field_of_game(WEIGHT, HEIGHT);

  // Create a new snake structure to hold its properties and position
  snake_t snake = {0};

  // Initialize the snake's properties and position at the start of the game
  init_snake (&snake);

  // Create a new food structure to hold its properties and position
  food_t food = {0};

  // Place a piece of food on the field at a random location
  place_food(&food);

  // Set the initial direction of movement for the snake
  vector_t direction = snake.vector;

  // Record the start time of the current frame
  clock_t begin = clock();

  // Keep track of the player's score
  int score = 0;

  // Print a message indicating that the game can be quit by pressing 'q'
  mvprintw(HEIGHT+3,(WEIGHT/2 - 9),"PUSH Q or q TO QUIT");

  // Print a message giving credit to the game developer
  mvprintw(HEIGHT+5,(WEIGHT/2 - 14),"Develop by Dmitry Cherkashin");

  // Refresh the display to show the initial state of the game field and messages
  refresh();

  // Main game loop: wait for user to quit or game to end
  while(1){

    // Print an indication of the player's current score on the screen
    mvprintw(HEIGHT+4,(WEIGHT/2-4),"SCORE %d", score);

    // Get a character from the input buffer (blocking call)
    char key = getch();

      // If the user presses 'q' or 'Q', exit the game loop and quit the program
      if (key == 'q' || key == 'Q')
        break;

      // Update the direction of movement for the snake based on user input
      direction = control(key, direction);

      // If it's been too long since the last update, skip to the next frame
      if((double)(clock() - begin) / CLOCKS_PER_SEC * 10 < DELAY )
        continue;

      // Record the start time of the current frame
      begin = clock();

      // Update the position and properties of the snake based on its direction of movement
      change_direction(&snake , direction);

      // Move the python forward by one cell, taking care not to overlap with itself or escape the game field
      charge_python(&snake);

      // Refresh the display to show the updated state of the game field and messages
      refresh();

      // If the snake has collided with the food piece, increase its length and score, place a new food piece on the field
      if ((snake.body[0].x == food.x_coord) && (snake.body[0].y == food.y_coord)){
        rotting_food(&food);
        snake_boost(&snake);
        place_food(&food);
        score += 100;
        refresh();
      }

      // If the time limit for a piece of food has expired, remove it and place a new one on the field
      if (--food.live_time == 0){
        rotting_food(&food);
        food.live_time = 35;
        place_food (&food);
        refresh();
      }

      // Check whether the game is over (i.e., the snake has collided with its own body)
      if (check_for_death(&snake) == death){
        mvprintw(HEIGHT+1,(WEIGHT/2-4),"YOU LOSE!");

        // Print a message indicating that the user can quit the program by pressing any key
        mvprintw(HEIGHT+3,(WEIGHT/2-9),"PUSH ANY KEY TO QUIT");

        // Refresh the display to show the final state of the game field and messages
        refresh();

        // Wait for the user to press a key before quitting the program
        getchar();
        break;
      }

      // Refresh the display to show the updated state of the game field and messages
      refresh();
  }

  // Clean up ncurses library resources before exiting program
  endwin();

  return EXIT_SUCCESS;
}

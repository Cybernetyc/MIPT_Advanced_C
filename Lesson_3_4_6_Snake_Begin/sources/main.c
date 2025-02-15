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


  place_food(&food, &snake);


  vector_t direction = snake.vector;


  clock_t begin = clock();


  int score = 0;


  mvprintw(HEIGHT+3,(WEIGHT/2 - 9),"PUSH Q or q TO QUIT");


  mvprintw(HEIGHT+5,(WEIGHT/2 - 14),"Develop by Dmitry Cherkashin");


  refresh();


  while(1){


    mvprintw(HEIGHT+4,(WEIGHT/2-4),"SCORE %d", score);


    char key = getch();


      if (key == 'q' || key == 'Q')
        break;


      direction = control(key, direction);


      if((double)(clock() - begin) / CLOCKS_PER_SEC * 10 < DELAY )
        continue;


      begin = clock();


      change_direction(&snake , direction);


      charge_python(&snake);


      refresh();


      if ((snake.body[0].x == food.x_coord) && (snake.body[0].y == food.y_coord)){
        rotting_food(&food);
        snake_boost(&snake);
        place_food(&food, &snake);
        score += 100;
        refresh();
      }


      if (--food.live_time == 0){
        rotting_food(&food);
        food.live_time = 35;
        place_food (&food, &snake);
        refresh();
      }


      if (check_for_death(&snake) == death){
        mvprintw(HEIGHT+1,(WEIGHT/2-4),"YOU LOSE!");


        mvprintw(HEIGHT+3,(WEIGHT/2-9),"PUSH ANY KEY TO QUIT");


        refresh();


        getchar();
        break;
      }


      refresh();
  }


  endwin();

  return EXIT_SUCCESS;
}

#ifndef HEADER_FILE
#define HEADER_FILE

//includes
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

//defines
#define SCREEN_COLOR al_map_rgb(8, 38, 8)
#define SNAKE_COLOR al_map_rgb(255,255,255)
#define FOOD_COLOR al_map_rgb(252, 138, 32)
#define SCREEN_H 600
#define SCREEN_W 800


//structures
typedef struct cell* pointer; //pointer to a cell of the snake (cell of the linked list)

typedef struct cell{
  int x; //x coordinate of the cell: from 1 to 27
  int y; //y coordinate of the cell: from 1 to 29
  int dir; //cell direction: 1-RIGHT, 2-UP, 3-LEFT, 4-down
  pointer next; //pointer to the next cell
} cell;

typedef struct snake{
  pointer head; //pointer to the head of the snake (has no values)
  pointer tail; //pointer to the tail of the snake (has values)
} snake;


//function prototypes
void drawSquare(int, int, ALLEGRO_COLOR); //receives coordinates and color and draws a square inside game rectangle
snake* newSnake(void); //creates a new snake with 4 cells plus the tail and returns the pointer to the snake
void setupScreen(); //creates screen default structures
void drawGrid(); //draws a grid in the game rectangle
void drawSnake(snake*); //receives a pointer to the snake and draws it
void updateSnake(snake *); //receives a pointer to the snake and updates it based on "dir" variable of its cells
void freeSnake(snake *); // deallocates the memory allocated for the snake and its cells


#endif

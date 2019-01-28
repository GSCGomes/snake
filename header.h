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

//function prototypes

void drawSquare(int, int, ALLEGRO_COLOR);
void setupScreen();
void drawGrid();

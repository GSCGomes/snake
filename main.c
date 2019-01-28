#include "header.h"

int main(void){

  const float FPS = 5;

  al_init();

  ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);
  ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
  ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();

  al_register_event_source(eventQueue, al_get_timer_event_source(timer));

  setupScreen();

  snake* S = newSnake();
  drawSquare(23,4,FOOD_COLOR);
  drawSnake(S);
  al_flip_display();

  al_rest(4.0);
  al_destroy_display(display);

  freeSnake(S);
  return 0;
}

void setupScreen(){

  al_clear_to_color(SCREEN_COLOR);

  al_init_font_addon();
  al_init_ttf_addon();

  al_draw_text(
    al_load_ttf_font("Comfortaa-Regular.ttf",42,ALLEGRO_TTF_NO_KERNING),
    al_map_rgb(255,255,255),578,10,ALLEGRO_ALIGN_LEFT,"jogo da"
  ); //writes "jogo da" on screen
  al_draw_text(
    al_load_ttf_font("Comfortaa-Regular.ttf",42,ALLEGRO_TTF_NO_KERNING),
    al_map_rgb(255,255,255),568,60,ALLEGRO_ALIGN_LEFT,"cobrinha"
  ); //writes "cobrinha" on screen
  al_draw_rectangle(10,10,SCREEN_W - 249,SCREEN_H - 9, al_map_rgb(255,255,255), 1);
}

void drawSquare(int x, int y, ALLEGRO_COLOR color){

  if(x <= 27 && x > 0 && y <=29 && y > 0) //if coordinates are inside game rectangle
    al_draw_filled_rectangle(11 + x*19, 11 + y*19, 29 + x*19, 29 + y*19, color);
}

void drawGrid(){

  setupScreen();
  for(int j = 10; j < 590; j += 20){
    for(int i = 10; i < 550; i+= 20){
      al_draw_rectangle(i,j,i+20,j+20,al_map_rgb(131, 160, 135),1);
    }
  }
}

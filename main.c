#include "header.h"

int main(void){

  const float FPS = 10;

  time_t t;
  srand((unsigned) time(&t));
  //initializes random number generator (for the food creation)

  al_init();
  al_install_keyboard();

  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

  eventQueue = al_create_event_queue();
  display = al_create_display(SCREEN_W, SCREEN_H);
  timer = al_create_timer(1.0 / FPS);

  al_register_event_source(eventQueue, al_get_keyboard_event_source());
  al_register_event_source(eventQueue, al_get_timer_event_source(timer));
  al_register_event_source(eventQueue, al_get_display_event_source(display));

  int foodX = 23;
  int foodY = 4;

  setupScreen();
  snake* S = newSnake();
  //drawGrid();
  drawSquare(foodX,foodY,FOOD_COLOR);

  drawSnake(S);
  al_flip_display();

  al_start_timer(timer);

  while(1){

    ALLEGRO_EVENT event;
    al_wait_for_event(eventQueue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER){

      updateSnake(S);
      if(collision(S))
           break;
      if(snakeAte(foodX,foodY,S)){
        updateScore();
        do{
          foodX = (rand() % 26) + 1;
          foodY = (rand() % 28) + 1;
        }while(isOverlapped(foodX,foodY,S));
        drawSquare(foodX,foodY,FOOD_COLOR);

        push(S);
      }

      al_flip_display();
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
      switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_RIGHT:
          if(S->dir == 3) break;
          else {S->dir = 1; break;}
        case ALLEGRO_KEY_UP:
          if(S->dir == 4) break;
          else {S->dir = 2; break;}
        case ALLEGRO_KEY_LEFT:
          if(S->dir == 1) break;
          else {S->dir = 3; break;}
        case ALLEGRO_KEY_DOWN:
          if(S->dir == 2) break;
          else {S->dir = 4; break;}
      }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      break;
    }
  }

  al_rest(0.2);
  al_destroy_timer(timer);
  al_destroy_display(display);

  freeSnake(S);

  if(overlap == 1)
    printf("%d overlap\n",overlap);
  else printf("%d overlaps\n",overlap);

  printf("score = %d\n",score);

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

  if(x <= 27 && x > 0 && y <= 29 && y > 0){ //if coordinates are inside game rectangle
    x--;y--;
    al_draw_filled_rectangle(11 + x*20, 11 + y*20, 29 + x*20, 29 + y*20, color);
  }
}

void drawGrid(){

  setupScreen();
  for(int j = 10; j < 590; j += 20){
    for(int i = 10; i < 550; i+= 20){
      al_draw_rectangle(i,j,i+20,j+20,al_map_rgb(131, 160, 135),1);
    }
  }
}

void updateScore(){

  al_draw_filled_rectangle(613,170,738,240,SCREEN_COLOR);
  score++;
  al_draw_textf(
    al_load_ttf_font("Comfortaa-Regular.ttf",60,ALLEGRO_TTF_NO_KERNING),
    al_map_rgb(255,255,255),670,170,ALLEGRO_ALIGN_CENTER,"%d",score);

}

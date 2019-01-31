#include "header.h"

int main(void){

  const float FPS = 10;
  int first = 1;

  time_t t;
  srand((unsigned) time(&t));
  //initializes random number generator (for the food creation)

  al_init();
  al_install_keyboard();

  ALLEGRO_DISPLAY *display = NULL;
  display = al_create_display(SCREEN_W, SCREEN_H);

  INIT: while(0){};
   //label

  //declaration of allegro variables
  ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
  ALLEGRO_EVENT event;
  ALLEGRO_TIMER *timer = NULL;

  //initialization of allegro variables
  eventQueue = al_create_event_queue();
  timer = al_create_timer(1.0 / FPS);

  //registration of allegro event sources
  al_register_event_source(eventQueue, al_get_keyboard_event_source());
  al_register_event_source(eventQueue, al_get_display_event_source(display));
  al_register_event_source(eventQueue, al_get_timer_event_source(timer));

  int foodX = 23;
  int foodY = 4;
  int endGame = 0;
  int trueDir = 1; //tells true valid direction of the snake (used to fix a bug)

  setupScreen();
  snake* S = newSnake();
  //drawGrid;  //uncomment this line to draw a grid on screen
  drawSquare(foodX,foodY,FOOD_COLOR);
  drawSnake(S);

  if(first){ //if the user just openned the game

    al_draw_filled_rectangle(50,200,510,246,FOOD_COLOR);
    al_draw_text(
      al_load_ttf_font("Comfortaa-Regular.ttf",20,ALLEGRO_TTF_NO_KERNING),
      al_map_rgb(0, 0, 0),280,210,ALLEGRO_ALIGN_CENTER,
      "Pressione qualquer tecla para começar."); //start up text
    al_flip_display();

    while(1){

      al_wait_for_event(eventQueue, &event);
      if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        break;
      else if(event.type == ALLEGRO_EVENT_KEY_DOWN){ //if any key was pressed
        al_draw_filled_rectangle(29,199,531,247,SCREEN_COLOR); //erase start up text
        al_flip_display();
        break;
      }
    }

    first = 0;
  }

  al_start_timer(timer);

  while(1){

    al_wait_for_event(eventQueue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER){

      if(abs(trueDir - (S->dir)) != 2) //if the new direction is valid
         trueDir = S->dir;
      else S->dir = trueDir;

      updateSnake(S);

      if(collision(S)){ //if snake died
        al_flip_display();
        al_rest(0.5);
        if(S->head->next->y <= 14){
          al_draw_filled_rectangle(30,390,530,436,FOOD_COLOR);
          al_draw_text(
            al_load_ttf_font("Comfortaa-Regular.ttf",20,ALLEGRO_TTF_NO_KERNING),
            al_map_rgb(0, 0, 0),280,400,ALLEGRO_ALIGN_CENTER,
            "Pressione qualquer tecla para jogar de novo.");
          } else{
            al_draw_filled_rectangle(30,100,530,146,FOOD_COLOR);
            al_draw_text(
              al_load_ttf_font("Comfortaa-Regular.ttf",20,ALLEGRO_TTF_NO_KERNING),
              al_map_rgb(0, 0, 0),280,110,ALLEGRO_ALIGN_CENTER,
              "Pressione qualquer tecla para jogar de novo.");
          }
        al_flip_display();
        al_rest(0.25);
        break;
      }

      if(snakeAte(foodX,foodY,S)){ //if snake ate
        updateScore();
        do{
          foodX = (rand() % 26) + 1;
          foodY = (rand() % 28) + 1;
        }while(isOverlapped(foodX,foodY,S));
        drawSquare(foodX,foodY,FOOD_COLOR);

        push(S); //add new cell to the end of the snake
      }

      al_flip_display();
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
      switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_RIGHT:
          if(S->dir == 3) break;
          S->dir = 1; break;
        case ALLEGRO_KEY_UP:
          if(S->dir == 4) break;
          S->dir = 2; break;
        case ALLEGRO_KEY_LEFT:
          if(S->dir == 1) break;
          S->dir = 3; break;
        case ALLEGRO_KEY_DOWN:
          if(S->dir == 2) break;
          S->dir = 4; break;
        default: break;
      }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
      endGame = 1;
      break;
    }
  }

  freeSnake(S);

  while(!endGame){

    al_wait_for_event(eventQueue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
      break;
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){

      al_destroy_event_queue(eventQueue);
      al_destroy_timer(timer);

      score = 0;
      goto INIT;
    }
  }


  al_destroy_display(display);
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

  al_draw_filled_rectangle(613,200,738,270,SCREEN_COLOR);
  score++;
  al_draw_textf(
    al_load_ttf_font("Comfortaa-Regular.ttf",60,ALLEGRO_TTF_NO_KERNING),
    al_map_rgb(255,255,255),670,200,ALLEGRO_ALIGN_CENTER,"%d",score);

}

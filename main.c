#include "header.h"

int main(void){

   ALLEGRO_DISPLAY *display = NULL;

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   al_clear_to_color(SCREEN_COLOR);

   al_init_font_addon();
   al_init_ttf_addon();

   setupScreen();


   al_flip_display();



   al_rest(4.0);
   al_destroy_display(display);
   return 0;
}

void setupScreen(){

  al_draw_text(
    al_load_ttf_font("Comfortaa-Regular.ttf",42,ALLEGRO_TTF_NO_KERNING),
    al_map_rgb(255,255,255),578,10,ALLEGRO_ALIGN_LEFT,"jogo da"
  );
  al_draw_text(
    al_load_ttf_font("Comfortaa-Regular.ttf",42,ALLEGRO_TTF_NO_KERNING),
    al_map_rgb(255,255,255),568,60,ALLEGRO_ALIGN_LEFT,"cobrinha"
  );
  al_draw_rectangle(10,10,SCREEN_W - 249,SCREEN_H - 9, al_map_rgb(255,255,255), 1);

}

void drawSquare(int x, int y, ALLEGRO_COLOR color){

  if(x <= 27 && x > 0 && y <=29 && y > 0){
    x --;
    y --;
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
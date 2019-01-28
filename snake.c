#include "header.h"

snake* newSnake(void){

  int xStart = 9;
  int yStart = 19;
  int sizeStart = 4;

  snake* S = (snake*) malloc(sizeof(snake)); //allocates memory for the snake itself
  S->head = (pointer) malloc(sizeof(cell)); //allocates memory for the first cell
  S->tail = S->head; //points tail to the head cell (list is empty)
  S->head->next = NULL;

  for(int i = 0; i < sizeStart + 1; i++){
    S->tail->next = (pointer) malloc(sizeof(cell));
    S->tail = S->tail->next;
    S->tail->next = NULL;
    S->tail->x = xStart - i;
    S->tail->y = yStart;
    S->tail->dir = 1;
  } //creates first initial cells plus the tail cell

  return S;
}

void drawSnake(snake* S){

  pointer p = S->head;

  while(p->next != S->tail){
    drawSquare(p->next->x, p->next->y, SNAKE_COLOR);
    p = p->next;
  } //draws every cell besides tail cell (the tail cell is used when snakes eats food)
}

void updateSnake(snake *S){

  pointer p = (pointer) malloc(sizeof(cell));
  p->dir = S->head->next->dir;
  switch(p->dir){
    case 1: //right
      p->x = S->head->next->x + 1;
      p->y = S->head->next->y;
      break;
    case 2: //up
      p->x = S->head->next->x;
      p->y = S->head->next->y - 1;
      break;
    case 3: //left
      p->x = S->head->next->x - 1;
      p->y = S->head->next->y;
      break;
    case 4: //down
      p->x = S->head->next->x;
      p->y = S->head->next->y + 1;
      break;
  } //decides position of the next cell based on variable "dir"

  p->next = S->head->next;
  S->head->next = p;
  //puts new cell pointed by "p" after the head of the snake

  while(p->next != S->tail){
    p = p->next;} //iterates till "p" is the last pointer before tail

  drawSquare(p->x, p->y, SCREEN_COLOR); //erases last cell of snake
  free(S->tail);
  S->tail = p; //new  tail is "p"

}

void freeSnake(snake *S){

  pointer p = S->head;

  while(p != S->tail){
    p = S->head;
    S->head = S->head->next;
    free(p);
  }
  free(p->next);
  free(S);
}

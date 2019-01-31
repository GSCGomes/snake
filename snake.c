#include "header.h"

snake* newSnake(void){

  int xStart = 9;
  int yStart = 19;
  int sizeStart = 4;

  snake* S = (snake*) malloc(sizeof(snake)); //allocates memory for the snake itself
  S->head = (pointer) malloc(sizeof(cell)); //allocates memory for the first cell
  S->tail = S->head; //points tail to the head cell (list is empty)
  S->head->next = NULL;

  S->dir = 1; //snake starts going to the right

  for(int i = 0; i < sizeStart + 1; i++){
    S->tail->next = (pointer) malloc(sizeof(cell));
    S->tail = S->tail->next;
    S->tail->next = NULL;
    S->tail->x = xStart - i;
    S->tail->y = yStart;
  } //creates first initial cells plus the tail cell

  return S;
}

void drawSnake(snake* S){

  pointer p = S->head;

  while(p->next != S->tail){
    drawSquare(p->next->x, p->next->y, SNAKE_COLOR);
    p = p->next;
  } //draws every cell except tail cell (the tail cell is used when snakes eats food)
}

void updateSnake(snake *S){

  pointer p = (pointer) malloc(sizeof(cell)); //points to the new cell
  switch(S->dir){
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

  while(p->next != S->tail)
    p = p->next; //iterates till "p" is the last pointer before tail

  drawSquare(p->x, p->y, SCREEN_COLOR); //erases last cell of snake
  drawSquare(S->head->next->x, S->head->next->y, SNAKE_COLOR); //draws new first cell
  free(S->tail);
  S->tail = p; //new  tail is "p"
  S->tail->next = NULL;
}

void freeSnake(snake *S){

  pointer p = S->head;

  while(p != S->tail){
    p = S->head;
    S->head = S->head->next;
    free(p);
  }
  free(S);
}

void push(snake *S){

  pointer p = S->head;
  while(p->next != S->tail){
    p = p->next;} //iterates till "p" is the last pointer before tail

  int dx = S->tail->x - p->x;
  int dy = S->tail->y - p->y;

  p = (pointer) malloc(sizeof(cell));
  p->x = S->tail->x + dx;
  p->y = S->tail->y + dy;

  S->tail->next = p;
  S->tail = p;
  p->next = NULL;

}

int collision(snake* S){

  int exit = 0;

  pointer p = S->head->next->next;
  while(p != NULL){
    if((S->head->next->x == p->x) && (S->head->next->y == p->y)){ // if snake ate itself
      printf("death by self-cannibalism, score was %d\n",score);
      exit = 1;
      break;
    }
    p = p->next;
  }

  if(S->head->next->x > 27 || S->head->next->x < 1 ||
    S->head->next->y > 29 || S->head->next->y < 1)
  {
      exit = 1;
      printf("death by head trauma, score was %d\n",score);
  }

  return exit;
}

int snakeAte(int foodX, int foodY, snake* S){

  return(
    S->head->next->x == foodX && S->head->next->y == foodY
  );
}

int isOverlapped(int foodX, int foodY, snake* S){

  pointer p = S->head;
  while(p != S->tail->next){
    if(p->x == foodX && p->y == foodY){
      return 1;
    }
    p = p->next;
  }

  return 0;
}

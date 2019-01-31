Hello, my name is Guilherme Gomes. Thank you for your interest in my code.

This is a snake game made in C language using the Allegro5 library.
To run this you will need to install the Allegro5 library and a C language compiler.

compilation:
  if you use GCC compiler, use the following command line while in the repository folder
  $   gcc -Wall *.c -o "snake" -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf

execution:
  to execute, just run the executable file generated after the compilation
  $ ./snake


ABOUT THE GAME
I decided to make this little game just to refresh some programming concepts after a
lot of time without doing any programming. The scope was to make it simple and functional.
The title of the game "jogo da cobrinha" is the portuguese translation for snake game.

ROOM FOR IMPROVEMENT
Of course there is much room for improvement, but I decided to move on to more complex
projects instead of making this one totally perfect. I've listed below some of the points where
I see how this game could be improved.
- improvement of the food generation method (the current method just chooses random positions until
  it finds one that is not occupied with the snake)
- pause functionality
- start up menu
- instructions on screen
- some kind of multi-player mode
- difficulty selector

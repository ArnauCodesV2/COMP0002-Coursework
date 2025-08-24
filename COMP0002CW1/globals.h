#ifndef GLOBALS_H
#define GLOBALS_H

extern int columns; //MAX = 20, MIN = 5 for visual purposes
extern int rows; //MAX 20, MIN = 5
extern int markerCol; 
extern int markerRow; 
extern int colStart; 
extern int rowStart; 
extern int maxX;
extern int maxY;

#endif

//columns - 2 cols and rows - 2 rows will be drawn as if not it does not scale correctly with the fixed 500x300 pixel size
//if you want to input n columns keep in mind that you will output an n-2 grid and the program will work with that as the n
//so if you want to input n, make sure to say n+2 when defining the variables at the top of this file
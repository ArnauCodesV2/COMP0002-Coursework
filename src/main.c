#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "graphics.h"

void drawColumns(int columns, double pixelsPerColumn, double pixelsPerRow); 
void drawRows(int rows, double pixelsPerRow, double pixelsPerColumn);
void drawGrid(double pixelsPerColumn, double pixelsPerRow);
void drawRobot(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotX, double robotY);
void drawHome(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY);
void drawMarker(double pixelsPerColumn, double pixelsPerRow, int markerCol, int markerRow, double lineOffsetX, double lineOffsetY);
void goRight1(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol);
void goRight2(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol);
void goDown1(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol, int *robotRow);
void goDown2(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol, int *robotRow);
void goUp1(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol, int *robotRow);
void goUp2(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol, int *robotRow);
void goLeft1(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol);
void goLeft2(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol);
void searchGrid1(int** grid, int *robotRow, int *robotCol, double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY);
void searchGrid2(int** grid, int *robotRow, int *robotCol, double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY);
void searchGrid3(int** grid, int *robotRow, int *robotCol);
void searchGrid4(int **grid, int *rows, int *columns);
void freeGrid(int **grid);
void move();


int main(){
    double pixelsPerCol = (float)maxX / columns; //unary operator float to get better spaced lines for the grid
    double pixelsPerRow = (float)maxY / rows;
    double robotBoundX = pixelsPerCol * 0.2; //find the bounds  
    double robotBoundY = pixelsPerRow * 0.17; 
    double robotStartX = pixelsPerCol * colStart + robotBoundY; //Re-scale the robot starting pos
    double robotStartY = pixelsPerRow * rowStart + robotBoundY; 

    int robotRow = rowStart;
    int robotCol = colStart;

    int **grid = (int**)malloc((rows - 2) * sizeof(int*)); //allocate memory for the rows of the array
    
    if (grid == NULL){
        printf("Memory allocation failed\n"); //quit if allocation failed
        return 1;
    }

    for (int i = 0; i < rows - 2; i++) {
        grid[i] = (int*)calloc((columns - 2), sizeof(int)); //initialise the array to 0's instead of garbage values, for each row allocate memory for the cols
        if (grid[i] == NULL){
            printf("Memory allocation failed\n"); 
            return 1;
        }
    }

    drawGrid(pixelsPerCol, pixelsPerRow);
    drawRobot(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, robotStartX, robotStartY);
    drawMarker(pixelsPerCol, pixelsPerRow, markerCol, markerRow, robotBoundX, robotBoundY);
    drawHome(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, robotStartX, robotStartY);

    //these 4 functions will always be called regardless of the input


    //these will cover the animations of the robot regarding on where it starts recall that later there is an algorithm to actually trace the marker's (x,y)
    if (robotStartX < pixelsPerCol * markerCol && robotStartY < pixelsPerRow * markerRow){
        searchGrid1(grid, &robotRow, &robotCol, pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, robotStartX, robotStartY);
        goRight1(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol);
        goDown1(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol, &robotRow);
        goUp1(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol, &robotRow);
        goLeft1(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol);
        freeGrid(grid);
        return 0;
    }

    if (robotStartX < pixelsPerCol * markerCol && robotStartY > pixelsPerRow * markerRow){
        searchGrid2(grid, &robotRow, &robotCol, pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, robotStartX, robotStartY);
        goRight1(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol);
        goUp2(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol, &robotRow);
        drawMarker(pixelsPerCol, pixelsPerRow, markerCol, markerRow, robotBoundX, robotBoundY);
        goDown2(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol, &robotRow);
        goLeft1(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol);
        freeGrid(grid);
        return 0;
    }

    if (robotStartX > pixelsPerCol * markerCol && robotStartY > pixelsPerRow * markerRow){
        searchGrid3(grid, &robotRow, &robotCol);
        goLeft2(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol);
        goUp2(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol, &robotRow);
        goDown2(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol, &robotRow);
        goRight2(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol);
        freeGrid(grid);
        return 0;
    }
                   
    if (robotStartX > pixelsPerCol * markerCol && robotStartY < pixelsPerCol * markerRow){ 
        searchGrid4(grid, &robotRow, &robotCol);
        goLeft2(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol);
        goDown1(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol, &robotRow);
        goUp1(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol, &robotRow);
        goRight2(pixelsPerCol, pixelsPerRow, robotBoundX, robotBoundY, markerCol, markerRow, robotStartX, robotStartY, &robotCol);
        freeGrid(grid);
        return 0;
    }

    return 0;
}

void freeGrid(int **grid){ 
    //a function to de-allocate the memory used for making the  grid, which will be called before ending the program to avoid memory leaks
    for (int i = 0; i < rows - 2; i++) {
        free(grid[i]);
    } 
    
    free(grid);
    grid = NULL; //avoid dangling pointers so set grid to NULL
}
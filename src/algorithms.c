#include "globals.h"
#include <stdio.h>

void searchGrid1(int** grid, int *robotRow, int *robotCol, double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY);
void searchGrid2(int** grid, int *robotRow, int *robotCol, double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY);
void searchGrid3(int** grid, int *robotRow, int *robotCol);
void searchGrid4(int **grid, int *rows, int *columns);

void searchGrid1(int** grid, int *robotRow, int *robotCol, double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY){
    //this will search the grid in a zigzag manner from left to right then increase the row and then right to left dpeneding on the value of direction
    //continously checking if the current (x,y) matches the marker's (x,y) and exiting the loop while found. 
    int found = 0; 
    int direction = 1;
    int c = columns - 2; 
    while(!found){
        if (direction == 1 && *robotCol < c) {
            (*robotCol)++; 
        } else if (direction == 1 && *robotCol == c) {
            (*robotRow)++; 
            direction = -1; 
        } else if (direction == -1 && *robotCol > 1) {
            (*robotCol)--; 
        } else if (direction == -1 && *robotCol == 1) {
            (*robotRow)++; 
            direction = 1; 
        } 
        if (*robotRow == markerRow && *robotCol == markerCol){ 
            //keep constantly checking if we are at the marker's position, and if we are, set found to 1 and exit the infinite loop
            found = 1;
            printf("Found at: %i, %i\n", *robotRow, *robotCol);
            break;
        }
    }
}

void searchGrid2(int **grid, int *robotRow, int *robotCol, double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY){
    //this will search for the marker starting from left to right and it will work exactly as the previous function
    //this also accounts for horizontal movements, like the previous one, starting at a bottom row
    int found = 0;
    int direction = 1;
    int c = columns - 2;
    while(!found){
        if (direction == 1 && *robotCol < c){
            (*robotCol)++; 
        } else if (direction == 1 && *robotCol == c){
            (*robotRow)--; 
            direction = -1; 
        } else if (direction == -1 && *robotCol > 1){
            (*robotCol)--; 
        } else if (direction == -1 && *robotCol == 1){
            (*robotRow)--; 
            direction = 1;
        } 
       if (*robotRow == markerRow && *robotCol == markerCol){ 
            found = 1;
            printf("Found at: %i, %i\n", *robotRow, *robotCol);
            break;
        } 

    }
}

void searchGrid3(int **grid, int *robotRow, int *robotCol){
    //this function will go from right to left but it will start at a bottom row, also searching in a zigzag manner until it 
    //reaches the marker's x,y position
    int found = 0;
    int direction = -1;
    int c = columns - 2;
    while (!found) {
        if (direction == -1 && *robotCol > 1) {
            (*robotCol)--; 
        } else if (direction == -1 && *robotCol == 1) {
            (*robotRow)--;
            direction = 1;
        } else if (direction == 1 && *robotCol < c) {
            (*robotCol)++; 
        } else if (direction == 1 && *robotCol == c) {
            (*robotRow)--; 
            direction = -1;
        }
        if (*robotRow == markerRow && *robotCol == markerCol){ 
            found = 1;
            printf("Found at: %i, %i\n", *robotRow, *robotCol);
            break;
        }
    }
}

void searchGrid4(int **grid, int *robotRow, int *robotCol) {
    //this function will go from top to bottom, right to left
    int found = 0;
    int direction = -1;
    int c = columns - 2;
    while (!found) {
        if (direction == -1 && *robotCol > 1) {
            (*robotCol)--;  
        } else if (direction == 1 && *robotCol < c) {
            (*robotCol)++; 
        } else if (direction == -1 && *robotCol == 1){
            (*robotRow)++;
            direction = 1; 
        } else if (direction == 1 && *robotCol == c){
            (*robotRow)++; 
            direction = -1;
        }
        if (*robotRow == markerRow && *robotCol == markerCol){
            found = 1;
            printf("Found at: %i, %i\n", *robotRow, *robotCol);
            break;
        }
    }
}
//Recall that we are passing by reference, so we are not just changing the values of robotCol and robotRow, we are changing the adress
//of these values, so we update them to where the marker position will be after the ends of these loops
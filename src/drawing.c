#include "globals.h"
#include "graphics.h"
#include <stdio.h>

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
void move();

void drawColumns(int columns, double pixelsPerColumn, double pixelsPerRow){
    for (int i = 1; i < columns; i++){
        drawLine((pixelsPerColumn * i), pixelsPerRow, (pixelsPerColumn * i), maxY - pixelsPerRow);
    }
}

void drawRows(int rows, double pixelsPerRow, double pixelsPerColumn){
    for (int i = 1; i < rows; i++){
        drawLine(pixelsPerColumn, (pixelsPerRow * i), maxX - pixelsPerColumn, (pixelsPerRow * i));
    }
}

void drawGrid(double pixelsPerColumn, double pixelsPerRow){
    //calls the two other just defined function to draw the whole grid
    background();
    drawColumns(columns, pixelsPerColumn, pixelsPerRow);  
    drawRows(rows, pixelsPerRow, pixelsPerColumn);
}   


void drawRobot(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY){
    //filling the Arc from 0,360 degrees and makes it green
    foreground();
    setColour(green);
    fillArc(robotStartX, robotStartY, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360);
}  

void drawHome(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, double robotStartX, double robotStartY){
    //draws the home position as a rectangle wherever the robot is starting, excalty sclaed for one box
    background();
    setColour(yellow);
    fillRect(robotStartX - lineOffsetY*0.803, robotStartY - lineOffsetY*0.8, pixelsPerColumn*0.97, pixelsPerRow);
}


void drawMarker(double pixelsPerColumn, double pixelsPerRow, int markerCol, int markerRow, double lineOffsetX, double lineOffsetY){
    //will draw the marker wherever the marker is positioned by the user
    foreground();
    setColour(gray);
    fillRect(pixelsPerColumn * (markerCol), pixelsPerRow * (markerRow), pixelsPerColumn, pixelsPerRow); 
    setColour(black);
    drawString("Mark", pixelsPerColumn * (markerCol) + lineOffsetY, pixelsPerRow * (markerRow) + lineOffsetX * 2);
}

void goRight1(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol){
    //keep increasing x-cord by 1 until it reaches the dereferenced value of robotCol (markers col) (-1 so it doeesnt overlap with grid)
    foreground();
    drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
    for (int i = robotStartX; i <= pixelsPerColumn * (*robotCol - 1); i++){
        move(); 
        fillArc(pixelsPerColumn + i + lineOffsetY, robotStartY, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360); 
        if (i <= pixelsPerColumn * ((*robotCol) - 1)){ 
            //checking if we have touched the marker, but while we havent, keep drawing it in the grid
            drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
        }
    } 
}

void goRight2(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol){
    // start at the markers position in the grid namely, tracing the path back home
    foreground();
    drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
    for (int i = pixelsPerColumn * (*robotCol); i <= robotStartX; i++){
        move();
        fillArc(i, robotStartY, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360);
    } 
}


void goDown1(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol, int *robotRow){
    //make the robot go down, by starting at its intial y position and it will go to the markers row (*robotRow)
    foreground();
    drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
    for (int i = robotStartY; i <= pixelsPerRow * (*robotRow); i++){
        move();
        fillArc(lineOffsetY + ((*robotCol) * pixelsPerColumn), i + lineOffsetY, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360);
        if (i <= pixelsPerRow * (*robotRow - 1)){
            drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
        }
    }
}

void goDown2(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartC, double robotStartY, int *robotCol, int *robotRow){
    //will go down starting at the marker's position  
    foreground();
    for (int i = pixelsPerRow * (*robotRow); i <= robotStartY; i++){
        move();
        fillArc(lineOffsetY + ((*robotCol) * pixelsPerColumn), i + lineOffsetY, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360);
    }
}

void goUp1(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol, int *robotRow){
    //here, we need to go up starting at the marker's row and go up until we reach the home position's row
    foreground();
    for (int i = pixelsPerRow * (*robotRow); i >= robotStartY; i--){
        move();
        fillArc(lineOffsetY + ((*robotCol) * pixelsPerColumn), i, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360);
    }
}

void goUp2(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double startRobotX, double startRobotY, int *robotCol, int *robotRow){
    //go up but starting at the home position 
    foreground();
    drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
    for (int i  = startRobotY; i >= (*robotRow) * pixelsPerRow; i--){
        move();
        fillArc(lineOffsetY + ((*robotCol) * pixelsPerColumn), i, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360);
        if (i >= pixelsPerRow * ((*robotRow) - 1)){
            drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
        }
    }
}

void goLeft1(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol){
    //go left by fisrt starting at the marker's position tracing the robot back to its home position
    foreground();
    for (int i = pixelsPerColumn * (*robotCol); i > robotStartX; i--){
        move();
        fillArc(i, robotStartY, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360);       
    }
}

void goLeft2(double pixelsPerColumn, double pixelsPerRow, double lineOffsetX, double lineOffsetY, int markerCol, int markerRow, double robotStartX, double robotStartY, int *robotCol){
    //start at its home poistion and go to the col where the marker is found
    foreground();
    drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
    for (int i = robotStartX; i > pixelsPerColumn * (*robotCol); i--){
        move();
        fillArc(i, robotStartY, pixelsPerColumn - lineOffsetX, pixelsPerRow - lineOffsetX, 0, 360);   
        drawMarker(pixelsPerColumn, pixelsPerRow, markerCol, markerRow, lineOffsetX, lineOffsetY);
    }
}

void move(){
    //general pattern for animation
    sleep(5);
    clear();
    setColour(green);
}


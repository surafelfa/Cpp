/*
     HiLCoE School of Computer Science & Technology
          Problem Solving with Programming
				Assignment on Tetris

     Start-up code developed by the Instructor

     Winter 2019
*/
///written by surafel
#include <iostream>
#include<stdio.h>
#include <conio.h>
#include <string>
#include <ctype.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>
const int NB_BLOCKS = 1;
const int BAR_BLOCK = 1;
const int T_BLOCK   = 2;
const int L_BLOCK   = 3;
const int LR_BLOCK  = 4;
const int BOX_BLOCK = 5;
const int NO_OREINTATION=1;
const int HORIZONTAL = 1;
const int VERTICAL = 2;
const int VERTICAL_LEFT=1;
const int VERTICAL_RIGHT=2;
const int HORIZONTAL_TOP=3;
const int HORIZONTAL_BOTTOM=4;
const int RIGHT = 1;
const int LEFT = 2;
const int DOWN  = 3;

const int BOARD_COLOR   = BLACK;
const int BKGRD_COLOR   = BOARD_COLOR;
const int FILLING_COLOR = GREEN; //LIGHTGRAY;
const int FRGRD_COLOR   = 1; //CYAN; //BLUE; //GREEN; //RED; // LIGHTGRAY;
// const int FRGRD_COLOR   = BOARD_COLOR; //FILLING_COLOR;
const int GRID_COLOR    = LIGHTGRAY;
const int BORDER_COLOR  = GRID_COLOR;


const int BOARDWIDTH 	= 180;
const int BOARDHEIGHT	= 240;
const int NB_ROWS  	= 15;
const int NB_COLS  	= 10;
const int CELL_SIZE	= BOARDHEIGHT/(NB_ROWS+1);//15
const int LEFTCORNER	= (600 - (CELL_SIZE*(NB_COLS+2)))/2; //230;
const int TOPCORNER	= 120;
const int INFOAREAWIDTH	= 600;
const int INFOAREAHEIGHT= 105;
const int INFOAREALEFT	= 20;
const int INFOAREATOP	= 370;

const int LEFTARROW=75;
const int RIGHTARROW=77;
const int UPARROW=72;
const int DOWNARROW=80;
const int ENTER=13;
const int ESC=27;
const int SPACE=32;


//initializes graphics driver
void initGraphEngine(){
  int gdriver = DETECT, gmode;
  initgraph(&gdriver, &gmode, "...\\BGI");
}
void game_name(){
    setcolor(LIGHTBLUE);
    settextstyle(6,0,4);
    outtextxy(15,20,"TETRIS ");
    outtextxy(15,30,"TETRIS ");
    outtextxy(450,20,"GAME ");
    outtextxy(450,30,"GAME ");


}
void displayInfo(char *msg){
  setcolor(WHITE);
  setfillstyle(SOLID_FILL, LIGHTBLUE);
  bar(INFOAREALEFT+1,INFOAREATOP+1,INFOAREALEFT+400,
	INFOAREATOP+INFOAREAHEIGHT-1);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.5);
  outtextxy(INFOAREALEFT+30,INFOAREATOP+50,msg);
}
void fillGrid( ){
 int x = LEFTCORNER+CELL_SIZE,  y = TOPCORNER;
 setcolor(GRID_COLOR);
 for(int i=1;i<=NB_ROWS;i++)
 {
     for (int j=1;j<=NB_COLS;j++)
     { rectangle(x,y,x+CELL_SIZE,y+CELL_SIZE);
       x+=CELL_SIZE;
     }
     x=LEFTCORNER+CELL_SIZE;
     y+=CELL_SIZE;
 }
}
void displayScore(int score, int level = 1){
    int  width= 150;
    int  height = 150;
    char totalscore[20];
    char levels[20];
    setcolor(LIGHTBLUE);

    sprintf(totalscore, "YOUR SCORE IS:%d", score);
    sprintf(levels, "CURRENT LEVEL:%d", level);
    setfillstyle(SOLID_FILL, BOARD_COLOR );
    bar(INFOAREALEFT, TOPCORNER, INFOAREALEFT+width, TOPCORNER+height);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1.5);

    outtextxy(INFOAREALEFT+410, TOPCORNER+10, totalscore);
    outtextxy(INFOAREALEFT+410, TOPCORNER+40, levels);
    settextstyle(6, 0, 1.5);
    outtextxy(INFOAREALEFT, TOPCORNER+30,"NEXT BLOCK");
}
void clearDisplayArea(){
  setfillstyle(SOLID_FILL, BLACK);
  bar(LEFTCORNER+CELL_SIZE,0,(LEFTCORNER+BOARDWIDTH-CELL_SIZE),TOPCORNER-1);
}
void drawBoard(){
 // Playing Board
 setfillstyle(SOLID_FILL, LIGHTBLUE);
 bar(LEFTCORNER,TOPCORNER,LEFTCORNER+BOARDWIDTH,TOPCORNER+BOARDHEIGHT);
 setfillstyle(SOLID_FILL, BOARD_COLOR);
 bar(LEFTCORNER+CELL_SIZE,TOPCORNER,
	  (LEFTCORNER+BOARDWIDTH-CELL_SIZE),(TOPCORNER+BOARDHEIGHT-
    CELL_SIZE));
 fillGrid();
  //Display Area
 setfillstyle(SOLID_FILL, LIGHTBLUE);
 bar(INFOAREALEFT,INFOAREATOP,INFOAREALEFT+INFOAREAWIDTH,INFOAREATOP+
		INFOAREAHEIGHT);
 rectangle(INFOAREALEFT,INFOAREATOP,INFOAREALEFT+INFOAREAWIDTH,
		INFOAREATOP+INFOAREAHEIGHT);

}
void reDrawCellsGrid(int xLeft, int yTop, int nbCells, int orientation){
    // redraw the grid of cells
      int i;
      setcolor(BORDER_COLOR);
      for (i=1; i<=nbCells; i++) {
       rectangle(xLeft, yTop, xLeft+CELL_SIZE, yTop+CELL_SIZE);
       if (orientation == HORIZONTAL)  xLeft=xLeft+CELL_SIZE;
       else yTop = yTop + CELL_SIZE;
      }
  }
//draws Bar Block
void drawBarBlock(int xLeft, int yTop, int orientation, int fillingColor)
  {
     setfillstyle(SOLID_FILL, fillingColor);
     if (orientation==HORIZONTAL) {
	  bar(xLeft, yTop, xLeft+4*CELL_SIZE,yTop+CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop, 4, HORIZONTAL);
     }
     else  {// orientation is VERTICAL
	  bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+4*CELL_SIZE);
	  reDrawCellsGrid(xLeft, yTop ,4, VERTICAL);
     }
  }
//draws L Block
void drawLBlock(int xLeft, int yTop, int orientation, int fillingColor)
  {
     setfillstyle(SOLID_FILL, fillingColor);
     if (orientation==VERTICAL_RIGHT) {
	  {bar(xLeft, yTop, xLeft+CELL_SIZE,yTop+3*CELL_SIZE);
	   bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE,yTop+CELL_SIZE);}
      {reDrawCellsGrid(xLeft, yTop ,3, VERTICAL);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop,1, HORIZONTAL);}
     }
     else if (orientation==HORIZONTAL_BOTTOM)  {

	  {bar(xLeft, yTop, xLeft+3*CELL_SIZE, yTop+CELL_SIZE);
	  bar(xLeft+2*CELL_SIZE, yTop+CELL_SIZE, xLeft+3*CELL_SIZE, yTop+2*CELL_SIZE);}
	  {reDrawCellsGrid(xLeft, yTop ,3, HORIZONTAL);
	  reDrawCellsGrid(xLeft+2*CELL_SIZE, yTop+CELL_SIZE ,1, VERTICAL);}
     }
     else if (orientation==VERTICAL_LEFT){
        {bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);
        bar(xLeft, yTop+2*CELL_SIZE, xLeft+CELL_SIZE, yTop+3*CELL_SIZE);}
        {reDrawCellsGrid(xLeft+CELL_SIZE, yTop ,3, VERTICAL);
        reDrawCellsGrid(xLeft, yTop+2*CELL_SIZE ,1, HORIZONTAL);}
     }
     else {// orientation is HORIZONTAL_TOP
        {bar(xLeft, yTop, xLeft+CELL_SIZE, yTop+2*CELL_SIZE);
        bar(xLeft+CELL_SIZE,yTop+CELL_SIZE, xLeft+3*CELL_SIZE, yTop+2*CELL_SIZE);}
        {reDrawCellsGrid(xLeft, yTop ,2, VERTICAL);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE ,2, HORIZONTAL);}
     }

  }


//draws LR Block
void drawLrBlock(int xLeft, int yTop, int orientation, int fillingColor)
  {
     setfillstyle(SOLID_FILL, fillingColor);
     if (orientation==VERTICAL_RIGHT) {
	  {bar(xLeft, yTop, xLeft+CELL_SIZE,yTop+3*CELL_SIZE);
	   bar(xLeft+CELL_SIZE, yTop+2* CELL_SIZE, xLeft+2*CELL_SIZE,yTop+3*CELL_SIZE);}
      {reDrawCellsGrid(xLeft, yTop ,3, VERTICAL);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop+2*CELL_SIZE ,1, HORIZONTAL);}
     }
     else if (orientation==HORIZONTAL_BOTTOM)  {

	  {bar(xLeft, yTop, xLeft+3*CELL_SIZE, yTop+CELL_SIZE);
	  bar(xLeft, yTop+CELL_SIZE, xLeft+CELL_SIZE, yTop+2*CELL_SIZE);}
	  {reDrawCellsGrid(xLeft, yTop ,3, HORIZONTAL);
	  reDrawCellsGrid(xLeft, yTop+CELL_SIZE ,1, VERTICAL);}
     }
     else if (orientation==VERTICAL_LEFT){
        {bar(xLeft, yTop, xLeft+2*CELL_SIZE, yTop+CELL_SIZE);
        bar(xLeft+CELL_SIZE, yTop+CELL_SIZE, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);}
        {reDrawCellsGrid(xLeft, yTop ,2, HORIZONTAL);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE ,2, VERTICAL);}
     }
     else {// orientation is HORIZONTAL_TOP
        {bar(xLeft+2*CELL_SIZE, yTop, xLeft+3*CELL_SIZE, yTop+CELL_SIZE);
        bar(xLeft, yTop+CELL_SIZE, xLeft+3*CELL_SIZE, yTop+2*CELL_SIZE);}
        {reDrawCellsGrid(xLeft+2*CELL_SIZE, yTop ,1, HORIZONTAL);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE ,3, HORIZONTAL);}
     }

  }

//draws T_BLOCK Block
void drawTBlock(int xLeft, int yTop, int orientation, int fillingColor)
  {
     setfillstyle(SOLID_FILL, fillingColor);
     if (orientation==HORIZONTAL_BOTTOM) {
	  {bar(xLeft, yTop, xLeft+3*CELL_SIZE,yTop+CELL_SIZE);
	  bar(xLeft+CELL_SIZE,yTop+CELL_SIZE, xLeft+2*CELL_SIZE,yTop+2*CELL_SIZE);}
	  {reDrawCellsGrid(xLeft, yTop, 3, HORIZONTAL);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE,1, HORIZONTAL);}
     }
     else if (orientation==HORIZONTAL_TOP) {
        {bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE,yTop+CELL_SIZE);
        bar(xLeft, yTop+CELL_SIZE, xLeft+3*CELL_SIZE,yTop+2*CELL_SIZE);}
        {reDrawCellsGrid(xLeft+CELL_SIZE, yTop, 1, HORIZONTAL);
        reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 3, HORIZONTAL);}
     }
     else if (orientation==VERTICAL_RIGHT) {
        {bar(xLeft, yTop, xLeft+CELL_SIZE,yTop+3*CELL_SIZE);
        bar(xLeft+CELL_SIZE, yTop+CELL_SIZE, xLeft+2*CELL_SIZE,yTop+2*CELL_SIZE);}
        {reDrawCellsGrid(xLeft, yTop ,3, VERTICAL);
        reDrawCellsGrid(xLeft+CELL_SIZE, yTop+CELL_SIZE,1, HORIZONTAL);}
     }
     else  {// orientation is VERTICAL_LEFT
	  {bar(xLeft, yTop+CELL_SIZE, xLeft+CELL_SIZE, yTop+2*CELL_SIZE);
	  bar(xLeft+CELL_SIZE, yTop, xLeft+2*CELL_SIZE, yTop+3*CELL_SIZE);}
	  {reDrawCellsGrid(xLeft, yTop+CELL_SIZE,1, HORIZONTAL);
	  reDrawCellsGrid(xLeft+CELL_SIZE, yTop ,3, VERTICAL);}
     }
  }

//draws Box Block
void drawBoxBlock(int xLeft, int yTop,int fillingColor)
  {
     setfillstyle(SOLID_FILL, fillingColor);
     bar(xLeft, yTop, xLeft+2*CELL_SIZE,yTop+2*CELL_SIZE);
    {reDrawCellsGrid(xLeft, yTop, 2, NO_OREINTATION);
     reDrawCellsGrid(xLeft, yTop+CELL_SIZE, 2,NO_OREINTATION);}
  }

void UpcomingBlock(int *blockId, int &orientation, int&fillingColor){
    srand(time(0));
       *blockId =rand()%5+1;
fillingColor  = rand()%4 + 1;
switch(*blockId){
case BAR_BLOCK:
    orientation = rand()%2 + 1;
    break;
case T_BLOCK:
    orientation = rand()%4 + 1;
    break;
case L_BLOCK:
    orientation = rand()%4 + 1;
    break;
case LR_BLOCK:
    orientation = rand()%4 + 1;
    break;
    }
}

void drawUpcomingBlock(int * blockId, int orientation, int fillingColor){

int x = INFOAREALEFT+75;
int y = 200;
switch (*blockId){

case BAR_BLOCK:
    drawBarBlock(x,y,orientation, fillingColor);
    break;
case T_BLOCK:
    drawTBlock(x,y,orientation, fillingColor);
    break;
case BOX_BLOCK:
    drawBoxBlock(x,y,fillingColor);
    break;
case L_BLOCK:
    drawLBlock(x,y,orientation, fillingColor);
    break;
case LR_BLOCK:
    drawLrBlock(x,y,orientation, fillingColor);
    break;
}
}

void clearScoreArea(){
int x =INFOAREALEFT+33;
int y = 75;
setfillstyle(SOLID_FILL, BKGRD_COLOR);
bar(x,y,x+CELL_SIZE*5,y+CELL_SIZE*5);
}
void generateBarBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
      {
	yTop = TOPCORNER;
	if (orientation == HORIZONTAL) xLeft  = LEFTCORNER+4*CELL_SIZE;
	else    xLeft = LEFTCORNER+5*CELL_SIZE;
	drawBarBlock(xLeft,yTop,orientation, fillingColor /*FRGRD_COLOR*/);
      }

void generateLBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
      {
	yTop = TOPCORNER;
	if (orientation == HORIZONTAL_BOTTOM||orientation ==HORIZONTAL_TOP) xLeft  = LEFTCORNER+5*CELL_SIZE;
	else    xLeft = LEFTCORNER+5*CELL_SIZE;
	drawLBlock(xLeft,yTop,orientation, fillingColor /*FRGRD_COLOR*/);
      }

void generateLrBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
      {
	yTop = TOPCORNER;
	if (orientation == HORIZONTAL_BOTTOM||orientation ==HORIZONTAL_TOP) xLeft  = LEFTCORNER+5*CELL_SIZE;
	else    xLeft = LEFTCORNER+5*CELL_SIZE;
	drawLrBlock(xLeft,yTop,orientation, fillingColor /*FRGRD_COLOR*/);
      }


void generateTBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
      {
	yTop = TOPCORNER;
	if (orientation == HORIZONTAL_BOTTOM||orientation ==HORIZONTAL_TOP) xLeft  = LEFTCORNER+5*CELL_SIZE;
	else    xLeft = LEFTCORNER+5*CELL_SIZE;

	drawTBlock(xLeft,yTop,orientation, fillingColor /*FRGRD_COLOR*/);
      }
// generates Box block in random orientation
void generateBoxBlock(int & orientation, int & xLeft, int & yTop, int & fillingColor)
      {
	orientation = NO_OREINTATION;
	yTop = TOPCORNER;
	/*if (orientation == NO_OREINTATION) */xLeft  = LEFTCORNER+5*CELL_SIZE;
	drawBoxBlock(xLeft,yTop, fillingColor /*FRGRD_COLOR*/);
      }

// generates a block at random
void generateNewBlock( int * blockId, int * orientation,int * xLeft, int *
	yTop, int * fillingColor)
     {
       switch(*blockId) {
	case T_BLOCK  : generateTBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case L_BLOCK  : generateLBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case LR_BLOCK : generateLrBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case BOX_BLOCK: generateBoxBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
	case BAR_BLOCK: generateBarBlock(*orientation, *xLeft, *yTop, *fillingColor); break;
       }
     }

// check if Bar block can be moved to the left
void checkTranslateBarRouteLeft(int orientation, int xLeft, int yTop, int &
freeRoute)
      {      int maxNbCells;
	  // check if route is not blocked
	  yTop = yTop + CELL_SIZE/2;
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL:
	       xLeft = xLeft - CELL_SIZE/2;
	       if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
	       break;

	    case VERTICAL:
	       maxNbCells = 4;
	       xLeft  = xLeft - CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
    }
// check if L block can be moved to the left
void checkTranslateLRouteLeft(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 2;
	       xLeft  = xLeft - CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    xLeft  = xLeft- 2* CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
	    case HORIZONTAL_TOP:
	       maxNbCells = 2;
	       xLeft  = xLeft-CELL_SIZE/2;
	       yTop = yTop+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
	        yTop = yTop+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       maxNbCells = 3;
	       xLeft  = xLeft-CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
            }
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       //maxNbCells = 1;
	       xLeft  = xLeft-CELL_SIZE/2;
	       yTop = yTop+2*CELL_SIZE + CELL_SIZE/2;
		if (getpixel(xLeft, yTop) == BOARD_COLOR );
		else  freeRoute = 0; // route is blocked
        if(freeRoute){
            maxNbCells=2;
            xLeft  = xLeft+CELL_SIZE;
	        yTop = yTop-CELL_SIZE;
	        do{
        if(getpixel(xLeft, yTop) == BOARD_COLOR ){
            yTop = yTop -CELL_SIZE;
            maxNbCells--;
        }
        else freeRoute=0;
            }while( maxNbCells >= 1 && freeRoute);
        }
	       break;
	  }
    }
// check if Lr block can be moved to the left
void checkTranslateLrRouteLeft(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 2;
	       xLeft  = xLeft - CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;

	    case HORIZONTAL_TOP:
	       maxNbCells = 2;
	       xLeft  = xLeft-CELL_SIZE/2;
	       yTop = yTop+CELL_SIZE + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+2*CELL_SIZE;
	        yTop = yTop-CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       maxNbCells = 3;
	       xLeft  = xLeft-CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop+CELL_SIZE + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop +CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
        if(freeRoute){
            maxNbCells=1;
            xLeft  = xLeft-CELL_SIZE;
	        yTop = yTop -3* CELL_SIZE;
	        do{
        if(getpixel(xLeft, yTop) == BOARD_COLOR )
            maxNbCells--;
        else freeRoute=0;
            }while( maxNbCells >= 1 && freeRoute);
        }
	       break;
	  }
    }
// check if T block can be moved to the left
void checkTranslateTRouteLeft(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 2;
	       xLeft  = xLeft - CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    xLeft  = xLeft + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;

	    case HORIZONTAL_TOP:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft-CELL_SIZE;
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       maxNbCells = 3;
	       xLeft  = xLeft-CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + 2* CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
        if(freeRoute){
            maxNbCells=1;
            xLeft  = xLeft-CELL_SIZE;
	        yTop = yTop -3* CELL_SIZE;
	        do{
        if(getpixel(xLeft, yTop) == BOARD_COLOR )
            maxNbCells--;
        else freeRoute=0;
            }while( maxNbCells >= 1 && freeRoute);
        }
	       break;
	  }
    }
// check if Box block can be moved to the left
void checkTranslateBoxRouteLeft(int orientation, int xLeft, int yTop, int &
freeRoute)
      {      int maxNbCells=2;
	  // check if route is not blocked
	  yTop = yTop + CELL_SIZE/2;
	  freeRoute = 1; //route is free
      xLeft = xLeft - CELL_SIZE/2;
	       do{
        if (getpixel(xLeft, yTop) == BOARD_COLOR){
            yTop = yTop + CELL_SIZE;
		    maxNbCells--;
        }
        else freeRoute = 0;
            }while ( maxNbCells >= 1 && freeRoute);
    }

// check if Bar block can be moved to the right
void checkTranslateBarRouteRight(int orientation, int xLeft, int yTop, int &
freeRoute)
      {      int maxNbCells;
	  // check if route is not blocked

	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL:
	       // maxNbCells = 1;
	       yTop = yTop + CELL_SIZE/2;
	       xLeft = xLeft + 4*CELL_SIZE + CELL_SIZE/2;
	       if (getpixel(xLeft, yTop) != BOARD_COLOR)
		    freeRoute = 0;
	       break;

	    case VERTICAL:
	       maxNbCells = 4;
	       yTop = yTop + CELL_SIZE/2;
	       xLeft  = xLeft + CELL_SIZE + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
    }
// check if L block can be moved to the right
void checkTranslateLRouteRight(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 2;
	       xLeft  = xLeft +3*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop +CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop +CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;

	    case HORIZONTAL_TOP:
	       maxNbCells = 2;
	       xLeft  = xLeft +CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft +2*CELL_SIZE;
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       maxNbCells = 3;
	       xLeft  = xLeft+2*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       //maxNbCells = 2;
	       xLeft  = xLeft+2*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
		if (getpixel(xLeft, yTop) == BOARD_COLOR );
		else  freeRoute = 0; // route is blocked
        if(freeRoute){
            maxNbCells=2;
            xLeft  = xLeft-CELL_SIZE;
            yTop = yTop + CELL_SIZE;
	        do{
        if(getpixel(xLeft, yTop) == BOARD_COLOR ){
            yTop = yTop + CELL_SIZE;
            maxNbCells--;
        }
        else freeRoute=0;
            }while( maxNbCells >= 1 && freeRoute);
        }
	       break;
	  }
    }


//surafel fantu
// check if Lr block can be moved to the right
void checkTranslateLrRouteRight(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 2;
	       xLeft  = xLeft +CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop +CELL_SIZE+ CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop - CELL_SIZE;
		    xLeft  = xLeft +2* CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;

	    case HORIZONTAL_TOP:
	       maxNbCells = 2;
	       xLeft  = xLeft +3*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       maxNbCells = 3;
	       xLeft  = xLeft+2*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
        if(freeRoute){
            maxNbCells=1;
            xLeft  = xLeft+CELL_SIZE;
	        do{
        if(getpixel(xLeft, yTop) == BOARD_COLOR )
            maxNbCells--;
        else freeRoute=0;
            }while( maxNbCells >= 1 && freeRoute);
        }
	       break;
	  }
    }

// check if T block can be moved to the right
void checkTranslateTRouteRight(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 2;
	       xLeft  = xLeft +3*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    xLeft  = xLeft - CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;

	    case HORIZONTAL_TOP:
	       maxNbCells = 2;
	       xLeft  = xLeft +2*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       maxNbCells = 3;
	       xLeft  = xLeft+2*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + 2* CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
        if(freeRoute){
            maxNbCells=1;
            xLeft  = xLeft+CELL_SIZE;
	        yTop = yTop -3*CELL_SIZE;
	        do{
        if(getpixel(xLeft, yTop) == BOARD_COLOR )
            maxNbCells--;
        else freeRoute=0;
            }while( maxNbCells >= 1 && freeRoute);
        }
	       break;
	  }
    }
// check if Box block can be moved to the right
void checkTranslateBoxRouteRight(int orientation, int xLeft, int yTop, int &
freeRoute)
      {      int maxNbCells=2;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	       yTop = yTop + CELL_SIZE/2;
	       xLeft = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
	          do{
        if (getpixel(xLeft, yTop) == BOARD_COLOR){
            yTop = yTop + CELL_SIZE;
		    maxNbCells--;
        }
        else freeRoute = 0;
            }while ( maxNbCells >= 1 && freeRoute);
    }

// check if Bar block can be moved down
void checkTranslateBarRouteDown(int orientation, int xLeft, int yTop, int &
freeRoute)
      {      int maxNbCells;
	  // check if route is not blocked
	  xLeft = xLeft + CELL_SIZE/2;
	  freeRoute = 1; //route is not blocked
	  switch(orientation) {
	   case HORIZONTAL:
	       maxNbCells = 4;
	       yTop  = yTop + CELL_SIZE + CELL_SIZE/2;
	       do
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    xLeft = xLeft + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       while ( maxNbCells >= 1 && freeRoute);
	       break;

	   case VERTICAL:
	       yTop = yTop + 4*CELL_SIZE + CELL_SIZE/2;
	       if (getpixel(xLeft, yTop) != BOARD_COLOR) freeRoute = 0;
	       break;
	  }
    }
// check if L block can be moved to the down
void checkTranslateLRouteDown(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 1;
	       xLeft  = xLeft+2*CELL_SIZE+CELL_SIZE/2;
	       yTop = yTop + 2*CELL_SIZE + CELL_SIZE/2;
		if (getpixel(xLeft, yTop) == BOARD_COLOR );
		else  freeRoute = 0; // route is blocked
        if(freeRoute){
            maxNbCells=2;
            xLeft  = xLeft-CELL_SIZE;
            yTop = yTop - CELL_SIZE;
            do{
         if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft-CELL_SIZE;
            maxNbCells--;
         }
         else freeRoute = 0;
            }while ( maxNbCells >= 1 && freeRoute);
        }
	       break;

	    case HORIZONTAL_TOP:
	       maxNbCells = 3;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop+2*CELL_SIZE +CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
           yTop = yTop + 3*CELL_SIZE+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
            yTop = yTop -2*CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop +3*CELL_SIZE+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
    }
// check if Lr block can be moved to the down
void checkTranslateLrRouteDown(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE +CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    xLeft  = xLeft + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
        if(freeRoute){
            maxNbCells=1;
            xLeft  = xLeft-3*CELL_SIZE;
            yTop = yTop + CELL_SIZE;
            do{
         if (getpixel(xLeft, yTop) == BOARD_COLOR )
            maxNbCells--;
         else freeRoute = 0;
            }while ( maxNbCells >= 1 && freeRoute);
        }
	       break;

	    case HORIZONTAL_TOP:
	       maxNbCells = 3;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop +2* CELL_SIZE+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
           yTop = yTop + 3*CELL_SIZE+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop +CELL_SIZE+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + 2*CELL_SIZE;
		    xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
    }
// check if T block can be moved to the down
void checkTranslateTRouteDown(int orientation, int xLeft, int yTop, int &
freeRoute){
     int maxNbCells;
	  // check if route is not blocked
	  freeRoute = 1; //route is free
	  switch (orientation) {
	    case HORIZONTAL_BOTTOM:
	        maxNbCells = 2;
	       xLeft  = xLeft +CELL_SIZE/2;
	       yTop = yTop + CELL_SIZE + CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    xLeft  = xLeft +2* CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
        if(freeRoute){
            maxNbCells=1;
            xLeft  = xLeft-3*CELL_SIZE;
            yTop = yTop + CELL_SIZE;
            do{
         if (getpixel(xLeft, yTop) == BOARD_COLOR )
            maxNbCells--;
         else freeRoute = 0;
            }while ( maxNbCells >= 1 && freeRoute);
        }
	       break;

	    case HORIZONTAL_TOP:
	       maxNbCells = 3;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop +2* CELL_SIZE+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_RIGHT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
           yTop = yTop + 3*CELL_SIZE+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
            xLeft  = xLeft+CELL_SIZE;
            yTop = yTop - CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
	       break;
        case VERTICAL_LEFT:
	       maxNbCells = 2;
	       xLeft  = xLeft+CELL_SIZE/2;
	       yTop = yTop +2*CELL_SIZE+CELL_SIZE/2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    yTop = yTop + CELL_SIZE;
		    xLeft  = xLeft+CELL_SIZE;
		    maxNbCells--;
            }
		else  freeRoute = 0; // route is blocked
            }while ( maxNbCells >= 1 && freeRoute);
	       break;
	  }
    }
// check if Box block can be moved down
void checkTranslateBoxRouteDown(int orientation, int xLeft, int yTop, int &
freeRoute)
      {      int maxNbCells;
	  // check if route is not blocked
	  xLeft = xLeft + CELL_SIZE/2;
	  yTop  = yTop + 2 * CELL_SIZE + CELL_SIZE/2;
	  freeRoute = 1; //route is not blocked
	       maxNbCells = 2;
	       do{
		if (getpixel(xLeft, yTop) == BOARD_COLOR ){
		    xLeft = xLeft + CELL_SIZE;
		    maxNbCells--;
		}
		else  freeRoute = 0; // route is blocked
	       }while ( maxNbCells >= 1 && freeRoute);
      }
// Invoke the appropriate checking function for Bar block depending on the direction
int checkTranslateBarRoute(int orientation, int xLeft, int yTop,
		int direction)
{    int maxNbCells, freeRoute = 1;
     switch (direction) {
       case RIGHT: checkTranslateBarRouteRight(orientation, xLeft, yTop,
freeRoute); break;
       case LEFT:  checkTranslateBarRouteLeft(orientation, xLeft, yTop,
freeRoute); break;
       case DOWN:  checkTranslateBarRouteDown(orientation, xLeft, yTop,
freeRoute); break;
     }
     return freeRoute;
  }
// Invoke the appropriate checking function for L block depending on the direction
int checkTranslateLRoute(int orientation, int xLeft, int yTop,
		int direction)
{    int maxNbCells, freeRoute = 1;
     switch (direction) {
       case RIGHT: checkTranslateLRouteRight(orientation, xLeft, yTop,
freeRoute); break;
       case LEFT:  checkTranslateLRouteLeft(orientation, xLeft, yTop,
freeRoute); break;
       case DOWN:  checkTranslateLRouteDown(orientation, xLeft, yTop,
freeRoute); break;
     }
     return freeRoute;
  }
// Invoke the appropriate checking function for Lr block depending on the direction
int checkTranslateLrRoute(int orientation, int xLeft, int yTop,
		int direction)
{    int maxNbCells, freeRoute = 1;
     switch (direction) {
       case RIGHT: checkTranslateLrRouteRight(orientation, xLeft, yTop,
freeRoute); break;
       case LEFT:  checkTranslateLrRouteLeft(orientation, xLeft, yTop,
freeRoute); break;
       case DOWN:  checkTranslateLrRouteDown(orientation, xLeft, yTop,
freeRoute); break;
     }
     return freeRoute;
  }
// Invoke the appropriate checking function for T block depending on the direction
int checkTranslateTRoute(int orientation, int xLeft, int yTop,
		int direction)
{    int maxNbCells, freeRoute = 1;
     switch (direction) {
       case RIGHT: checkTranslateTRouteRight(orientation, xLeft, yTop,
freeRoute); break;
       case LEFT:  checkTranslateTRouteLeft(orientation, xLeft, yTop,
freeRoute); break;
       case DOWN:  checkTranslateTRouteDown(orientation, xLeft, yTop,
freeRoute); break;
     }
     return freeRoute;
  }
// Invoke the appropriate checking function for Box block depending on the direction
int checkTranslateBoxRoute(int orientation, int xLeft, int yTop,
		int direction)
{    int maxNbCells, freeRoute = 1;
     switch (direction) {
       case RIGHT: checkTranslateBoxRouteRight(orientation, xLeft, yTop,
freeRoute); break;
       case LEFT:  checkTranslateBoxRouteLeft(orientation, xLeft, yTop,
freeRoute); break;
       case DOWN:  checkTranslateBoxRouteDown(orientation, xLeft, yTop,
freeRoute); break;
     }
     return freeRoute;
  }

// translate the Bar block
void translateBarBlock(int orientation, int & xLeft, int & yTop, int fillingColor,
	int direction)
  {
     // Erase the bar at current position
     drawBarBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction) {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     // Now redraw the bar at the new position
     drawBarBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
  }

// translate the L block
void translateLBlock(int orientation, int & xLeft, int & yTop, int fillingColor,
	int direction)
  {
     // Erase the L at current position
     drawLBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction) {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     // Now redraw the L at the new position
     drawLBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
  }
//surafel fantu
// translate the Lr block
void translateLrBlock(int orientation, int & xLeft, int & yTop, int fillingColor,
	int direction)
  {
     // Erase the Lr at current position
     drawLrBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction) {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     // Now redraw the Lr at the new position
     drawLrBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
  }
//surafel fantu
// translate the T block
void translateTBlock(int orientation, int & xLeft, int & yTop, int fillingColor,
	int direction)
  {
     // Erase the T at current position
     drawTBlock(xLeft, yTop, orientation, BKGRD_COLOR);
     switch (direction) {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     // Now redraw the T at the new position
     drawTBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
  }
// translate the Box block
void translateBoxBlock(int orientation, int & xLeft, int & yTop, int fillingColor,
	int direction)
  {
     // Erase the box at current position
     drawBoxBlock(xLeft, yTop,BKGRD_COLOR);
     switch (direction) {
       case RIGHT: xLeft = xLeft + CELL_SIZE; break;
       case LEFT : xLeft = xLeft - CELL_SIZE; break;
       case DOWN : yTop = yTop + CELL_SIZE;   break;
     }
     // Now redraw the Box at the new position
     drawBoxBlock(xLeft, yTop,fillingColor /*FRGRD_COLOR*/);
  }

// Invoke the appropriate route checking function for translation depending on block Id
int translateRouteFree(int blockId, int orientation, int xLeft, int yTop,
				int direction)
 { int freeRoute;
    switch(blockId) {
      case T_BLOCK  : freeRoute =
	     checkTranslateTRoute(orientation, xLeft, yTop, direction); break;
      case L_BLOCK  : freeRoute =
          checkTranslateLRoute(orientation, xLeft, yTop, direction); break;
      case LR_BLOCK : freeRoute =
         checkTranslateLrRoute(orientation, xLeft, yTop, direction); break;
      case BOX_BLOCK: freeRoute =
	     checkTranslateBoxRoute(orientation, xLeft, yTop, direction); break;
      case BAR_BLOCK: freeRoute =
	     checkTranslateBarRoute(orientation, xLeft, yTop, direction);
	     break;
    }
    return freeRoute;
  }

// Invoke the appropriate function for translation depending on block Id
void translateBlock(int blockId, int & orientation, int & xLeft, int & yTop,
				      int fillingColor, int direction)
  {
    switch(blockId) {
      case T_BLOCK  :
      translateTBlock(orientation, xLeft, yTop, fillingColor, direction); break;
      case L_BLOCK  :
      translateLBlock(orientation, xLeft, yTop, fillingColor, direction); break;
      case LR_BLOCK :
      translateLrBlock(orientation, xLeft, yTop, fillingColor, direction); break;
      case BOX_BLOCK:
      translateBoxBlock(orientation, xLeft, yTop, fillingColor, direction); break;
      case BAR_BLOCK:
	  translateBarBlock(orientation, xLeft, yTop, fillingColor, direction); break;
    }
  }

// Check if a Bar block can be rotated
int checkRotateBarRoute(int orientation, int xLeft, int yTop)
  {  int maxNbCells, x, y, freeRoute;
     switch (orientation) {
      case HORIZONTAL:
	// Checking upper three cells
	maxNbCells = 3;
	freeRoute = 1;
	x = xLeft + CELL_SIZE + CELL_SIZE/2;
	y = yTop  + CELL_SIZE + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	      x = x + CELL_SIZE;
	      maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	while (maxNbCells >=1 && freeRoute);

	// Checking lower three cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 3;
	   freeRoute = 1;
	   x = xLeft + CELL_SIZE   + CELL_SIZE/2;
	   y = yTop  + 2*CELL_SIZE + CELL_SIZE/2;
	   do
	   if (getpixel(x, y) == BOARD_COLOR ){
	       x = x + CELL_SIZE;
	       maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	   while (maxNbCells >=1 && freeRoute);
	}
	break;

      case VERTICAL:
	// Checking left two cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft - CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do
	   if (getpixel(x, y) == BOARD_COLOR ){
	    y = y + CELL_SIZE;
	    maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	while (maxNbCells > 0 && freeRoute);

	// Checking middle three cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 3;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   while (maxNbCells > 0 && freeRoute);
	}

	// right most three cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 3;
	   freeRoute = 1;
	   x = xLeft + 2*CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE   + CELL_SIZE/2;
	   do
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   while (maxNbCells > 0 && freeRoute);
	}
	break;
     }
     return freeRoute;
  }
// Check if a L block can be rotated
int checkRotateLRoute(int orientation, int xLeft, int yTop)
  {  int maxNbCells, x, y, freeRoute;
     switch (orientation) {
      case HORIZONTAL_BOTTOM:
	// Checking upper two cells
	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft+CELL_SIZE/2;
	y = yTop-CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
	      x = x + CELL_SIZE;
	      maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells >=1 && freeRoute);
        if(freeRoute){// if route is so far free
            maxNbCells = 2;
            freeRoute  = 1;
            x = xLeft + CELL_SIZE/2;
            y = yTop+CELL_SIZE+CELL_SIZE/2;
        do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     x = x + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
        }
        break;
      case VERTICAL_LEFT:
	// Checking the left two  cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft+ CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            y=y+CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking the right two cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft+2*CELL_SIZE + CELL_SIZE/2;
	   y = yTop +CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
	 break;
	case HORIZONTAL_TOP:
	// Checking  upper two cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft+ CELL_SIZE + CELL_SIZE/2;
	y = yTop + CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            x = x + CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking lower two cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + 2* CELL_SIZE + CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     x = x + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
    break;

     case VERTICAL_RIGHT:
	// Checking the left two  cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft - CELL_SIZE/2;
	y = yTop  +CELL_SIZE+ CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            y = y+CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking the right two cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop+ CELL_SIZE +CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y= y +CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
    break;
     }
     return freeRoute;
  }
// Check if a Lr block can be rotated
int checkRotateLrRoute(int orientation, int xLeft, int yTop)
  {  int maxNbCells, x, y, freeRoute;
     switch (orientation) {
      case HORIZONTAL_BOTTOM:
	// Checking lower two cells
	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft+CELL_SIZE + CELL_SIZE/2;
	y = yTop  + CELL_SIZE + CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
	      x = x + CELL_SIZE;
	      maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells >=1 && freeRoute);
        if(freeRoute){// if route is so far free
            maxNbCells = 2;
            freeRoute  = 1;
            x = xLeft + CELL_SIZE/2;
            y = yTop  - CELL_SIZE/2;
        do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     x = x + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
        }
        break;
      case VERTICAL_LEFT:
	// Checking the right two  cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft+2*CELL_SIZE + CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            y=y+CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking the left two cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE/2;
	   y = yTop + CELL_SIZE+ CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
	 break;
	case HORIZONTAL_TOP:
	// Checking  upper two cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft + CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            x = x + CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking lower two cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + 2* CELL_SIZE + CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     x = x + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
    break;

     case VERTICAL_RIGHT:
	// Checking  two left cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft - CELL_SIZE/2;
	y = yTop  +CELL_SIZE+ CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            y = y+CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking lower two cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  +CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y= y +CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
    break;
     }
     return freeRoute;
  }
// Check if a T block can be rotated
int checkRotateTRoute(int orientation, int xLeft, int yTop)
  {  int maxNbCells, x, y, freeRoute;
     switch (orientation) {
      case HORIZONTAL_BOTTOM:
	// Checking lower two cells
	maxNbCells = 2;
	freeRoute = 1;
	x = xLeft + CELL_SIZE/2;
	y = yTop  + CELL_SIZE + CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
	      x = x + 2*CELL_SIZE;
	      maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells >=1 && freeRoute);

	break;
      case VERTICAL_LEFT:
	// Checking two left cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft + CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            y=y+2*CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking two right cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + 2 * CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y = y + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
	 break;
	case HORIZONTAL_TOP:
	// Checking  upper two cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft + CELL_SIZE/2;
	y = yTop  + CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            x = x +2* CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking lower two cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  + 2* CELL_SIZE + CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     x = x + CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
    break;

     case VERTICAL_RIGHT:
	// Checking  two left cells
	maxNbCells = 2;
	freeRoute = 1; // assume route is free
	x = xLeft - CELL_SIZE/2;
	y = yTop  +CELL_SIZE+ CELL_SIZE/2;
	do{
	   if (getpixel(x, y) == BOARD_COLOR ){
            y = y+CELL_SIZE;
            maxNbCells--;
	   }
	   else  freeRoute = 0; // route is blocked
	}while (maxNbCells > 0 && freeRoute);

	// Checking lower two cells
	if (freeRoute) { // if route is so far free
	   maxNbCells = 2;
	   freeRoute  = 1;
	   x = xLeft + CELL_SIZE + CELL_SIZE/2;
	   y = yTop  +CELL_SIZE/2;
	   do{
	  if (getpixel(x, y) == BOARD_COLOR ){
	     y= y +2* CELL_SIZE;
	     maxNbCells--;
	  }
	  else  freeRoute = 0; // route is blocked
	   }while (maxNbCells > 0 && freeRoute);
	}
    break;
     }
     return freeRoute;
  }

// Invoke the appropriate route checking function for rotation depending on block Id
int rotateRouteFree(int blockId, int orientation, int xLeft, int yTop)
   {   int freeRoute;
       switch(blockId) {
      case T_BLOCK  :
        freeRoute = checkRotateTRoute(orientation, xLeft, yTop);
        break;
      case L_BLOCK  :
        freeRoute = checkRotateLRoute(orientation, xLeft, yTop);
        break;
      case LR_BLOCK :
        freeRoute = checkRotateLrRoute(orientation, xLeft, yTop);
	    break;
      case BOX_BLOCK: break;
      case BAR_BLOCK:
	   freeRoute = checkRotateBarRoute(orientation, xLeft, yTop);
	   break;
       }
       return freeRoute;
  }

// Rotate the Bar block
void rotateBarBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
 {
   // Erase the bar at current position
   drawBarBlock(xLeft, yTop, orientation, BKGRD_COLOR);
   // Now compute the new location
   switch (orientation) {
     case HORIZONTAL:
       orientation = VERTICAL;
       xLeft = xLeft + CELL_SIZE;
       yTop  = yTop  - CELL_SIZE;
       break;

     case VERTICAL:
       orientation = HORIZONTAL;
       xLeft = xLeft - CELL_SIZE;
       yTop  = yTop  + CELL_SIZE;
       break;
   }
   // Now redraw the bar at the new position
   drawBarBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
 }

// Rotate the L block
void rotateLBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
 {
   // Erase the L at current position
   drawLBlock(xLeft, yTop, orientation, BKGRD_COLOR);
   // Now compute the new location
   switch (orientation) {
     case HORIZONTAL_BOTTOM:
       orientation = VERTICAL_LEFT;
       xLeft = xLeft + CELL_SIZE;
       yTop  = yTop  - CELL_SIZE;
       break;
     case VERTICAL_LEFT:
       orientation = HORIZONTAL_TOP;
       break;
      case HORIZONTAL_TOP:
       orientation = VERTICAL_RIGHT;
       xLeft = xLeft + CELL_SIZE;
       break;
      case VERTICAL_RIGHT:
        orientation = HORIZONTAL_BOTTOM;
        xLeft = xLeft - CELL_SIZE;
        yTop  = yTop  + CELL_SIZE;
        break;
   }
   // Now redraw the Lr at the new position
   drawLBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
 }


// Rotate the Lr block
void rotateLrBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
 {
   // Erase the Lr at current position
   drawLrBlock(xLeft, yTop, orientation, BKGRD_COLOR);
   // Now compute the new location
   switch (orientation) {
     case HORIZONTAL_BOTTOM:
       orientation = VERTICAL_LEFT;
       yTop  = yTop  - CELL_SIZE;
       break;

     case VERTICAL_LEFT:
       orientation = HORIZONTAL_TOP;
       break;
      case HORIZONTAL_TOP:
       orientation = VERTICAL_RIGHT;
       xLeft = xLeft + CELL_SIZE;
       break;
      case VERTICAL_RIGHT:
        orientation = HORIZONTAL_BOTTOM;
        xLeft = xLeft - CELL_SIZE;
        yTop  = yTop  + CELL_SIZE;
        break;
   }
   // Now redraw the Lr at the new position
   drawLrBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
 }

// Rotate the T block
void rotateTBlock(int & orientation, int & xLeft, int & yTop, int fillingColor)
 {
   // Erase the T at current position
   drawTBlock(xLeft, yTop, orientation, BKGRD_COLOR);
   // Now compute the new location
   switch (orientation) {
     case HORIZONTAL_BOTTOM:
       orientation = VERTICAL_LEFT;
       yTop  = yTop  - CELL_SIZE;
       break;

     case VERTICAL_LEFT:
       orientation = HORIZONTAL_TOP;
       break;
      case HORIZONTAL_TOP:
       orientation = VERTICAL_RIGHT;
       xLeft = xLeft + CELL_SIZE;
       break;
      case VERTICAL_RIGHT:
        orientation = HORIZONTAL_BOTTOM;
        xLeft = xLeft - CELL_SIZE;
        yTop  = yTop  + CELL_SIZE;
        break;
   }
   // Now redraw the T at the new position
   drawTBlock(xLeft, yTop, orientation, fillingColor /*FRGRD_COLOR*/);
 }
// Invokes the appropriate rotating function depending on the block Id
void rotateBlock(int blockId, int & orientation, int & xLeft, int & yTop,
			int fillingColor)
  {
       switch(blockId) {
      case T_BLOCK  :
      rotateTBlock(orientation, xLeft, yTop, fillingColor);
	  break;
      case L_BLOCK  :
      rotateLBlock(orientation, xLeft, yTop, fillingColor);
	  break;
      case LR_BLOCK :
      rotateLrBlock(orientation, xLeft, yTop, fillingColor);
	  break;
      case BOX_BLOCK:
      case BAR_BLOCK:
	  rotateBarBlock(orientation, xLeft, yTop, fillingColor);
	  break;
       }
  }

void pullDown(int x, int y){
    for(int i=1; i<=10; i++){
        setfillstyle(SOLID_FILL, getpixel(x+(0.5*CELL_SIZE), y-(0.5*CELL_SIZE)));
        bar(x,y,x+CELL_SIZE,y+CELL_SIZE);
        x+=CELL_SIZE;
    }
}

int checkRow(double x, double y){
int chk = 1;
    for(int i = 1; i<=10; i++){
        if(getpixel(x,y)==BOARD_COLOR)
            chk=0;
    x+=CELL_SIZE;
    }
    return chk;
}

int FullRowNumber(int x,int y){
    int cnt = 0;
    for(int i = 0; i<15; i++){
        if(checkRow(x,y))
            cnt++;
    y-=CELL_SIZE;
    }
    return cnt;
}

void deleteRow(int &scoreup){
scoreup = 0;
int ptx = LEFTCORNER+CELL_SIZE;
int pty = TOPCORNER + (14*CELL_SIZE);
int centerx = ptx+(0.5*CELL_SIZE);
int centery = pty+(0.5*CELL_SIZE);
int cnt = FullRowNumber(centerx, centery);
scoreup = cnt;
int tpty = pty;
int tcentery = centery;
int j = 0;
while(cnt>0){
    for (j = 0; j<15; j++){ //to know which row
        if (checkRow(centerx,centery)){//check every row
            for (int i = 0; i <(15-j); i++){//not to pass the top limit
                    pullDown(ptx, pty-(j*CELL_SIZE));
                    if(i==14)
                        Beep(1000,50);
                    pty-=CELL_SIZE;//iterate up
                }

        pty=tpty;//to redo
        }
        centery-=CELL_SIZE;
    }
    centery=tcentery;
    cnt--;
}
fillGrid();
Beep(1000,50);
}
// Invokes the appropriate function depending on the arrow key pressed
void handleUserInput(int blockId, int & orientation,
				int & xLeft, int & yTop, int fillingColor, int key,bool &drop)
 {
  switch(key) {
     case LEFTARROW:
	  if (translateRouteFree(blockId,orientation, xLeft, yTop, LEFT))
	       translateBlock(blockId, orientation, xLeft, yTop, fillingColor, LEFT); break;
     case RIGHTARROW:
	  if (translateRouteFree(blockId,orientation, xLeft, yTop, RIGHT))
	       translateBlock(blockId, orientation, xLeft, yTop, fillingColor, RIGHT); break;
     case UPARROW:
	  if (rotateRouteFree(blockId, orientation, xLeft, yTop))
	  rotateBlock(blockId, orientation, xLeft, yTop, fillingColor); break;
     case DOWNARROW:// it accelerates a falling block
	  drop=true;
	  break;
      }
 }
// checks whether the game is over or not
int gameOver()
      {      int xLeft, yTop, maxNbCells, gOver;
	  // check if the top middle two/four cells are not covered
	  yTop  = TOPCORNER + CELL_SIZE /2;
	  xLeft = LEFTCORNER + 4*CELL_SIZE + CELL_SIZE/2;
	  maxNbCells = 2;  // or 4
	  gOver = 0;   // game is not over
	  while ( maxNbCells >= 1 && !gOver)
	   if (getpixel(xLeft, yTop) == BOARD_COLOR ){
	       xLeft = xLeft + CELL_SIZE;
	       maxNbCells--;
	   } else  gOver = 1; // game is over
	  return gOver;
      }

// checks confirmation of ESCAPE
int escapeConfirmed()
  {    char ans;
       displayInfo("Are you sure you want to Exit [Y/N] ?>");
       do
	 ans=toupper(char(getch()));
       while (ans != 'Y' && ans != 'N');
       if(ans == 'Y') return 1;
       else  return 0;
  }
// falls a block until it touches "ground"
int freeFall(int blockId, int orientation, int & xLeft, int & yTop,int fillingColor,int score,int level_speed)
{

int levelUP;
//acceleration
if (score < 5000 ) {levelUP = level_speed;}
else if (score > 5000 && score<10000) {level_speed = 500; levelUP = level_speed;}
else if (score > 10000&& score<15000) {level_speed = 200; levelUP = level_speed;}
else {level_speed = 77; levelUP = level_speed;}

  int fallBlocked = 0;
     if (translateRouteFree(blockId, orientation, xLeft, yTop, DOWN)) {
	translateBlock(blockId, orientation, xLeft, yTop, fillingColor, DOWN);
	delay(levelUP); //Levels can be introduced
     } else fallBlocked = 1;
    return fallBlocked;
 }
void sound()
  {
    for(int i=400;i>0;i-=100)
        Beep(600-i,300);
}

int pause_game()
  {    char ans;
   displayInfo((char*)"Game is paused PRESS C to continue");
       do{
	 ans=toupper(char(getch()));}
       while (ans != 'C');
       switch(ans){
       case 'C':  {return 1; break;
       default:  return 0; break;
       }
  }
  }
// Controls the overall logic of the game
void playGame()
  {
int score = 0, totscore, level,level_speed; bool OT = TRUE;
int currentBlock,predictedBlock, currentOrientation, predictedOrientation, key;
int xLeftCurrent, yTopCurrent, fillingColor, predictedColor, fallBlocked;
while(OT){//to execute this only once
    displayScore(score);
    UpcomingBlock(&currentBlock, currentOrientation, fillingColor);
     OT = FALSE;
}
bool drop;
sound();
do {
    int scoreup;
    displayInfo((char*)"press ESC to abort the game");

    generateNewBlock(&currentBlock, &currentOrientation, &xLeftCurrent, &yTopCurrent, &fillingColor);
    UpcomingBlock(&predictedBlock, predictedOrientation, predictedColor);
    drawUpcomingBlock(&predictedBlock, predictedOrientation, predictedColor);
	drop=false;
  do { // loop as long as the current block is falling down
   do{
    if(drop)  level_speed=25;
    else level_speed=800;
    fallBlocked = freeFall(currentBlock, currentOrientation, xLeftCurrent,
yTopCurrent, fillingColor,score,level_speed);
   }while (!kbhit() && !fallBlocked);
   if (!fallBlocked) { // ie. key is pressed
    key=getch();
    switch(key) {
      case ESC:   if (!escapeConfirmed()) key = 1; break;
      case SPACE:int p;  p=pause_game(); if (p==TRUE) displayInfo((char*)"press ESC to abort the game");   break;
      case '\0' : { // Key is not int the 256 ASCII table
      key = getch();
      handleUserInput(currentBlock, currentOrientation, xLeftCurrent,
	yTopCurrent, fillingColor, key,drop);

     }
   }
  }
  else if(fallBlocked){
      deleteRow(scoreup);
      score+=scoreup*1000;
      if (score<5000) level = 1;
      else if (score<10000) level = 2;
      else level = 3;
      displayScore(score, level);
      delay(1000);
      clearScoreArea();
  }
  }while (key != ESC && !fallBlocked);
  currentBlock = predictedBlock;
    currentOrientation = predictedOrientation;
    fillingColor = predictedColor;
       //std::cin.ignore(kbhit());
 }while (key != ESC && !gameOver());
}
// Launchs the game
int main() {
    int key;
    initGraphEngine();
    do {
     game_name();
     drawBoard();
     // clearKeyBoard(); // clears any previously pressed key strokes
     clearDisplayArea();
     displayInfo("press ENTER key to play or ESC to Exit");
     key=getch();
     switch(key) {
       case ESC:
	  if (!escapeConfirmed()) key = 1; // to erase ESCAPE
	  break;
       case ENTER:
	  playGame();
	  displayInfo("Game Over!!! Press any key ---> ");
	  getch();
	  break;
     }
    } while (key != ESC); // this is to exit from the program
    displayInfo ("Come Again ... ");
    delay(1000);
    return 0;
}



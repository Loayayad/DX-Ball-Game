#include "HeaderFile.h"
#include "Nokia5110.h"
#include "..//tm4c123gh6pm.h"
#include "TExaS.h"
#include "time.h"
#include "stdlib.h"
// ---------------------------------------------------------------------------
// ------------------ The Directions of the Ball -----------------------------
/*
- d = 0 : North - East 
- d = 1 : North
- d = 2 : North-East
- d = 3 : South-East
- d = 4 : South
- d = 5 : South-west
- default : North west
*/
// ---------------------------------------------------------------------------
// ------------------ ball_move ----------------------------------------------
// z will equal to zero in case of the next cell be empty cell, this not affect the state of the cell
// and the ball continue movving on its way.
void ball_move (){
	switch (d){
		// z holds the current state of the ball. check the current state of the ball.
		// and then the state be changed.
		int z;
		// ------------------------------- CASE 0 / UP LEFT ----------------------
		case 0:
			z = ball_checkState(y-1, x-1);
	    SwitchStates(z);
			if(z == 0){ y--; x--; }
			break;
		// ------------------------------- CASE 1 / UP  --------------------------
		case 1:
			z = ball_checkState(y-1, x);
			SwitchStates(z);
			if(z == 0){ y--; }
			break;
		// ------------------------------- CASE 2 / UP RIGHT  --------------------
		case 2:
			z = ball_checkState(y-1, x+1);
			SwitchStates(z);
			if(z == 0){ y--; x++; }
			break;
		// ------------------------------- CASE 3 / DOWN LEFT  -------------------
		case 3:
			z = ball_checkState(y+1, x-1);
			SwitchStates(z);
			if(z == 0){ y++; x--; }
			break;
	  // ------------------------------- CASE 4 / DOWN   -----------------------
			case 4:
				z = ball_checkState(y+1, x);
				SwitchStates(z);
				if(z == 0){ y++; }
				break;
		// ------------------------------- CASE 5 / DOWN RIGHT  -----------------------
			case 5:
				z = ball_checkState(y+1, x+1);
			  SwitchStates(z);
			  if(z == 0){ y++; x++; }
			break;
		
			default: break;
	}
}

//-----------------------------------------------------------------------------------------
//------------------------------------ ball_init ------------------------------------------
// at start, the direction be north, and x, y be in center of screen.
void ball_init (){
	d = 1;
	x = 10;
	y = 9;
}
//-----------------------------------------------------------------------------------------
//------------------------------------ ball_initlevel -------------------------------------
// at start, score is 0, total lifes is 3 and initial level is 1.
void ball_initlevel(){
	score = 0;
	lifes = 3;
	level = 1;
}
//-----------------------------------------------------------------------------------------
//------------------------------------ ball_ChangeDir -------------------------------------
// states of the ball movement:
// state = 1 -> hits a cell to get its score.
// state = 2 -> hits the bunker to go up.
// state = 3 -> if hits any side of screen, move in same direction.
// state = 4 -> if hits the upper bound of the screen, go down.
/*
More about rand() method:
-------------------------
rand() function is used in C to generate random numbers.
If we generate a sequence of random number with rand() function, it will create the same sequence again 
and again every time program runs. Say if we are generating 5 random numbers in C with the help of rand() 
in a loop, then every time we compile and run the program our output must be the same sequence of numbers.
*/
void ball_ChangeDir(unsigned int state){
	// if hits a cell to get its score.
	if(state == 1){
		// if d was any north .. go south randomly.
		if(d <= 2) 
			d = rand()%3 + 3; // move the ball down.
		else d = rand()%3;  // move the ball up.
	}
	
	// if hits the bunker, go up.
	if(state == 2) d = rand()%3; // move the ball up.
	
	// if hits the upper bound of the screen, go down.
	if(state == 4) d = rand()%3 + 3; // move the ball down. 
	
	// if hits any side of screen, move in same direction.
	if(state == 3){
		if(d > 2)
			d = rand()%3 + 3; // move the ball down.
		else d = rand()%3;  // move the ball up.
	}
}
//-----------------------------------------------------------------------------------------
//------------------------------------ ball_increaseScore ---------------------------------
void ball_increaseScore(){ score += 15*level; }
//-----------------------------------------------------------------------------------------
//------------------------------------ ball_init ------------------------------------------
int ball_checkState(int y,int x){
	// The ball moved down the bunker -> game over.
	if(y >= GRIDH) { return -1; }
	
	// The ball hits the top border of screen.
	if(y <= 0)   	 { return 4;  }

	// The next cell is out of the screen borders.
	if(x >= GRIDW || x < 0 ) { return 3; }  
	
	// The next state is an empty cell.
	if(screen[y][x] == 0) { return 0; } 
	
	// The cell is exist in the above cells to be shoted, take its score and make the cell empty.
	// the prev state was 1, the future state will be 0.
	if(screen[y][x] == 1){
		screen[y][x] = 0; 
		ball_increaseScore(); 
		return 1;
	}
	
	// The ball hits the bunker.
	if(screen[y][x] == 2) { return 2; }
	
	// if non of the prev cases happened.
	return -1;
}
//-----------------------------------------------------------------------------------------
//------------------------------------ ball_deleteCell ------------------------------------
// any cell will be deleted only in one case, if the ball touched this cell, then the score will be increased.
// the method checks the state of the surrounding cells around the ball at the time when the ball hits the cells
// if any of them is in touch with the ball, the score will be increased and the cell state will be changed to empty.
// all surrounding possibilities are: (y, x-1) / (y, x+1) / (y+1, x) / (y-1, x)
void ball_deleteCell(){
	if( ball_checkState(y, x-1) == 1 ){
		screen[y][x-1] = 0;
		ball_increaseScore();
	}
	
	if( ball_checkState(y, x+1) == 1){
		screen[y][x+1]=0;
		ball_increaseScore();
	}
	
	if( ball_checkState(y+1, x) == 1){
		screen[y+1][x] = 0;
		ball_increaseScore();
	}
	
	if( ball_checkState(y-1,x) == 1){
		screen[y-1][x]=0;
		ball_increaseScore();}		
}
//-----------------------------------------------------------------------------------------
//------------------------------------ ball_deleteCell ------------------------------------
void SwitchStates(int state){
	switch(state){ 
		// in case of -1 -> the ball moved down and didn't touch the bunker, so a life is missed.
		case -1:
			lifes--;
		break;
		
		case 0: break;
		case 1: // During these cases (states 1:4 above), the ball will hit cells -> delete cell, increase score and change direction
		case 2:
		case 4:
		case 3:
			ball_ChangeDir(state);	
		  ball_deleteCell();
		break;
		
		default: break;
	}	
}
//-----------------------------------------------------------------------------------------
//------------------------------------ Setters --------------------------------------------
void setX 		(int xVal)              { x = xVal; }
void setY			(int yVal)              { y = yVal; }
void setD			(int dirVal)	          { d = dirVal; }
void setScore (int sVal)		          { score = sVal; }
void setLifes (int lVal)		 				  { lifes = lVal; }
void setLevel (int levelVal)          { level = levelVal; }
void setScreen(int i,int j,int state) { screen[i][j]=state; }
//-----------------------------------------------------------------------------------------
//------------------------------------ Getters --------------------------------------------
int GetX()                            { return x; }
int GetY()							              { return y; }
int GetD()								            { return d; }
int GetScore()				                { return score; }
int GetLifes()                        { return lifes; } 
int GetLevel()                        { return level; }
int GetScreen(int i,int j)            { return screen[i][j]; }
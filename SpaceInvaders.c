#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "ModelPlayer.h"

// Lab 15 Methods headers:
void DisableInterrupts(void);
void EnableInterrupts(void);
void Timer2_Init(unsigned long period);
void Delay100ms(unsigned long count);
unsigned long TimerCount;
unsigned long Semaphore;

// Method headers:
void welcomeScreen(void);
void GameOver();
void PortF_Init(void);
void disableTimer(void);
void enableTimer(void);
void Draw();
void Init();
int  checkLifes();
void displayLevel(int);
unsigned long life;
unsigned long shoot;
unsigned int BunkerX;
unsigned int BunkerY;
unsigned long left, right;
//-----------------------------------------------------------------------------------------
//------------------------------------ BMPs -----------------------------------------------
const unsigned char Bunker0[] = {
 0x42, 0x4D, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00,
 0x00, 0x00, 0xAA, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
 0xAA, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0xFF};

const unsigned char Cell[] = {
 0x42, 0x4D, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,};



// BMPs array: arr[18] = width, arr[22] = hight.
#define BUNKERW ((unsigned char) Bunker0[18])
#define BUNKERH ((unsigned char) Bunker0[22])
#define CellW   ((unsigned char) Cell[18])
#define CellH   ((unsigned char) Cell[22])

//-----------------------------------------------------------------------------------------
//------------------------------------ WELCOME --------------------------------------------
void welcomeScreen(){
	Nokia5110_Clear();
	Nokia5110_SetCursor(2, 1);
	Nokia5110_OutString(" WELCOME");
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutString(" DX BALL");
	Nokia5110_SetCursor(0, 0);
}
//-----------------------------------------------------------------------------------------
//------------------------------------ Init -----------------------------------------------
void Init(){ 
	int j;
	ball_init();
	// the bunker is a movable part which hits the ball, its initial coordinates are BunkerY, BunkerX.
	BunkerY = 10;
	BunkerX = 8;
	
	/*for(j = 0; j < GRIDW ; j++)
		setScreen(BunkerY, j, 0);*/
	
	// initially, we determine which cells belongs to the area of the bunker which will hit the ball:
	// the drawing of the bunker will be as a part of the draw method.
	// without this loop, the bunker will be drawn with draw method but will be not effective.
	// BunkerX + 5 --> defines the width of it.
	// set screen method takes the x, y coordinates and the desired stste (3rd parameter) of this cell, the states are:
	// cell state = 0 --> ordinary and empty cell.
	// cell state = 1 --> a cell may be shoted by the bunker.
	// cell state = 2 --> a cell in the bunker body. 
	for(j = BunkerX; j < BunkerX + 5; j++)
		setScreen(BunkerY, j, 2);
}
//-----------------------------------------------------------------------------------------
//------------------------------------ Draw -----------------------------------------------
/* Draw is used to "display" the cells with its state, if a cell was shoted will be removed because
 the nested for loop draws cells when its state is 1 only, so we can consider that this method updates 
 the cells after each shot, also it draws the ball and the bunker. */
void Draw(){
	int i, j;
  Nokia5110_ClearBuffer();
	Nokia5110_Clear();
	// x and y are multiplyed by 4 to determine the hight and the width of the element be drawn.
	// Nokia5110_PrintBMP      -> this method just send theelement will be printed to the "buffer".
	// Nokia5110_Clear         -> this method clears the screen before printing any thing.
	// Nokia5110_DisplayBuffer -> this method display the elements stored in the buffer on the screen immediately.
	for(i = 0; i < GRIDH; i++){
		for(j = 0; j < GRIDW; j++){
			if(GetScreen(i, j) == 1){
				Nokia5110_PrintBMP(4*j, i*4+(CellH - 1), Cell, 0);
			}
		}
	}	
	Nokia5110_PrintBMP(4*GetX(), GetY()*4+(CellH - 1), image, 0);
	Nokia5110_PrintBMP(4*BunkerX, BunkerY*4+(BUNKERH - 1), Bunker0, 0);		
	Nokia5110_Clear();
	Nokia5110_DisplayBuffer();
}
//-----------------------------------------------------------------------------------------
//------------------------------------ WinGame --------------------------------------------
void WinGame(){
	Nokia5110_Clear();
	Nokia5110_SetCursor(1, 1);
	Nokia5110_OutString("CONGRATS");
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutString("YOU WON !");
	Nokia5110_SetCursor(0, 0);
}
//-----------------------------------------------------------------------------------------
//------------------------------------ displayLevel ---------------------------------------
void displayLevel(int level){
	int i,j;
	Nokia5110_Clear();
	Nokia5110_SetCursor(1, 2);
	Nokia5110_OutString("  LEVEL  ");	
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutUDec(level);
	Nokia5110_SetCursor(0, 0);
	// setLevel -> used to update the current level of the game by updating the "level" variable in .h file.
	setLevel(level);
	// reinitialize the screen of the new level by calling "Init()" again.
	Init();
	// as the level be higher, blocks be more.
	// this be obtained by adding a const number of rows 3 to the current level number.
	// level 1 -> (3 + 1) rows of shotting cells.
	// level 2 -> (3 + 2) rows of shotting cells.
	// level 3 -> (3 + 3) rows of shotting cells.
	// more cells, the game be more difficult.
	for(i = 0; i < 3 + GetLevel() ; i++)
		for(j = 0; j < GRIDW ; j++){
			setScreen(i, j, 1);	
		}
		Delay100ms(30);
}
//-----------------------------------------------------------------------------------------
//------------------------------------ GameOver -------------------------------------------
void GameOver(){
	Nokia5110_Clear();
	Nokia5110_SetCursor(1, 1);
	Nokia5110_OutString("GAME OVER");
	Nokia5110_SetCursor(1, 3);
	Nokia5110_OutString("  Score");
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutUDec(GetScore());
	Nokia5110_SetCursor(0, 0);
}
//------------------------------------------START------------------------------------------
//-------------------------------------- MAIN METHOD --------------------------------------
//-----------------------------------------------------------------------------------------
int main(void){
	// using lab15 timer2 and portF initialization.
	TExaS_Init(NoLCD_NoScope); // set system clock to 80 MHz.
	Nokia5110_Init();					 // initialize lcd nokia 5110.
	PortF_Init();							 // portF initialization.
	Timer2_Init(800000000/30); // 30 Hz. "controls the speed of the game."
	//--------------------------------------------------------------------------------------
	ball_initlevel(); // ball_initleve -> at start, score is 0, total lifes is 3 and initial level is 1.
	Init();						// initialize the borders of the bunker and its position on screen.
	welcomeScreen();  // welcome screen display with some delay.
	Delay100ms(30);   // delay = 0.1 sec * 30 = 3 sec.
	displayLevel(1);  // start the game with level 1.
	Draw();						// display the elements on the screen (the above cells, the ball and the bunker).
	life = GetLifes();// get the current life of the game.
	/*
	- the while loop checks if your life is greater than 0 -> continue playing.
	- the 3 available lifes through all the three levels.
	- if your score reaches some value -> you will be jump to the next level.
	- if you are out of lifes at any time through any level you will lose the game.
	- timer be disables after winning the game.
	*/
	while(GetLifes() > 0){
		if(GetLevel() == 1 && GetScore() > 200) { displayLevel(2); }
		if(GetLevel() == 2 && GetScore() > 300) { displayLevel(3); }
		if(GetLevel() == 3 && GetScore() > 400) { WinGame(); disableTimer(); }
	}
	GameOver();
}
//------------------------------------------END--------------------------------------------
//-------------------------------------- MAIN METHOD --------------------------------------
//-----------------------------------------------------------------------------------------
//------------Lab 15--------------------Timer2 Initialization------------------------------
void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
	// interrupts enabled in the main program after all devices initialized
	// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}
//-----------------------------------------------------------------------------------------
//------------Lab 15--------------------disableTimer---------------------------------------
void disableTimer(){
	  TIMER2_CTL_R = 0x00000000;    //  disable timer2A
}
//-----------------------------------------------------------------------------------------
//------------Lab 15--------------------enableTimer----------------------------------------
void enableTimer(void){
		TIMER2_CTL_R = 0x00000001;    //  enable timer2A
}
//-----------------------------------------------------------------------------------------
//------------Lab 15--------------------Timer2A_Handler------------------------------------
void Timer2A_Handler(void){ 
	int i,j;
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
  TimerCount++;
  ball_move(); 
	
	if(GetLifes()>0){
		if(GetLifes() != life){
			Init();
			life = GetLifes();
			Delay100ms(20);
		}
		
		// read the SW1 & SW2 as the right and left switches.
		left  = GPIO_PORTF_DATA_R&0x10; // read PF4 into SW1
    right = GPIO_PORTF_DATA_R&0x01; // read PF0 into SW2
		
		// check the state of the switches (switches are active low -> 0 means pressed, other means not pressed).
		// if both are pressed -> "blue led" and the "bunker cannot move".
		if(!left && !right) GPIO_PORTF_DATA_R = 0x04;
		
		else{
			// if left is pressed -> "red led" and the "bunker move left".
			if(!left && right){
				GPIO_PORTF_DATA_R = 0x02;	
				// if the left is pressed and the bunker is at the most left of the screen, stay in your place.
				if(BunkerX >= 1){
					setScreen(BunkerY, BunkerX+4 ,0);
					setScreen(BunkerY ,BunkerX-1 ,2);
					BunkerX--;
				}
			}
			
			// if right is pressed -> "green led" and the "bunker move right".
			else if(!right && left){
				GPIO_PORTF_DATA_R = 0x08;
				// if the right is pressed and the bunker is at the most right of the screen, stay in your place.
				if(BunkerX <= 15) {
       		setScreen(BunkerY, BunkerX, 0);
					setScreen(BunkerY, BunkerX+5, 2);  
					BunkerX++;		
				}
			}
			// if no thing is pressed -> no move, no led , nothing will happen, just the ball is moving.
			else GPIO_PORTF_DATA_R = 0x00;      	
		}
		// at every press on any switches, we draw the screen again.
		Draw();  
	}	
  Semaphore = 1; // trigger
}
//-----------------------------------------------------------------------------------------
//------------Lab 15--------------------Delay100ms-----------------------------------------
void Delay100ms(unsigned long count){
	unsigned long volatile time;
	disableTimer();
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
	enableTimer();
}
//-----------------------------------------------------------------------------------------
//------------Lab ----------------------PortF_Init-----------------------------------------
void PortF_Init(void){ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}
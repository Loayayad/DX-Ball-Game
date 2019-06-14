static unsigned int x;      // x coordinate
static unsigned int y;      // y coordinate
static unsigned int d;      //direction
static unsigned int score;  // score
static unsigned int level;  //level
static unsigned int o;      //setter&getter
static const unsigned int GRIDW = 21; // screen grid width
static const unsigned int GRIDH = 12; // screen grid height 
static int lifes = 3;
	
// Screen grid which will store the state of the each cell on the screen, the states are: 
// cell state = 0 --> ordinary and empty cell.
// cell state = 1 --> a cell may be shoted by the bunker.
// cell state = 2 --> a cell in the bunker body. 
static unsigned int screen [GRIDH] [GRIDW];  

// the ball ball wich will move 
	static const unsigned char image[] ={
	 0x42, 0x4D, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
	 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF,};
	
	
//initiate the screen grid and ball position at the begining  
void ball_init ();

//initiate level ,score and lifes	
void ball_initlevel();
	 
// will move the ball in its direction
void ball_move ();
 
// change the direction of the ball if it hits something  
void ball_ChangeDir(unsigned int);
	 
// return the current direction of the ball 
unsigned int ball_getDir();
	 
// returns the score of the ball 
unsigned int Pll8ayer_getScore();
	 
// increment the score of the ball 
void ball_increaseScore();

int ball_checkState(int,int);

// delete all touched cells from all directions.
void ball_deleteCell();
void SwitchStates(int state);

void setX(int x);
void setY(int y);
void setD(int d);
void setScore(int S);
void setLifes(int L);
void setScreen(int,int,int);
void setLevel(int L);
int GetX();
int GetY();
int GetD();
int GetScore();
int GetLifes();
int GetScreen(int,int);
int GetLevel();

#include <allegro.h>
#include "snake.h"
#include "snake-data.h"
#include "snake-func.h"

DATAFILE *m_dataFile;
// Offscreen buffer, it's a 640x480 BITMAP created in initGameEngine()
BITMAP *m_offScreen;

// Player info...
PLAYER m_players[4];
int m_numPlayers = 1;
int m_currentPlayer = 0;

// Snake data for the current player
int m_snakeDead = 0;
int m_snakeExited = 0;
int m_snakeLength = 0;
int m_snakeLengthGrow = CONST_SNAKE_INIT_LENGTH;
int m_snakeAnimationFrame = 0;
int m_snakeNumbersEaten = 0;

// Numbers in the maze
int m_numberAnimationFrame = 0;
int m_numberX = 0;
int m_numberY = 0;
int m_numberValue = 9;
int m_numberAge = 0;
int m_foodAnimationFrame = 0;

// Directions are defined in the header file
int m_snakeDirection = CONST_SNAKE_DIRECTION_RIGHT;

// Head and tail locations, and frames representing them
SNAKE_POINT m_snakeNodes[CONST_SNAKE_MAX_LENGTH];
SNAKE_POINT m_snakeNextHead;
int m_snakeHeadAnimationFrame=0, m_snakeTailAnimationFrame=0;

// Level loading stuff
int m_levelsLoaded = 0;
LEVEL m_levelMap[CONST_MAX_LEVELS];

// Game engine handling, drawing and speed
int m_gameTempoCounter = 0;
int m_gameNeedInput = 0;

// Game tempo function...
void gameTempo(void) {
	m_gameTempoCounter++;
}
END_OF_FUNCTION(gameTempo)

// Load the resource data file, perform all the variable and setting initialization
void initGameEngine(void) {
	int p;
	
	// Wake up Allegro and all the optional modules we need	
	allegro_init();
	install_keyboard();

	// mouse init
	install_mouse();

	// timing magic
	install_timer();

	// spawn the graphic mode	
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
	clear(screen);
	m_offScreen = create_bitmap(640, 480);

	// smart people read docs first, idiots like me wonder why the hell doesnt this work
	// if i first load the data file, and then set the mode... argh
	m_dataFile = load_datafile("data/snake.dat");

	// Init the entropy generator(TM)
	srand(time(NULL));

	// Players init...
	for (p=0; p<m_numPlayers; p++) {
		m_players[p].score=0;
		m_players[p].level=2;
		m_players[p].lives=CONST_PLAYER_START_LIVES;
	}

	// Now, init the game tempo counter
	LOCK_VARIABLE(m_gameTempoCounter);
	LOCK_FUNCTION(gameTempo);
	install_int_ex(gameTempo, BPS_TO_TIMER(CONST_GAME_TEMPO_BPS));
}


// The game loops inside this function until the play is over - zero lives for everyone
void mainGameLoop() {
	int p, loop=1;

	while (loop) {
		loop=0;
		for (p=0; p<m_numPlayers; p++) {
			m_currentPlayer=p;
			if (m_players[m_currentPlayer].lives>0) {
				loop=1;
				if (m_players[m_currentPlayer].level%2) {
					gameOddLevel();
				} else {
					m_players[m_currentPlayer].levelMap = m_levelMap[m_players[m_currentPlayer].level%2];
					gameEvenLevel();
				}
			}
		}
	}
}

// Program entry point
int main (void) {
	int x, y;
	
	loadEvenLevels();
	
	// Wake up Allegro, load resources and perform game engine init
	initGameEngine();
	
	// Run the main game loop
	mainGameLoop();

	// Aw, phuck it all...
	allegro_exit();

	for(x=0; x<m_numPlayers; x++) {
		printf("Player %d\n\tLevel: %d\n\tScore: %d\n\n", x+1, m_players[x].level, m_players[x].score);
	}
	
	return 0;
}


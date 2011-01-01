#include <allegro.h>

extern DATAFILE *m_dataFile;
// Offscreen buffer, it's a 640x480 BITMAP created in initGameEngine()
extern BITMAP *m_offScreen;

// Player info...
extern PLAYER m_players[4];
extern int m_numPlayers;
extern int m_currentPlayer;

// Snake data for the current player
extern int m_snakeDead;
extern int m_snakeExited;
extern int m_snakeLength;
extern int m_snakeLengthGrow;
extern int m_snakeAnimationFrame;
extern int m_snakeNumbersEaten;

// Items in the maze
extern int m_numberAnimationFrame;
extern int m_numberX;
extern int m_numberY;
extern int m_numberValue;
extern int m_numberAge;
extern int m_foodAnimationFrame;

// Directions are defined in the header file
extern int m_snakeDirection;

// Head and tail locations, and frames representing them
extern SNAKE_POINT m_snakeNodes[CONST_SNAKE_MAX_LENGTH];
extern SNAKE_POINT m_snakeNextHead;
extern int m_snakeHeadAnimationFrame, m_snakeTailAnimationFrame;

// Game speed handling (tempo)
extern int m_gameTempoCounter;
extern int m_gameNeedInput;

// Level loading stuff
extern int m_levelsLoaded;
extern LEVEL m_levelMap[CONST_MAX_LEVELS];

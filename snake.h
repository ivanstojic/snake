// The maximum number of nodes in a snake's body...
#define CONST_SNAKE_MAX_LENGTH 300

// The maximum number of levels to load
#define CONST_MAX_LEVELS 25

// Constants defining the numerical value for every snake direction...
#define CONST_SNAKE_DIRECTION_UP 3
#define CONST_SNAKE_DIRECTION_RIGHT 0
#define CONST_SNAKE_DIRECTION_DOWN 2
#define CONST_SNAKE_DIRECTION_LEFT 1
#define CONST_SNAKE_DIRECTION_STOP 4

// Dimensions of one snake sprite, be it a head, tail or a body ring
#define CONST_SNAKE_SPRITE_HEIGHT 25
#define CONST_SNAKE_SPRITE_WIDTH 25

// Initial length of the snake
#define CONST_SNAKE_INIT_LENGTH 4

// Offset of the start of effective playing area from the top-left corner of the screen
#define CONST_FIELD_LEFT 11
#define CONST_FIELD_TOP 15

// The number of playing 'units' on the screen
#define CONST_FIELD_UNITS_HEIGHT 17
#define CONST_FIELD_UNITS_WIDTH 16

// Defines how many steps a snake can make before the number is decremented by one
#define CONST_NUMBER_AGE_LIMIT 2
// Defines the factor which limits the number rotation speed. The bigger the define, the
// slower will the number spin. 1 is useless, 3 is optimal, I think...
#define CONST_FOOD_ANIMATION_FACTOR 13

// Defines the number of the points needed to go to the next level
#define CONST_LEVEL_DONE_POINTS 40

// Starting number of lives a player has...
#define CONST_PLAYER_START_LIVES 2

// Game speed
#define CONST_GAME_TEMPO_BPS 100

// Level map constants
#define CONST_MAP_EMPTY 0
#define CONST_MAP_FOOD1 1
#define CONST_MAP_FOOD2 2
#define CONST_MAP_BLOCK_RED 3
#define CONST_MAP_BLOCK_WHITE 4
#define CONST_MAP_BLOCK_BLUE 5


// Structure of a single point in the snake's body
typedef struct {
	int x;
	int y;
} SNAKE_POINT;

typedef struct {
	SNAKE_POINT startNode;
	int startDirection;
	int nodes[17][16];
} LEVEL;

// Structure for one player... there's one like this for every player, sounds logical, uh?
typedef struct {
	int lives;
	int score;
	int level;
	LEVEL levelMap;
} PLAYER;


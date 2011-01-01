extern void initGameEngine(void);
extern void mainGameLoop();
extern void cycleAnimationItems(void);
extern void handleInput(void);
extern void drawState(void);

extern void moveSnake();
extern SNAKE_POINT getNextHeadPoint(void);
extern int detectTailDirection(SNAKE_POINT first, SNAKE_POINT second);
extern void detectSnakeMotion(SNAKE_POINT first, SNAKE_POINT second, int *vector_x, int *vector_y);

extern int snakeCollision();
void generateNextNumber();

void gameTempo(void);

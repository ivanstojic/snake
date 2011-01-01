#include "snake.h"
#include "snake-vars.h"

// Handle input from the user's keyboard - replace with a mouse input routine
void handleKeyboardInput(void) {
	int key;
	if (keypressed()) {
		key = readkey();
		if (key>>8 == KEY_UP) {
			exit(0);
		}
		
		if (key>>8 == KEY_LEFT) {
			switch (m_snakeDirection) {
				case CONST_SNAKE_DIRECTION_UP:
					m_snakeDirection = CONST_SNAKE_DIRECTION_LEFT;
					break;
				case CONST_SNAKE_DIRECTION_RIGHT:
					m_snakeDirection = CONST_SNAKE_DIRECTION_UP;
					break;
				case CONST_SNAKE_DIRECTION_DOWN:
					m_snakeDirection = CONST_SNAKE_DIRECTION_RIGHT;
					break;
				case CONST_SNAKE_DIRECTION_LEFT:
					m_snakeDirection = CONST_SNAKE_DIRECTION_DOWN;
					break;
			}
		}
		if (key>>8 == KEY_RIGHT) {
			switch (m_snakeDirection) {
				case CONST_SNAKE_DIRECTION_UP:
					m_snakeDirection = CONST_SNAKE_DIRECTION_RIGHT;
					break;
				case CONST_SNAKE_DIRECTION_RIGHT:
					m_snakeDirection = CONST_SNAKE_DIRECTION_DOWN;
					break;
				case CONST_SNAKE_DIRECTION_DOWN:
					m_snakeDirection = CONST_SNAKE_DIRECTION_LEFT;
					break;
				case CONST_SNAKE_DIRECTION_LEFT:
					m_snakeDirection = CONST_SNAKE_DIRECTION_UP;
					break;
			}
		}
	}
}

// Handle the input from the user
void handleInput(void) {
	handleKeyboardInput();
}

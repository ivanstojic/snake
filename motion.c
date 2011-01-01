#include "snake.h"
#include "snake-vars.h"
#include "snake-func.h"

// Move the snake in the direction of motion, growing the snake as needed
// Collision detection/handling is performed elsewhere, this function will
// just update the snakeNodes structure
void moveSnake() {
	SNAKE_POINT new;
	int crawl;
	
	new = getNextHeadPoint();

	if (m_snakeLengthGrow) {
		// We need to grow the snake
		// Starting from the last, move all elements of the body, one place towards the back of
		// the array (thus creating one more element in the body - snake grows). Then, add the
		// newly created element to the head.
		m_snakeLengthGrow--;
		for (crawl=m_snakeLength; crawl>-1; crawl--) {
			m_snakeNodes[crawl+1] = m_snakeNodes[crawl];
		}
		m_snakeNodes[0] = new;
		m_snakeLength++;
		
	} else {
		// The snake simply moves one field forward with no growing - crawl from the last
		// index of the snake-1 (just before tail) to the head, and move them back, then
		// add the newly acquired field to the head of the snake. Since we start on the snake-1
		// element, we'll overwrite the last field - snake won't grow
		for (crawl=m_snakeLength-1; crawl>-1; crawl--) {
			m_snakeNodes[crawl+1] = m_snakeNodes[crawl];
		}
		m_snakeNodes[0] = new;
	}
}


// Fetches the next location of the head - used to determine the direction the snake will 'crawl'
// between playing field locations
SNAKE_POINT getNextHeadPoint(void) {
	SNAKE_POINT new;

	new = *m_snakeNodes;
	
	switch (m_snakeDirection) {
		case CONST_SNAKE_DIRECTION_LEFT:
			new.x--;
			break;
			
		case CONST_SNAKE_DIRECTION_RIGHT:
			new.x++;
			break;
			
		case CONST_SNAKE_DIRECTION_UP:
			new.y--;
			break;
			
		case CONST_SNAKE_DIRECTION_DOWN:
			new.y++;
			break;
	}
	
	return new;
}



// Detect the direction of the snake's tail, given two of it's adjacent nodes. I use this to pick the
// correct tail image to draw. The 'first' node should be the one nearer to the head, and the 'second'
// node is the one nearer to the tail. Do NOT mix this up ;)
int detectTailDirection(SNAKE_POINT first, SNAKE_POINT second) {
	if (first.x==second.x) {
		if (first.y>second.y) {
			return CONST_SNAKE_DIRECTION_DOWN;
		} else {
			return CONST_SNAKE_DIRECTION_UP;
		}
	} else {
		if (first.x>second.x) {
			return CONST_SNAKE_DIRECTION_LEFT;
		} else {
			return CONST_SNAKE_DIRECTION_RIGHT;
		}
	}
}


// Detect the snake motion vector between two adjacent snake nodes. I use this to find out the vector
// by which to offset snake elements in animations. The first node should be the one nearer to the head,
// and the second one is the one nearer to the tail. Do NOT mix this up! ;)
void detectSnakeMotion(SNAKE_POINT first, SNAKE_POINT second, int *vector_x, int *vector_y) {
	if (first.x==second.x) {
		*vector_x = 0;
		if (first.y>second.y) {
			*vector_y = 1;
		} else {
			*vector_y = -1;
		}
	} else {
		*vector_y = 0;
		if (first.x>second.x) {
			*vector_x = 1;
		} else {
			*vector_x = -1;
		}
	}
}


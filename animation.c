#include "snake.h"
#include "snake-vars.h"

// Turn one step of the snake's head and tail animation
void cycleAnimationItems(void) {
	// FIX ME! Why the hell did I even think of using static vars? %-)
	static int tailDirection=1, headElapsed=0;
	static int foodDirection=1;
	
	if (m_snakeTailAnimationFrame+tailDirection<0 || m_snakeTailAnimationFrame+tailDirection>2) {
		tailDirection *= -1;
	} else {
		m_snakeTailAnimationFrame += tailDirection;
	}
	
	headElapsed++;
	if (headElapsed>10 && headElapsed<12) {
		m_snakeHeadAnimationFrame=1;
	} else {
		headElapsed = (headElapsed+1)%13;
		m_snakeHeadAnimationFrame=0;
	}

	m_numberAnimationFrame=(m_numberAnimationFrame+1)%(6*CONST_FOOD_ANIMATION_FACTOR);

	m_foodAnimationFrame+=foodDirection;
	if (m_foodAnimationFrame>3*CONST_FOOD_ANIMATION_FACTOR || m_foodAnimationFrame<0) {
		foodDirection*=-1;
		m_foodAnimationFrame+=foodDirection;
	}
}

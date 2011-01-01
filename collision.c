#include "snake.h"
#include "snake-vars.h"
#include "snake-func.h"

int checkCollision() {
	int crawl;
	
	if (1) {
		for (crawl=0; crawl<m_snakeLength; crawl++) {
			if (m_snakeNodes[crawl].x==m_snakeNextHead.x && m_snakeNodes[crawl].y==m_snakeNextHead.y) {
				// Snake would collide with itself in the m_snakeNextHead square...
				return 1;
			}
		}

		if (m_snakeNextHead.x==-1 || m_snakeNextHead.x==17 || m_snakeNextHead.y==-1 || m_snakeNextHead.y==18) {
			// Snake hit the end of screen...
			return 1;
		}	
	} else {
		// Even numbered levels are yet to be implemented, yes?
	}

	return 0;
}

void checkNumberHit() {
	if (m_snakeNextHead.x==m_numberX && m_snakeNextHead.y==m_numberY) {
		m_snakeLengthGrow+=m_numberValue;
		m_snakeNumbersEaten+=m_numberValue;
		
		// Score calculation... FIX ME
		m_players[m_currentPlayer].score+=m_numberValue*m_players[m_currentPlayer].level+m_snakeLength;
		
		generateNextNumber();
	}
}


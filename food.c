#include "snake.h"
#include "snake-vars.h"
#include "snake-func.h"


void generateNextNumber() {
	int found = 0, crawl;
	m_numberValue=9;
	m_numberAge=0;

	do {
		m_numberX = rand() % CONST_FIELD_UNITS_WIDTH;
		m_numberY = rand() % CONST_FIELD_UNITS_HEIGHT;
		
		found = 0;
		for (crawl=0; crawl<m_snakeLength; crawl++) {
			if (m_numberX==m_snakeNodes[crawl].x && m_numberY==m_snakeNodes[crawl].y) {
				found++;
			}
		}

		if (m_numberX==m_snakeNextHead.x && m_numberY==m_snakeNextHead.y) {
			found++;
		}
	} while (found);
	// FIX ME!
	// This should check if the newly generated number is 'in' the snake...
}

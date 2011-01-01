#include "snake.h"
#include "snake-vars.h"
#include "snake-func.h"

// Handles the play for even-numbered levels. It expects that someone else handles the
// player announcements, current player increments and stuff like that...
void gameEvenLevel() {
	// Snake init stuff
	m_snakeNodes[0].x = 0; m_snakeNodes[0].y = 0;
	m_snakeLength = 0; m_snakeLengthGrow = 4;
	m_snakeDead = 0; m_snakeNumbersEaten = 0;
	m_snakeDirection = CONST_SNAKE_DIRECTION_RIGHT;
	
	generateNextNumber();

	// Set the game tempo counter to zero, we don't want to pay the price for accumulated
	// game frames...
	m_gameTempoCounter = 0;
	m_gameNeedInput=1;
	while (keypressed()) {
		readkey();
	}
	while (!m_snakeDead) {
		// Stay inside this loop for as long the snake ain't dead, and the player hasn't exited the
		// level yet...

		while (m_gameTempoCounter>0) {
			// This loop is repeated for as long as we need to keep updating our game logic
			// When we exit it, we'll be up to date with the game tempo, and we can draw the current
			// frame on to the screen

			if (m_gameNeedInput) {
				// If m_gameNeedInput is set, then all of the interim frames have been drawn and
				// we need to process the user's input for the next move
				m_snakeAnimationFrame=0;
				
				moveSnake();
				handleInput();
				m_snakeNextHead = getNextHeadPoint();
				checkNumberHit();

				// FIX ME - we need better naming. checkNumberHit is food collision, checkCollision is
				// snake/edge collision
				if (checkCollision()) {
					// FIX ME - the death sequence should come here...
					m_snakeDead++;
				}
				m_gameNeedInput=0;
			}
			
			// Check if there are any interim frames to be drawn, draw them if there are any
			// else, set the m_gameNeedInput flag.
			if (m_snakeAnimationFrame<CONST_SNAKE_SPRITE_WIDTH) {
				cycleAnimationItems();
				m_snakeAnimationFrame++;
			} else {
				m_gameNeedInput=1;
				if (m_numberAge++==CONST_NUMBER_AGE_LIMIT) {
					m_numberAge = 0;
					m_numberValue--;
					if (!m_numberValue) {
						generateNextNumber();
						m_snakeLengthGrow+=1;
					}
				}
			}
			m_gameTempoCounter--;
		}

		// Now, we are ready to draw this shitty item...
		drawState();
	}

	// The play is finished, find out why...

	if (m_snakeDead) {
		drawDeadSnake();
		m_players[m_currentPlayer].lives--;
	}
	if (m_snakeExited) {
		// drawExitSnake();
		m_players[m_currentPlayer].score+=1000;
	}
	if (m_snakeNumbersEaten>=CONST_LEVEL_DONE_POINTS) {
		m_players[m_currentPlayer].level++;
	}
}




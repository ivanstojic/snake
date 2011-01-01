#include <math.h>
#include "snake.h"
#include "snake-vars.h"
#include "snake-func.h"
#include "snake-data.h"

// Draw the "score"
void drawNumbersEaten(void) {
	blit(m_dataFile[BAR_PCX].dat, m_offScreen,
		0,0,
		470, 170,

		30, 190-190./CONST_LEVEL_DONE_POINTS*m_snakeNumbersEaten
	);
	
	blit(m_dataFile[BAR_PCX].dat, m_offScreen,
		30, 190-190./CONST_LEVEL_DONE_POINTS*m_snakeNumbersEaten,
		470, 360-190./CONST_LEVEL_DONE_POINTS*m_snakeNumbersEaten,

		30, 190./CONST_LEVEL_DONE_POINTS*m_snakeNumbersEaten
	);
}

// Draws the snake
void drawSnake(void) {
	int crawl;
	int x,y;
	int offset;

	// blit the head first
	// first, calculate the vectors for the animation offseting, then, use them in the formula to blit correctly
	if (!m_snakeDead) {
		detectSnakeMotion(m_snakeNextHead, m_snakeNodes[0], &x, &y);
		blit(m_dataFile[HEAD_PCX].dat, m_offScreen,
			m_snakeHeadAnimationFrame*CONST_SNAKE_SPRITE_WIDTH, m_snakeDirection*CONST_SNAKE_SPRITE_HEIGHT,
			
			m_snakeNodes[0].x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT+(x*m_snakeAnimationFrame),
			m_snakeNodes[0].y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP+(y*m_snakeAnimationFrame),
	
			CONST_SNAKE_SPRITE_WIDTH, CONST_SNAKE_SPRITE_HEIGHT
		);
	}
	
	// blit body rings... FIX ME! this function should find the XY offset of each ring from
	// the middle element by using the sin() and cos() functions, it would look more natural
	// that way... who's ever seen a straight snake? >:)
	for (crawl=1; crawl<m_snakeLength-1; crawl++) {
		detectSnakeMotion(m_snakeNodes[crawl-1], m_snakeNodes[crawl], &x, &y);
		if (crawl%2) {
			offset=5-(m_snakeAnimationFrame/5)*2;
		} else {
			offset=-5+(m_snakeAnimationFrame/5)*2;
		}
		offset=0;
	
		if (x) {		
			blit(m_dataFile[BODY_PCX].dat, m_offScreen,
				0, 0,
				m_snakeNodes[crawl].x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT+5+(x*m_snakeAnimationFrame),
				m_snakeNodes[crawl].y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP+5+(y*m_snakeAnimationFrame)+offset,
				15, 15
			);
		} else {
			blit(m_dataFile[BODY_PCX].dat, m_offScreen,
				0, 0,
				m_snakeNodes[crawl].x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT+5+(x*m_snakeAnimationFrame)+offset,
				m_snakeNodes[crawl].y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP+5+(y*m_snakeAnimationFrame),
				15, 15
			);
		}
	}

	if (m_snakeLength-1>0) {
		// blit the tail
		detectSnakeMotion(m_snakeNodes[m_snakeLength-2], m_snakeNodes[m_snakeLength-1], &x, &y);
		blit(m_dataFile[TAIL_PCX].dat, m_offScreen,
			m_snakeTailAnimationFrame*CONST_SNAKE_SPRITE_WIDTH,
			detectTailDirection(m_snakeNodes[m_snakeLength-2], m_snakeNodes[m_snakeLength-1])*CONST_SNAKE_SPRITE_HEIGHT,
	
			m_snakeNodes[m_snakeLength-1].x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT+((m_snakeLengthGrow?0:x)*m_snakeAnimationFrame),
			m_snakeNodes[m_snakeLength-1].y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP+((m_snakeLengthGrow?0:y)*m_snakeAnimationFrame),

			CONST_SNAKE_SPRITE_WIDTH, CONST_SNAKE_SPRITE_HEIGHT		
		);
	}
}

void drawNumber() {
	blit(m_dataFile[NUMBERS_PCX].dat, m_offScreen,
		(m_numberAnimationFrame/CONST_FOOD_ANIMATION_FACTOR)*17,
		(m_numberValue-1)*18,
	
		m_numberX*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT,
		m_numberY*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP,

		17, 18
	);
}

void drawPlayerInfo() {
	char buf[20];
	int l;

	sprintf(buf, "Player:    %02d", m_currentPlayer+1);
	textout(m_offScreen, font, buf, 470, 50, -1);

	sprintf(buf, "Level:     %02d", m_players[m_currentPlayer].level);
	textout(m_offScreen, font, buf, 470, 60, -1);
	
	sprintf(buf, "Score:  %05d", m_players[m_currentPlayer].score);
	textout(m_offScreen, font, buf, 470, 70, -1);

	sprintf(buf, "Numbers: %d", m_snakeNumbersEaten);
	textout(m_offScreen, font, buf, 470, 80, -1);

	for (l=0; l<4 && l<m_players[m_currentPlayer].lives-1; l++) {
		blit(m_dataFile[LIFE_PCX].dat, m_offScreen,
			0, 0,
			577, 360-(l*50),
			63, 50
		);
	}
}

void drawDeadSnake(void) {
	int frame=0, direction=1, iteration=0;

	m_gameTempoCounter=0;
	while (iteration<3) {
		while (m_gameTempoCounter>0) {
			frame+=direction;
			if (frame<0 || frame>50) {
				direction*=-1;
				frame+=direction;
				iteration++;
			}
			m_gameTempoCounter--;
		}
		drawState();
		masked_blit(m_dataFile[BIGHEAD_PCX].dat, m_offScreen,
			(frame/10)*50, 0,
			
			m_snakeNodes[0].x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT-12,
			m_snakeNodes[0].y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP-12,

			50, 50
		);

		// move to the screen...
		blit(m_offScreen, screen, 0, 0, 0, 0, 640, 480);
	}
}

void drawMap(void) {
	int x, y;

	for (x=0; x<17; x++) {
		for (y=0; y<16; y++) {
			switch (m_levelMap[m_players[m_currentPlayer].level/2-1].nodes[y][x]) {
				// Foods
				case (CONST_MAP_FOOD1):
					blit(m_dataFile[EATBLOCKS_PCX].dat, m_offScreen,
						17*(m_foodAnimationFrame/CONST_FOOD_ANIMATION_FACTOR), 0,

						x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT,
						y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP,

						17,17
					);
					break;

				case (CONST_MAP_FOOD2):
					blit(m_dataFile[EATBLOCKS_PCX].dat, m_offScreen,
						17*(m_foodAnimationFrame/CONST_FOOD_ANIMATION_FACTOR), 17,

						x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT,
						y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP,

						17,17
					);
					break;

				// Walls
				case (CONST_MAP_BLOCK_RED):
					blit(m_dataFile[BLOCKS_PCX].dat, m_offScreen,
						50, 0,

						x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT,
						y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP,

						25,25
					);
					break;
				case (CONST_MAP_BLOCK_WHITE):
					blit(m_dataFile[BLOCKS_PCX].dat, m_offScreen,
						25, 0,

						x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT,
						y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP,

						25,25
					);
					break;
				case (CONST_MAP_BLOCK_BLUE):
					blit(m_dataFile[BLOCKS_PCX].dat, m_offScreen,
						0, 0,

						x*CONST_SNAKE_SPRITE_WIDTH+CONST_FIELD_LEFT,
						y*CONST_SNAKE_SPRITE_HEIGHT+CONST_FIELD_TOP,

						25,25
					);
					break;

					
			}
		}
	}
}

// Draws the current state of the game by calling child draw metho^Wfunctions. No OOP >:)
void drawState(void) {
	if (m_players[m_currentPlayer].level%2) {
		// Odd levels drawing...
		blit(m_dataFile[BACKGROUND_ODD_PCX].dat, m_offScreen, 0, 0, 0, 0, 640, 480);
		drawNumber();
		drawNumbersEaten();
	} else {
		// Even levels drawing...
		blit(m_dataFile[BACKGROUND_EVEN_PCX].dat, m_offScreen, 0, 0, 0, 0, 640, 480);
		drawMap();
	}
	
	drawPlayerInfo();
	drawSnake();

	if (!m_snakeDead) {
		blit(m_offScreen, screen, 0, 0, 0, 0, 640, 480);
	}
}



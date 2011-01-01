#include <stdio.h>
#include "snake.h"
#include "snake-vars.h"
#include "snake-func.h"

void loadEvenLevels() {
	FILE *levels;
	int row, col;
	char ch;

	levels = fopen("data/levels.txt", "r");

	if (!levels)
		return;

	while (!feof(levels)) {
		for (row=0; row<16 ; row++) {
			col=0;
			while ((ch=fgetc(levels))!='\n' && col++<17 && !feof(levels)) {
				printf("%c", ch);
				switch (ch) {
					// Block colors, ABC - for Blue(A), White(B), Red(C)
					case 'A':
						m_levelMap[m_levelsLoaded].nodes[row][col] = CONST_MAP_BLOCK_RED;
						break;
					case 'B':
						m_levelMap[m_levelsLoaded].nodes[row][col] = CONST_MAP_BLOCK_WHITE;
						break;
					case 'C':
						m_levelMap[m_levelsLoaded].nodes[row][col] = CONST_MAP_BLOCK_BLUE;
						break;

					// Head positions/directions, UDLR - for Up, Down, Left, Right
					case 'U':
						m_levelMap[m_levelsLoaded].startNode.x=col;
						m_levelMap[m_levelsLoaded].startNode.y=row;
						m_levelMap[m_levelsLoaded].startDirection=CONST_SNAKE_DIRECTION_UP;
						break;
						
					case 'D':
						m_levelMap[m_levelsLoaded].startNode.x=col;
						m_levelMap[m_levelsLoaded].startNode.y=row;
						m_levelMap[m_levelsLoaded].startDirection=CONST_SNAKE_DIRECTION_DOWN;
						break;
						
					case 'L':
						m_levelMap[m_levelsLoaded].startNode.x=col;
						m_levelMap[m_levelsLoaded].startNode.y=row;
						m_levelMap[m_levelsLoaded].startDirection=CONST_SNAKE_DIRECTION_LEFT;
						break;
						
					case 'R':
						m_levelMap[m_levelsLoaded].startNode.x=col;
						m_levelMap[m_levelsLoaded].startNode.y=row;
						m_levelMap[m_levelsLoaded].startDirection=CONST_SNAKE_DIRECTION_RIGHT;
						break;

					// Food types, 12 - Green(1), Red(2)
					case '1':
						m_levelMap[m_levelsLoaded].nodes[row][col] = CONST_MAP_FOOD1;
						break;
						
					case '2':
						m_levelMap[m_levelsLoaded].nodes[row][col] = CONST_MAP_FOOD2;
						break;

					// Empty cell, otherwise:
					default:
						m_levelMap[m_levelsLoaded].nodes[row][col] = CONST_MAP_EMPTY;
						break;
				}
			}
			printf("\n");
		}
		m_levelsLoaded++;
	}

	fclose(levels);

	printf("Loaded: %d\n", m_levelsLoaded);
}

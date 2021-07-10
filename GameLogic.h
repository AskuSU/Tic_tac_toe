#pragma once
#include"GameField.h"

typedef struct gameLogic
{
	size_t scorePlayer;
	size_t scoreAI;

	size_t elementsToWin;

	CellField::Cell playerValue;
	CellField::Cell AI_Value;
	
	gameLogic();

	void playerTurn(CellField* cellFd);
	void AI_Turn();
} GameLogic;
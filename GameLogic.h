#pragma once
#include"GameField.h"
#include<random>
#include<list>

typedef struct gameLogic
{
	size_t scorePlayer;
	size_t scoreAI;

	size_t elementsToWin;

	CellField::Cell playerValue;
	CellField::Cell AI_Value;
	
	gameLogic();

	std::random_device rd;	

	void playerTurn(CellField* cellFd);
	void AI_Turn();
} GameLogic;
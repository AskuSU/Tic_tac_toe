#include "GameLogic.h"

gameLogic::gameLogic()
{
	std::mt19937 mersenne(rd());	

	scorePlayer = scoreAI = 0;
	elementsToWin = 3;

	playerValue = CellField::Cell::cross;
	AI_Value = CellField::Cell::zero;
}

void gameLogic::playerTurn(CellField* cellFd)
{
	if (cellFd->CheckEmptyInTheCell())
	{
		cellFd->SetValueOnCell(playerValue);
	}
}

void gameLogic::AI_Turn()
{
	size_t x, y;
	std::uniform_real_distribution<double> dist(0, 8);
}




#include "GameLogic.h"

gameLogic::gameLogic()
{
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

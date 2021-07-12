#include "GameLogic.h"

GameLogic::GameLogic()
{
	

	scorePlayer = scoreAI = 0;
	elementsToWin = 3;

	nextMove = players::Player;

	playerValue = CellField::Cell::cross;
	AI_Value = CellField::Cell::zero;
}

players GameLogic::NextMove()
{
	return nextMove;
}

BOOL GameLogic::PlayerTurn(CellField* cellFd)
{
	if (cellFd->CheckEmptyInTheCell())
	{
		cellFd->SetValueOnCell(playerValue);
		nextMove = players::AI;
		return TRUE;
	}
	return FALSE;
}

BOOL GameLogic::AI_Turn(GameField* gameFl)
{
	size_t x, y;
	std::mt19937 mersenne(rd());
	std::uniform_real_distribution<double> dist(0, 9);
	auto cel = gameFl->cells[0].begin();
	if (gameFl->CheckEmptyCellOnTheField())
	{
		do
		{
			size_t a = dist(mersenne);
			cel = gameFl->cells[a/gameFl->sizeMatrix].begin();
			cel += a % gameFl->sizeMatrix;
		} while (!(*cel)->CheckEmptyInTheCell());
		gameFl->selection = cel;
		(*cel)->SetValueOnCell(AI_Value);
		nextMove = players::Player;
		return TRUE;
	}
	return FALSE;
}

winner GameLogic::HasAnyoneWon(GameField* gameFl)
{
	
	return winner();
}




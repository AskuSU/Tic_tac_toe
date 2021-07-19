#include "GameLogic.h"

GameLogic::GameLogic()
{
	

	scorePlayer = scoreAI = 0;
	elementsToWin = CONST_ELEMENTTOWIN;

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
	//size_t x, y;
	std::mt19937 mersenne(rd());
	std::uniform_real_distribution<double> dist(0, gameFl->sizeMatrix * gameFl->sizeMatrix);
	auto cel = gameFl->cells[0].begin();
	if (gameFl->CheckEmptyCellOnTheField())
	{
		do
		{
			size_t a = static_cast<size_t>(dist(mersenne));
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

void GameLogic::IsThereAwinner(GameField* gameFl)
{
	int x = static_cast<int>(gameFl->Selection()->Pos.x);
	int y = static_cast<int>(gameFl->Selection()->Pos.y);
	int elemToWin = static_cast<int>(elementsToWin);
	int size = static_cast<int>(gameFl->sizeMatrix);

	int fromY = 0, toY = 0, fromX = 0, toX = 0, qty = 0;
	//vertical
	//fromY = ((y - elemToWin + 1) >= 0) ? (y - elemToWin + 1) : 0;
	//toY = ((y + elemToWin - 1) < size) ? (y + elemToWin - 1) : size - 1;
	fromY = y - elemToWin + 1;
	toY = y + elemToWin - 1;

	for (size_t i = (fromY >= 0 ? (y - elemToWin + 1) : 0); i <= (toY < size ? (y + elemToWin - 1) : size - 1); i++)
	{
		if (gameFl->cells[i][x]->cell == gameFl->cells[y][x]->cell)
		{
			qty++;
		}
		else
		{
			qty = 0;
		}
		if (qty >= elemToWin)
		{
			WhoWin(true, nextMove);
			return;
		}
	}
	//horizontal
	qty = 0;
	//fromX = ((x - elemToWin + 1) >= 0) ? (x - elemToWin + 1) : 0;
	//toX = ((x + elemToWin - 1) < size) ? (x + elemToWin - 1) : size - 1;
	fromX = x - elemToWin + 1;
	toX = x + elemToWin - 1;

	for (size_t i = (fromX >= 0 ? (x - elemToWin + 1) : 0); i <= (toX < size ? (x + elemToWin - 1) : size - 1); i++)
	{
		if (gameFl->cells[y][i]->cell == gameFl->cells[y][x]->cell)
		{
			qty++;
		}
		else
		{
			qty = 0;
		}
		if (qty >= elemToWin)
		{
			WhoWin(true, nextMove);
			return;
		}
	}
	//diagonal Top Left
	qty = 0;	
	for (size_t i = 0; i < 2 * elemToWin; i++)
	{
		if ((fromY + i >= 0) && (fromX + i >= 0) && (fromY + i < size) && (fromX + i < size))
		{
			if (gameFl->cells[fromY + i][fromX + i]->cell == gameFl->cells[y][x]->cell)
			{
				qty++;
			}
			else
			{
				qty = 0;
			}
			if (qty >= elemToWin)
			{
				WhoWin(true, nextMove);
				return;
			}
		}
	}
	// diagonal Bottom Left
	qty = 0;
	for (size_t i = 0; i < 2 * elemToWin; i++)
	{
		if ((toY - i < size) && (fromX + i >= 0) && (toY - i >= 0) && (fromX + i < size))
		{
			if (gameFl->cells[toY - i][fromX + i]->cell == gameFl->cells[y][x]->cell)
			{
				qty++;
			}
			else
			{
				qty = 0;
			}
			if (qty >= elemToWin)
			{
				WhoWin(true, nextMove);
				return;
			}
		}
	}
	return;
}

void GameLogic::WhoWin(BOOL won, players who)
{
	this->whoWin.won = won;
	this->whoWin.who = who;
}

BOOL GameLogic::DidNotWin()
{
	return !whoWin.won;
}




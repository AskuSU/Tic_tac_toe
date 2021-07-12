#pragma once
#include "GameField.h"
#include <random>
#include <list>

enum class players
{
	Player,
	AI
};

struct winner
{
	BOOL won;
	players who;
};


class GameLogic
{
	size_t scorePlayer;
	size_t scoreAI;

	size_t elementsToWin;

	struct movePosition
	{
		size_t x, y;
	} movePos;
	
	players nextMove;

	CellField::Cell playerValue;
	CellField::Cell AI_Value;
	
	std::random_device rd;	
public:
	GameLogic();

	players NextMove();
	BOOL PlayerTurn(CellField* cellFd);
	BOOL AI_Turn(GameField* gameFl);
	winner HasAnyoneWon(GameField* gameFl);
};
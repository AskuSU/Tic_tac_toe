#pragma once
#include "GameField.h"
#include <random>
#include <list>
//#include <cmath>

enum class players
{
	Player,
	AI
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

	struct winner
	{
		BOOL won;
		players who;
	} whoWin;
	
	players nextMove;

	CellField::Cell playerValue;
	CellField::Cell AI_Value;
	
	std::random_device rd;	
public:
	GameLogic();

	players NextMove();
	BOOL PlayerTurn(CellField* cellFd);
	BOOL AI_Turn(GameField* gameFl);
	void IsThereAwinner(GameField* gameFl);
	void WhoWin(BOOL won, players who);
	BOOL DidNotWin();
};
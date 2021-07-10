#pragma once

#include <d2d1.h>

typedef struct gameField
{
	size_t	sizeMatrix;							//Размер матрицы поля
	size_t	sizeCellpx;							//Длинна ячейки
	static const size_t	thicknessBorderpx = 1;	//Толщина рамки
	static const size_t	spaceBetweenCellpx = 4;	//Промежуток м/у ячейками 
	static const size_t	thicknessContent = 4;   //Толщина фигур O X
		
	D2D1_COLOR_F backgroundColour; //Цвет фона окна

	gameField();
	size_t GetSizepx();
} GameField;


typedef struct cellField
{
	enum class Cell
	{
		empty,
		zero,
		cross
	};

	GameField* gameField;
	
	D2D1_RECT_F rect;
	D2D1_ELLIPSE ellipse;
	D2D1_COLOR_F color;
	Cell cell;

	D2D1_COLOR_F cellColour;
	D2D1_COLOR_F zeroColour;
	D2D1_COLOR_F crossColour;

	float lengthContent;			//Длинна габарита для O X
	float radiusZero;				//Радиус O
	float halfLengthDiagonalCross;	//Длинна половины диагонали X

	cellField(GameField* gField);

	BOOL HitTest(POINT pt);

	void DrawCell(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	void DrawValue(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	BOOL CheckEmptyInTheCell();
	void SetValueOnCell(Cell value);

} CellField;
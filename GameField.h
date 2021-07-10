#pragma once

#include <d2d1.h>

struct gameField
{
	static const size_t sizeMatrix = 3;			//Размер матрицы поля
	static const size_t	sizeCellpx = 200;		//Длинна ячейки
	static const size_t thicknessBorderpx = 1;	//Толщина рамки
	static const size_t spaceBetweenCellpx = 4;	//Промежуток м/у ячейками 
	static const size_t thicknessContent = 4;   //Толщина фигур O X

	static const D2D1_COLOR_F backgroundColour;

	size_t GetSizepx();
};


struct CellField
{
	enum class Cell
	{
		empty,
		zero,
		cross
	};
	
	D2D1_RECT_F rect;
	D2D1_ELLIPSE ellipse;
	D2D1_COLOR_F color;
	Cell cell;

	static const D2D1_COLOR_F cellColour;
	static const D2D1_COLOR_F zeroColour;
	static const D2D1_COLOR_F crossColour;

	static float lengthContent;				//Длинна габарита для O X
	static float radiusZero;				//Радиус O
	static float halfLengthDiagonalCross;	//Длинна половины диагонали X

	void DrawCell(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	void DrawValue(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
};
#pragma once

#include <d2d1.h>

struct gameField
{
	static const size_t sizeMatrix = 3;			//Размер матрицы поля
	static const size_t	sizeCellpx = 200;		//Длинна ячейки
	static const size_t thicknessBorderpx = 1;	//Толщина рамки
	static const size_t spaceBetweenCellpx = 4;	//Промежуток м/у ячейками 

	size_t GetSizepx();
};


struct CellField
{
	D2D1_RECT_F rect;
	D2D1_COLOR_F color;

	void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);	
};
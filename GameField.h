#pragma once

#include <d2d1.h>

struct gameField
{
	size_t sizeMatrix = 3, 
		sizeCellpx = 100,
		thicknessBorderpx = 3,
		spaceBetweenCellpx = 6;

	size_t GetSizepx();
};


struct CellField
{
	D2D1_RECT_F rect;
	D2D1_COLOR_F color;

	void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);	
};
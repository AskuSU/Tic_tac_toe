#pragma once

#include <d2d1.h>

struct gameField
{
	static const size_t sizeMatrix = 3;			//������ ������� ����
	static const size_t	sizeCellpx = 200;		//������ ������
	static const size_t thicknessBorderpx = 1;	//������� �����
	static const size_t spaceBetweenCellpx = 4;	//���������� �/� �������� 

	size_t GetSizepx();
};


struct CellField
{
	D2D1_RECT_F rect;
	D2D1_COLOR_F color;

	void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);	
};
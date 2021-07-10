#pragma once

#include <d2d1.h>

struct gameField
{
	static const size_t sizeMatrix = 3;			//������ ������� ����
	static const size_t	sizeCellpx = 200;		//������ ������
	static const size_t thicknessBorderpx = 1;	//������� �����
	static const size_t spaceBetweenCellpx = 4;	//���������� �/� �������� 
	static const size_t thicknessContent = 4;   //������� ����� O X

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

	static float lengthContent;				//������ �������� ��� O X
	static float radiusZero;				//������ O
	static float halfLengthDiagonalCross;	//������ �������� ��������� X

	BOOL HitTest(POINT pt);

	void DrawCell(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	void DrawValue(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	void SetValueOnCell();
};
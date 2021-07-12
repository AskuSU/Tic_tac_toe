#pragma once

#include <d2d1.h>
//#include <list>
#include <vector>
#include <memory>

using namespace std;

struct CellField;

typedef struct gameField
{
	size_t	sizeMatrix;									//������ ������� ����
	size_t	sizeCellpx;									//������ ������
	static const size_t	thicknessBorderpx = 1;			//������� �����
	static const size_t	spaceBetweenCellpx = 4;			//���������� �/� �������� 
	static const size_t	thicknessContent = 4;			//������� ����� O X
		
	D2D1_COLOR_F backgroundColour;						//���� ���� ����

	vector<shared_ptr<CellField>>             cells;		//������ �����
	vector<shared_ptr<CellField>>::iterator   selection;	//��������� ������

	shared_ptr<CellField> Selection();

	void ClearSelection() { selection = cells.end(); }
	BOOL CheckEmptyCellOnTheField();
	
	gameField();
	size_t GetSizepx();
} GameField;


typedef struct CellField
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

	float lengthContent;			//������ �������� ��� O X
	float radiusZero;				//������ O
	float halfLengthDiagonalCross;	//������ �������� ��������� X

	CellField(GameField* gField);

	BOOL HitTest(POINT pt);

	void DrawCell(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	void DrawValue(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	BOOL CheckEmptyInTheCell();	
	void SetValueOnCell(Cell value);

};
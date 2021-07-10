#include "GameField.h"


size_t gameField::GetSizepx()
{
	return (sizeMatrix * sizeCellpx + (sizeMatrix + 1) * spaceBetweenCellpx);
}

void CellField::Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush)
{
	pBrush->SetColor(D2D1::ColorF(0.678f, 0.847f, 0.9f));
	pRT->FillRectangle(rect, pBrush);
	pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
	//pRT->DrawRectangle(rect, pBrush, gameField::thicknessBorderpx/100.0f);
	D2D1_RECT_F rectIn;
	rectIn.top = rect.top + gameField::thicknessBorderpx;
	rectIn.left = rect.left + gameField::thicknessBorderpx;
	rectIn.bottom = rect.bottom - gameField::thicknessBorderpx;
	rectIn.right = rect.right - gameField::thicknessBorderpx;
	pRT->FillRectangle(rectIn, pBrush);
}
#include "GameField.h"


size_t gameField::GetSizepx()
{
	return (sizeMatrix * sizeCellpx + (sizeMatrix + 1) * spaceBetweenCellpx);
}

void CellField::Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush)
{
	pBrush->SetColor(color);
	pRT->FillRectangle(rect, pBrush);
	pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	pRT->DrawRectangle(rect, pBrush, 1.0f);
}
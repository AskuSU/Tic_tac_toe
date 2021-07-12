#include "GameField.h"

size_t gameField::GetSizepx()
{
	return (sizeMatrix * sizeCellpx + (sizeMatrix + 1) * spaceBetweenCellpx);
}

shared_ptr<CellField> gameField::Selection()
{
	if (selection == cells.end())
	{
		return nullptr;
	}
	else
	{
		return (*selection);
	}
}

BOOL gameField::CheckEmptyCellOnTheField()
{
	for (auto cel : cells )
	{
		if (cel->cell == CellField::Cell::empty)
		{
			return TRUE;
		}
	}
	return FALSE;
}

gameField::gameField()
{
	sizeMatrix = 3;
	sizeCellpx = 200;

	backgroundColour = D2D1::ColorF(D2D1::ColorF::Black);
}

void CellField::DrawCell(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush)
{
	pBrush->SetColor(cellColour);
	pRT->FillRectangle(rect, pBrush);
	pBrush->SetColor(gameField->backgroundColour);
	D2D1_RECT_F rectIn;
	rectIn.top = rect.top + gameField::thicknessBorderpx;
	rectIn.left = rect.left + gameField::thicknessBorderpx;
	rectIn.bottom = rect.bottom - gameField::thicknessBorderpx;
	rectIn.right = rect.right - gameField::thicknessBorderpx;
	pRT->FillRectangle(rectIn, pBrush);
}

void CellField::DrawValue(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush)
{
	switch (cell)
	{
	case Cell::empty:
		pBrush->SetColor(gameField->backgroundColour);
		D2D1_RECT_F rectIn;
		rectIn.top = rect.top + gameField->thicknessBorderpx;
		rectIn.left = rect.left + gameField->thicknessBorderpx;
		rectIn.bottom = rect.bottom - gameField->thicknessBorderpx;
		rectIn.right = rect.right - gameField->thicknessBorderpx;
		pRT->FillRectangle(rectIn, pBrush);
		break;

	case Cell::zero:
		ellipse = D2D1::Ellipse(D2D1::Point2F((rect.left + rect.right)/2, (rect.top + rect.bottom)/2), radiusZero, radiusZero);
		pBrush->SetColor(zeroColour);
		pRT->DrawEllipse(ellipse, pBrush, gameField->thicknessContent);
		break;

	case Cell::cross:
		D2D1_POINT_2F a, b, centerRect;
		centerRect = D2D1::Point2F((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
		a = D2D1::Point2F(centerRect.x, centerRect.y - halfLengthDiagonalCross);
		b = D2D1::Point2F(a.x, a.y + 2*halfLengthDiagonalCross);
		
		D2D1::Matrix3x2F mat = 
			D2D1::Matrix3x2F::Rotation(45.0f, centerRect);

		D2D1_POINT_2F aa, bb;
		aa = mat.TransformPoint(a);
		bb = mat.TransformPoint(b);

		pBrush->SetColor(crossColour);
		pRT->DrawLine(aa, bb, pBrush, gameField->thicknessContent);

		mat = D2D1::Matrix3x2F::Rotation(-45.0f, centerRect);
		aa = mat.TransformPoint(a);
		bb = mat.TransformPoint(b);

		pRT->DrawLine(aa, bb, pBrush, gameField->thicknessContent);
		break;
	}
}

BOOL CellField::HitTest(POINT pt)
{
	return ((rect.left < pt.x) && (rect.right > pt.x)) && ((rect.top < pt.y) && (rect.bottom > pt.y));
}

CellField::CellField(GameField* gField) : cell(Cell::empty), color(gField->backgroundColour), ellipse(), rect(D2D1::RectF())
{
	gameField = gField;
	lengthContent = gameField->sizeCellpx * 0.75f;
	radiusZero = lengthContent / 2.0f;
	halfLengthDiagonalCross = lengthContent * 1.414f * 0.5f;

	cellColour = D2D1::ColorF(0.678f, 0.847f, 0.9f);
	zeroColour = D2D1::ColorF(0.0f, 1.0f, 1.0f);
	crossColour = D2D1::ColorF(1.0f, 0.753f, 0.796f);

}

void CellField::SetValueOnCell(Cell value)
{
	cell = value;
	/*if (cell == Cell::empty)
	{
		cell = Cell::zero;
		return;
	}
	if (cell == Cell::zero)
	{
		cell = Cell::cross;
		return;
	}
	if (cell == Cell::cross)
	{
		cell = Cell::empty;
		return;
	}*/
}

BOOL CellField::CheckEmptyInTheCell()
{
	return cell == Cell::empty;
}


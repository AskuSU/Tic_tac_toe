#include "GameField.h"

float CellField::lengthContent = gameField::sizeCellpx * 0.75f;
float CellField::radiusZero = CellField::lengthContent / 2.0f;
float CellField::halfLengthDiagonalCross = CellField::lengthContent * 1.414f * 0.5f;

const D2D1_COLOR_F gameField::backgroundColour = D2D1::ColorF(D2D1::ColorF::Black);
const D2D1_COLOR_F CellField::cellColour = D2D1::ColorF(0.678f, 0.847f, 0.9f);
const D2D1_COLOR_F CellField::zeroColour = D2D1::ColorF(0.0f, 1.0f, 1.0f);
const D2D1_COLOR_F CellField::crossColour = D2D1::ColorF(1.0f, 0.753f, 0.796f);

size_t gameField::GetSizepx()
{
	return (sizeMatrix * sizeCellpx + (sizeMatrix + 1) * spaceBetweenCellpx);
}

void CellField::DrawCell(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush)
{
	pBrush->SetColor(cellColour);
	pRT->FillRectangle(rect, pBrush);
	pBrush->SetColor(gameField::backgroundColour);
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
		pBrush->SetColor(gameField::backgroundColour);
		D2D1_RECT_F rectIn;
		rectIn.top = rect.top + gameField::thicknessBorderpx;
		rectIn.left = rect.left + gameField::thicknessBorderpx;
		rectIn.bottom = rect.bottom - gameField::thicknessBorderpx;
		rectIn.right = rect.right - gameField::thicknessBorderpx;
		pRT->FillRectangle(rectIn, pBrush);
		break;

	case Cell::zero:
		ellipse = D2D1::Ellipse(D2D1::Point2F((rect.left + rect.right)/2, (rect.top + rect.bottom)/2), CellField::radiusZero, CellField::radiusZero);
		pBrush->SetColor(zeroColour);
		pRT->DrawEllipse(ellipse, pBrush, gameField::thicknessContent);
		break;

	case Cell::cross:
		D2D1_POINT_2F a, b, centerRect;
		centerRect = D2D1::Point2F((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
		a = D2D1::Point2F(centerRect.x, centerRect.y - CellField::halfLengthDiagonalCross);
		b = D2D1::Point2F(a.x, a.y + 2*CellField::halfLengthDiagonalCross);
		
		D2D1::Matrix3x2F mat = 
			D2D1::Matrix3x2F::Rotation(45.0f, centerRect);

		D2D1_POINT_2F aa, bb;
		aa = mat.TransformPoint(a);
		bb = mat.TransformPoint(b);

		pBrush->SetColor(crossColour);
		pRT->DrawLine(aa, bb, pBrush, gameField::thicknessContent);

		mat = D2D1::Matrix3x2F::Rotation(-45.0f, centerRect);
		aa = mat.TransformPoint(a);
		bb = mat.TransformPoint(b);

		pRT->DrawLine(aa, bb, pBrush, gameField::thicknessContent);
		break;
	}
}

BOOL CellField::HitTest(POINT pt)
{
	return ((rect.left < pt.x) && (rect.right > pt.x)) && ((rect.top < pt.y) && (rect.bottom > pt.y));
}

void CellField::SetValueOnCell()
{
	if (cell == Cell::empty)
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
	}
}

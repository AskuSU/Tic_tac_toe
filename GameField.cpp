#include "GameField.h"


size_t gameField::GetSizepx()
{
	return (sizeMatrix * sizeCellpx + (sizeMatrix + 1) * spaceBetweenCellpx);
}
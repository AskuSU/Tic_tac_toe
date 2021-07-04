#pragma once

struct gameField
{
	size_t sizeMatrix = 3,
		sizeCellpx = 50,
		thicknessBorderpx = 1,
		spaceBetweenCellpx = 3;

	size_t GetSizepx();
};
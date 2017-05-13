#ifndef CHIP_DESIGN_TYPEDEFS_H
#define CHIP_DESIGN_TYPEDEFS_H

using Coord = int;

enum Dimension
{
	DIM_X = 0,
	DIM_Y = 1,
	DIM_Z = 2,
	NUM_DIM = 3
};

auto const DIMENSIONS = {DIM_X, DIM_Y, DIM_Z};

std::string to_string(Dimension const dimension);

#endif //CHIP_DESIGN_TYPEDEFS_H

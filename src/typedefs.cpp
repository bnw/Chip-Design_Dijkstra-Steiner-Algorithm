#include "typedefs.h"

std::basic_string<char, std::char_traits<char>, std::allocator<char>> to_string(Dimension const dimension)
{
	switch (dimension) {
		case DIM_X:
			return "DIM_X";
		case DIM_Y:
			return "DIM_Y";
		case DIM_Z:
			return "DIM_Z";
		case NUM_DIM:
			return "NUM_DIM";
		default:
			abort();
	}
}

#ifndef CHIP_DESIGN_POSITION3D_H
#define CHIP_DESIGN_POSITION3D_H

#include <string>
#include "typedefs.h"

class Position3D
{
public:
	bool operator==(Position3D const &rhs) const;

	bool operator!=(Position3D const &rhs) const;

	std::string to_string() const
	{
		return "[x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", z=" + std::to_string(z) + "]";
	}

public:
	Coordinate x;
	Coordinate y;
	Coordinate z;
};


#endif //CHIP_DESIGN_POSITION3D_H

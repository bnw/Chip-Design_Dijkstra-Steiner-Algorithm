#ifndef CHIP_DESIGN_POSITION3D_H
#define CHIP_DESIGN_POSITION3D_H

#include "typedefs.h"

class Position3D
{
public:
	bool operator==(Position3D const &rhs) const;

	bool operator!=(Position3D const &rhs) const;

public:
	Coordinate x;
	Coordinate y;
	Coordinate z;
};


#endif //CHIP_DESIGN_POSITION3D_H

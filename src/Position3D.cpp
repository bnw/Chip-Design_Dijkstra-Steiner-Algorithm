

#include "Position3D.h"

bool Position3D::operator==(Position3D const &rhs) const
{
	return x == rhs.x &&
		   y == rhs.y &&
		   z == rhs.z;
}

bool Position3D::operator!=(Position3D const &rhs) const
{
	return !(rhs == *this);
}

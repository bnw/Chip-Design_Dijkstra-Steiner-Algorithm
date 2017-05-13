#include "Position.h"

bool Position::operator==(Position const &rhs) const
{
	return coordinates == rhs.coordinates;
}

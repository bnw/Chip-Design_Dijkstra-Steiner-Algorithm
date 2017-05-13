

#include "Terminal.h"

Terminal::Terminal(Position3D const &position) : position(position)
{}

bool Terminal::operator==(Terminal const &rhs) const
{
	return position == rhs.position;
}

bool Terminal::operator!=(Terminal const &rhs) const
{
	return !(rhs == *this);
}

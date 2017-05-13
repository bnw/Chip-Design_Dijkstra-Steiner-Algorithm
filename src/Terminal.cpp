

#include "Terminal.h"

Terminal::Terminal(Position const &position) : position(position)
{}

bool Terminal::operator==(Terminal const &rhs) const
{
	return position == rhs.position;
}

bool Terminal::operator!=(Terminal const &rhs) const
{
	return !(rhs == *this);
}

Position const &Terminal::get_position() const
{
	return position;
}

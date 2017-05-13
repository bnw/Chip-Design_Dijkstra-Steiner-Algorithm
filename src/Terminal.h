#ifndef CHIP_DESIGN_TERMINAL_H
#define CHIP_DESIGN_TERMINAL_H


#include "Position.h"

class Terminal
{
public:
	Terminal(Position const &position);

	bool operator==(Terminal const &rhs) const;

	bool operator!=(Terminal const &rhs) const;

	Position const &get_position() const;

private:
	Position const position;
};


#endif //CHIP_DESIGN_TERMINAL_H

#ifndef CHIP_DESIGN_TERMINAL_H
#define CHIP_DESIGN_TERMINAL_H


#include "Position3D.h"

class Terminal
{
public:
	Terminal(Position3D const &position);

	bool operator==(Terminal const &rhs) const;

	bool operator!=(Terminal const &rhs) const;

private:
	Position3D const position;
};


#endif //CHIP_DESIGN_TERMINAL_H

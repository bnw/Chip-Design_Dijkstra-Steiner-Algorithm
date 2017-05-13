#ifndef CHIP_DESIGN_READER_H
#define CHIP_DESIGN_READER_H

#include <iosfwd>
#include <vector>
#include <sstream>
#include <iostream>
#include "Terminal.h"
#include "typedefs.h"

class Reader
{
public:
	std::vector<Terminal> read(std::istream &input) const
	{
		std::vector<Terminal> terminals;
		int n;
		input >> n;
		for (int i = 0; i < n; i++) {
			input >> std::ws;
			if (input.eof()) {
				throw std::runtime_error("Input contains less than " + std::to_string(n) + " data rows.");
			}
			std::string line_buffer;
			std::getline(input, line_buffer);
			std::istringstream line_stream(line_buffer);

			Coord x, y, z;
			line_stream >> x >> y >> z >> std::ws;
			terminals.emplace_back(Position{x, y, z});
			if (not line_stream.eof()) {
				throw std::runtime_error("Data line contains more than 3 numbers.");
			}
		}
		input >> std::ws;
		if (not input.eof()) {
			throw std::runtime_error("Input contains more than " + std::to_string(n) + " data rows.");
		}
		return terminals;
	}

};


#endif //CHIP_DESIGN_READER_H

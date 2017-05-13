#ifndef CHIP_DESIGN_HANANGRIDGRAPH_H
#define CHIP_DESIGN_HANANGRIDGRAPH_H

#include <set>
#include <vector>
#include <assert.h>
#include "../Position.h"

namespace grid {

class Node
{
public:
	Node(std::array<std::set<int>::const_iterator, NUM_DIM> const &coordinate_iterators)
			: coordinate_iterators(coordinate_iterators)
	{}

	Position position() const
	{
		std::array<Coord, NUM_DIM> coordinates;
		for (auto const dimension : DIMENSIONS) {
			coordinates.at(dimension) = *coordinate_iterators.at(dimension);
		}
		return {coordinates};
	}

	auto const &get_coordinate_iterators() const
	{
		return coordinate_iterators;
	}

private:
	std::array<std::set<Coord>::const_iterator, NUM_DIM> coordinate_iterators;
};

class HananGridGraph
{
public:
	using Coordinates = std::set<Coord>;

	void add_feasible_position(Position const &position);

	/**
	 * Runtime is linear in the number of dimensions.
	 */
	std::vector<Node> neighbors(Node const &node) const;

	Node create_node(Position const &position) const;

private:
	Coordinates &coordinates(Dimension const dimension);

	Coordinates const &coordinates(Dimension const dimension) const;

	std::array<Coordinates, NUM_DIM> dimension_coordinates;
};


}

#endif //CHIP_DESIGN_HANANGRIDGRAPH_H
#ifndef CHIP_DESIGN_HANANGRIDGRAPH_H
#define CHIP_DESIGN_HANANGRIDGRAPH_H

#include <set>
#include <vector>
#include <assert.h>
#include "../Position.h"

namespace graph {

class Node
{
public:
	Node(std::array<std::vector<Coord>::const_iterator, NUM_DIM> const &coordinate_iterators)
			: coordinate_iterators(coordinate_iterators)
	{}

	Position get_position() const
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

	bool operator==(Node const &rhs) const
	{
		return get_position() == rhs.get_position();
	}

	Coord distance(Node const& other) const{
		return get_position().distance(other.get_position());
	}

	bool operator<(Node const &rhs) const
	{
		return coordinate_iterators < rhs.coordinate_iterators;
	}

private:
	std::array<std::vector<Coord>::const_iterator, NUM_DIM> coordinate_iterators;
};

class HananGridGraph
{
public:
	using Coordinates = std::vector<Coord>;

	HananGridGraph(Position::Vector const& positions){
		for(auto const& position : positions){
			add_feasible_position(position);
		}
	}

	/**
	 * Runtime is linear in the number of dimensions.
	 */
	std::vector<Node> neighbors(Node const &node) const;

	Node create_node(Position const &position) const;

	size_t get_index(Node const &node) const
	{
		size_t sum = 0;
		size_t offset = 1;
		for (auto const &dimension : DIMENSIONS) {
			sum += offset *
				   std::distance(coordinates(dimension).begin(), node.get_coordinate_iterators().at(dimension));
			offset *= coordinates(dimension).size();
		}
		return sum;
	}

	size_t num_nodes() const
	{
		size_t num = 1;
		for (auto const &dimension : DIMENSIONS) {
			num *= coordinates(dimension).size();
		}
		return num;
	}
private:
	void add_feasible_position(Position const &position);

	Coordinates &coordinates(Dimension const dimension);

	Coordinates const &coordinates(Dimension const dimension) const;

	std::array<Coordinates, NUM_DIM> dimension_coordinates;
};


}

#endif //CHIP_DESIGN_HANANGRIDGRAPH_H

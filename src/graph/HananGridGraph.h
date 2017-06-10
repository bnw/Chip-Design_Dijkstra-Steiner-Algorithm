#ifndef CHIP_DESIGN_HANANGRIDGRAPH_H
#define CHIP_DESIGN_HANANGRIDGRAPH_H

#include <set>
#include <vector>
#include <assert.h>
#include "../Position.h"
#include "Node.h"

namespace graph {

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

	/**
	 * Calculates a unique index of a node.
	 * Index is between 0 and num_nodes().
	 */
	size_t get_index(Node const &node) const
	{
		size_t sum = 0;
		size_t offset = 1;
		for (auto const &dimension : DIMENSIONS) {
			sum += offset *
				   std::distance(coordinates(dimension).begin(), node.get_coordinate_iterators().at(dimension));
			offset *= coordinates(dimension).size();
		}
		assert(sum < num_nodes());
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

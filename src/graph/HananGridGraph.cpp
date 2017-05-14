#include "HananGridGraph.h"

namespace graph {

void HananGridGraph::add_feasible_position(Position const &position)
{
	for (auto const dimension : DIMENSIONS) {
		coordinates(dimension).emplace(position.coord(dimension));
	}
}

std::vector<Node> HananGridGraph::neighbors(Node const &node) const
{
	std::vector<Node> neighbors;
	auto const &coordinate_iterators = node.get_coordinate_iterators();
	for (auto const dimension : DIMENSIONS) {
		if (coordinate_iterators.at(dimension) != dimension_coordinates.at(dimension).begin()) {
			auto coordinate_iterators_copy = coordinate_iterators;
			coordinate_iterators_copy.at(dimension)--;
			neighbors.emplace_back(coordinate_iterators_copy);
		}
		if (coordinate_iterators.at(dimension) != std::prev(dimension_coordinates.at(dimension).end())) {
			auto coordinate_iterators_copy = coordinate_iterators;
			coordinate_iterators_copy.at(dimension)++;
			neighbors.emplace_back(coordinate_iterators_copy);
		}
	}
	return neighbors;
}

Node HananGridGraph::create_node(Position const &position) const
{
	std::array<HananGridGraph::Coordinates::const_iterator, NUM_DIM> coordinate_iterators;
	for (auto const dimension : DIMENSIONS) {
		coordinate_iterators.at(dimension) = coordinates(dimension).find(position.coord(dimension));
		assert(coordinate_iterators.at(dimension) != coordinates(dimension).end());
	}
	return  {coordinate_iterators};
}

HananGridGraph::Coordinates &HananGridGraph::coordinates(Dimension const dimension)
{
	return dimension_coordinates.at(dimension);
}

HananGridGraph::Coordinates const &HananGridGraph::coordinates(Dimension const dimension) const
{
	return dimension_coordinates.at(dimension);
}

}
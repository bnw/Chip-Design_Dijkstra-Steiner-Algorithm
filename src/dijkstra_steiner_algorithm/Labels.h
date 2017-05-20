#ifndef CHIP_DESIGN_LABELS_H
#define CHIP_DESIGN_LABELS_H


#include "../graph/HananGridGraph.h"

namespace dijkstra_steiner_algorithm {

class Instance;
class NodePlusTerminalSubset;

class Labels
{
public:
	Labels(Instance const &instance);

	Coord get(NodePlusTerminalSubset const &node_plus_terminal_subset) const;

	void set(NodePlusTerminalSubset const &node_plus_terminal_subset, Coord const new_value);

	//public for unit tests
	size_t get_index(NodePlusTerminalSubset const &node_plus_terminal_subset) const;

private:
	graph::HananGridGraph const &graph;
	std::vector<Coord> labels;
};

}


#endif //CHIP_DESIGN_LABELS_H

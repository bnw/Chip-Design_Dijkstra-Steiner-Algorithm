#ifndef CHIP_DESIGN_LABELS_H
#define CHIP_DESIGN_LABELS_H


#include "../graph/HananGridGraph.h"
#include "../TerminalSubset.h"
#include "NodePlusTerminalSubset.h"

namespace dijkstra_steiner_algorithm {

class Instance;

class Labels
{
public:
	Labels(Instance const &instance);

	Coord get(NodePlusTerminalSubset const &node_plus_terminal_subset) const;

	void set(NodePlusTerminalSubset const &node_plus_terminal_subset, Coord const new_value);

	void mark_permanently_labeled(NodePlusTerminalSubset const &node_plus_terminal_subset);

	bool is_permanently_labeled(NodePlusTerminalSubset const &node_plus_terminal_subset) const;

	std::vector<TerminalSubset> const &get_permanently_labeled_subsets_for_node(graph::Node const &node) const;

	//public for unit tests
	size_t get_index(NodePlusTerminalSubset const &node_plus_terminal_subset) const;

private:
	graph::HananGridGraph const &graph;
	std::vector<Coord> labels;
	std::vector<bool> permanently_labeled;
	std::vector<std::vector<TerminalSubset>> permanently_labeled_subsets;
};

}


#endif //CHIP_DESIGN_LABELS_H

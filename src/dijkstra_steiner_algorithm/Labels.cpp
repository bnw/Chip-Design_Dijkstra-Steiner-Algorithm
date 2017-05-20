#include "Labels.h"
#include "DijkstraSteinerAlgorithm.h"

namespace dijkstra_steiner_algorithm {

Labels::Labels(Instance const &instance) :
		graph(instance.graph),
		labels(graph.num_nodes() * pow2(instance.terminals.size()), std::numeric_limits<Coord>::max())
{}

Coord Labels::get(NodePlusTerminalSubset const &node_plus_terminal_subset) const
{
	return labels.at(get_index(node_plus_terminal_subset));
}

void Labels::set(NodePlusTerminalSubset const &node_plus_terminal_subset, Coord const new_value)
{
	labels.at(get_index(node_plus_terminal_subset)) = new_value;
}

size_t Labels::get_index(NodePlusTerminalSubset const &node_plus_terminal_subset) const
{
	return
			node_plus_terminal_subset.subset.get_index()
			+ graph.get_index(node_plus_terminal_subset.node) * pow2(node_plus_terminal_subset.subset.max_size());
}

}
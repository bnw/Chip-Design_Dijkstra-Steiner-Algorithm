#include "Labels.h"
#include "DijkstraSteinerAlgorithm.h"

namespace dijkstra_steiner_algorithm {

Labels::Labels(Instance const &instance) :
		graph(instance.graph),
		labels(graph.num_nodes() * pow2(instance.terminals.size()), std::numeric_limits<Coord>::max()),
		permanently_labeled(graph.num_nodes() * pow2(instance.terminals.size()), false),
		permanently_labeled_subsets(graph.num_nodes())
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

void Labels::mark_permanently_labeled(NodePlusTerminalSubset const &node_plus_terminal_subset)
{
	assert(not is_permanently_labeled(node_plus_terminal_subset));
	permanently_labeled[get_index(node_plus_terminal_subset)] = true;
	permanently_labeled_subsets
			.at(graph.get_index(node_plus_terminal_subset.node))
			.push_back(node_plus_terminal_subset.subset);
}

bool Labels::is_permanently_labeled(NodePlusTerminalSubset const &node_plus_terminal_subset) const
{
	return permanently_labeled[get_index(node_plus_terminal_subset)];
}

std::vector<TerminalSubset> const &Labels::get_permanently_labeled_subsets_for_node(graph::Node const &node) const
{
	return permanently_labeled_subsets.at(graph.get_index(node));
}

}
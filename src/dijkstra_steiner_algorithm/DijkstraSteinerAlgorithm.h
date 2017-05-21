#ifndef CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H
#define CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H


#include <map>
#include "../graph/HananGridGraph.h"
#include "../Terminal.h"
#include "../heap/Heap.h"
#include "../utils.h"
#include "../TerminalSubset.h"
#include "Labels.h"

namespace dijkstra_steiner_algorithm {

class Instance
{
public:
	static Instance create(Terminal::Vector const &terminals)
	{
		Position::Vector positions;
		for (auto const &terminal:terminals) {
			positions.push_back(terminal.get_position());
		}
		return {graph::HananGridGraph{positions}, terminals, terminals.front()};
	}

	graph::HananGridGraph const graph;
	Terminal::Vector const &terminals; // contains t
	Terminal const &t;
};

class NodePlusTerminalSubset
{
public:
	bool operator<(NodePlusTerminalSubset const &rhs) const
	{
		return std::tie(node, subset) < std::tie(rhs.node, rhs.subset);
	}

	graph::Node const node;
	TerminalSubset const subset;
};

class DijkstraSteinerAlgorithm
{
public:
	DijkstraSteinerAlgorithm(Instance const &instance) :
			instance(instance),
			labels(instance)
	{}

	Coord calculate_minimum_steiner_tree_length()
	{
		heap::Heap<Coord, NodePlusTerminalSubset> heap(
				[](NodePlusTerminalSubset const &lhs, NodePlusTerminalSubset const &rhs) {
					return lhs < rhs;
				}
		);

		std::vector<std::vector<TerminalSubset>> P(instance.graph.num_nodes());

		auto T_minus_t = TerminalSubset::create_empty(instance.terminals);
		for (auto const &terminal : instance.terminals) {
			if (terminal != instance.t) {
				T_minus_t.add(terminal);
			}
		}


		// Line 1
		for (auto const &terminal : instance.terminals) {
			NodePlusTerminalSubset const node_plus_subset
					= {
							instance.graph.create_node(terminal.get_position()),
							TerminalSubset::create_singleton(terminal, instance.terminals)
					};
			update_l(heap, node_plus_subset, 0);
		}


		// Line 2
		auto const empty_terminal_subset = TerminalSubset::create_empty(instance.terminals);
		//Adding to P not necessary?
		// -> Never add sth. with empty_subset to heap


		// Line 3
		while (true) {
			auto const v_I = heap.pop_minimum();
			auto const &v = v_I.node;
			auto const &I = v_I.subset;

			bool contained_in_P = false;
			for (auto const &subset : P.at(instance.graph.get_index(v))) {
				if (subset == I) {
					contained_in_P = true;
					break;
				}
			}
			if (contained_in_P) { continue; }

			// Line 4

			P.at(instance.graph.get_index(v)).push_back(I);

			// Line 5
			if (v.get_position() == instance.t.get_position() and I == T_minus_t) {
				return labels.get(v_I);
			}

			// Line 6
			for (auto const &neighbor : instance.graph.neighbors(v)) {
				Coord new_l_value = labels.get(v_I) + v.distance(neighbor);
				NodePlusTerminalSubset w_I = {neighbor, I};
				if (new_l_value < labels.get(w_I)) {
					update_l(heap, w_I, new_l_value);
				}
			}

			// Line 7
			auto const T_minus_I_and_t =
					TerminalSubset::create_full(instance.terminals)
							.minus(I)
							.minus(TerminalSubset::create_singleton(instance.t, instance.terminals));
			for (auto const &J : P.at(instance.graph.get_index(v))) {
				if (T_minus_I_and_t.contains(J)) {
					auto const I_union_J = TerminalSubset{I}.plus(J);
					NodePlusTerminalSubset const v_I_union_J = {v, I_union_J};
					Coord new_l_value =
							std::min(
									labels.get(v_I_union_J),
									labels.get(v_I)
									+ labels.get(NodePlusTerminalSubset{v, J})
							);
					update_l(heap, v_I_union_J, new_l_value);
				}
			}
		}
	}

private:

	void update_l(
			heap::Heap<Coord, NodePlusTerminalSubset> &heap,
			NodePlusTerminalSubset const &v_I,
			Coord const new_l_value
	)
	{
		Coord const old_value = labels.get(v_I);
		Coord const lb = lower_bound({v_I.node, v_I.subset.complement()});
		heap.erase_if_exists(old_value + lb, v_I);
		heap.insert(new_l_value + lb, v_I);
		labels.set(v_I, new_l_value);
	}

	Coord lower_bound(NodePlusTerminalSubset node_plus_terminal_subset) const
	{
		return bounding_box(node_plus_terminal_subset) / 2;
	}

	Coord bounding_box(NodePlusTerminalSubset const &node_plus_terminal_subset) const
	{
		Coord sum = 0;
		for (auto const &dimension : DIMENSIONS) {
			Coord max = node_plus_terminal_subset.node.get_position().coord(dimension);
			Coord min = max;
			for (auto const &terminal : instance.terminals) {
				if (node_plus_terminal_subset.subset.contains(terminal)) {
					max = std::max(max, terminal.get_position().coord(dimension));
					min = std::min(min, terminal.get_position().coord(dimension));
				}
			}
			sum += max - min;
		}
		return sum * 2;
	}

	Instance const &instance;
	Labels labels;
};

}

#endif //CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H

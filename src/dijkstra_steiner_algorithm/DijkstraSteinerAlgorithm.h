#ifndef CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H
#define CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H


#include "../graph/HananGridGraph.h"
#include "../Terminal.h"
#include "../heap/Heap.h"
#include "../utils.h"
#include "../TerminalSubset.h"
#include "Labels.h"
#include "lower_bound/BoundingBoxLowerBound.h"
#include "lower_bound/MinimumSpanningTreeLowerBound.h"

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
			labels(instance),
			heap(),
			lower_bound_oracle_bb(instance.terminals),
			lower_bound_oracle_mst(instance.terminals)
	{}

	Coord calculate_minimum_steiner_tree_length()
	{
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
		//Adding to P not necessary?
		// -> Never add sth. with empty_subset to heap


		// Line 3
		while (true) {
			auto const v_I = heap.pop_minimum();
			auto const &v = v_I.node;
			auto const &I = v_I.subset;
			auto const label_of_v_I = labels.get(v_I);

			if (labels.is_permanently_labeled(v_I)) {
				continue;
			}

			// Line 4
			labels.mark_permanently_labeled(v_I);

			// Line 5
			if (v.get_position() == instance.t.get_position() and I == T_minus_t) {
				return labels.get(v_I);
			}

			// Line 6
			update_neighbors(v, I, label_of_v_I);

			// Line 7
			auto const T_minus_I_and_t =
					TerminalSubset::create_full(instance.terminals)
							.minus(I)
							.minus(TerminalSubset::create_singleton(instance.t, instance.terminals));
			update_subsets_in_P(T_minus_I_and_t, v, I, label_of_v_I);

		}
	}

private:
	void update_subsets_in_P(
			TerminalSubset const &T_minus_I_and_t,
			graph::Node const &v,
			TerminalSubset const &I,
			Coord const label_of_v_I
	)
	{
		for (auto const &J : labels.get_permanently_labeled_subsets_for_node(v)) {
			if (T_minus_I_and_t.contains(J)) {
				auto const I_union_J = TerminalSubset{I}.plus(J);
				NodePlusTerminalSubset const v_I_union_J = {v, I_union_J};
				Coord new_l_value =
						std::min(
								labels.get(v_I_union_J),
								label_of_v_I + labels.get(NodePlusTerminalSubset{v, J})
						);
				update_l(heap, v_I_union_J, new_l_value);
			}
		}
	}

	void update_neighbors(graph::Node const &v, TerminalSubset const &I, Coord const label_of_v_I)
	{
		for (auto const &neighbor : instance.graph.neighbors(v)) {
			Coord new_l_value = label_of_v_I + v.distance(neighbor);
			NodePlusTerminalSubset const w_I = {neighbor, I};
			if (new_l_value < labels.get(w_I)) {
				update_l(heap, w_I, new_l_value);
			}
		}
	}

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

	Coord lower_bound(NodePlusTerminalSubset node_plus_terminal_subset)
	{
		return std::max(
				lower_bound_oracle_mst.lower_bound(
						node_plus_terminal_subset.node,
						node_plus_terminal_subset.subset
				),
				lower_bound_oracle_bb.lower_bound(
						node_plus_terminal_subset.node,
						node_plus_terminal_subset.subset
				)
		);
	}

	Instance const &instance;
	Labels labels;
	heap::Heap<Coord, NodePlusTerminalSubset> heap;
	lower_bound::BoundingBoxLowerBound lower_bound_oracle_bb;
	lower_bound::MinimumSpanningTreeLowerBound lower_bound_oracle_mst;
};

}

#endif //CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H

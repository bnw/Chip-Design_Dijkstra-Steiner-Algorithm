#include <boost/test/unit_test.hpp>
#include "../../src/dijkstra_steiner_algorithm/Labels.h"
#include "../../src/dijkstra_steiner_algorithm/DijkstraSteinerAlgorithm.h"


BOOST_AUTO_TEST_CASE(TestLabels_get_index)
{
	using namespace dijkstra_steiner_algorithm;

	Terminal::Vector terminals = {
			{{0, 0, 0}, 0},
			{{1, 1, 1}, 1},
			{{2, 2, 2}, 2},
			{{3, 3, 3}, 3}
	};
	auto const instance = Instance::create(terminals);
	auto const &graph = instance.graph;

	std::vector<graph::Node> nodes;
	for (auto const x : {0, 1, 2, 3}) {
		for (auto const y : {0, 1, 2, 3}) {
			for (auto const z : {0, 1, 2, 3}) {
				nodes.push_back(graph.create_node({x, y, z}));
			}
		}
	}

	Labels const labels(instance);
	auto const full_subset = TerminalSubset::create_full(terminals);

	std::set<size_t> seen_indices;
	size_t max_index = 0;
	for (auto const &subset : full_subset.create_nonempty_subsets()) {
		for (auto const &node : nodes) {
			auto const index = labels.get_index({node, subset});
			BOOST_TEST(0 == seen_indices.count(index));
			seen_indices.insert(index);
			max_index = std::max(max_index, index);
		}
	}
	BOOST_TEST(nodes.size() * (pow2(terminals.size()) - 1) == seen_indices.size());
	BOOST_TEST(max_index <= seen_indices.size() + nodes.size());
}
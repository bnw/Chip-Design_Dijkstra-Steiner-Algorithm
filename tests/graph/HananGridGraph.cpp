#include <boost/test/unit_test.hpp>
#include "../../src/graph/HananGridGraph.h"
#include "../../src/utils.h"

using namespace grid;

struct SimpleGrid
{
	SimpleGrid() : graph()
	{
		graph.add_feasible_position({1, 1, 1});
		graph.add_feasible_position({2, 2, 2});
		graph.add_feasible_position({3, 3, 3});
	}

	HananGridGraph graph;
};

BOOST_FIXTURE_TEST_CASE(TestHananGrid1, SimpleGrid)
{
	auto const center = graph.create_node({2, 2, 2});
	BOOST_TEST(6 == graph.neighbors(center).size());
}

BOOST_FIXTURE_TEST_CASE(TestHananGrid2, SimpleGrid)
{
	auto const corner = graph.create_node({1, 1, 1});
	BOOST_TEST(3 == graph.neighbors(corner).size());
}

BOOST_FIXTURE_TEST_CASE(TestHananGrid3, SimpleGrid)
{
	auto const center = graph.create_node({2, 2, 2});
	auto const neighbors = graph.neighbors(center);
	std::vector<Position> expected_neighbors_positions = {
			{1, 2, 2},
			{3, 2, 2},
			{2, 1, 2},
			{2, 3, 2},
			{2, 2, 1},
			{2, 2, 3},
	};
	auto const actual_neighbors_positions
			= transform<Position>(neighbors, [](Node const &node) { return node.position(); });
	BOOST_TEST(expected_neighbors_positions == actual_neighbors_positions);
}
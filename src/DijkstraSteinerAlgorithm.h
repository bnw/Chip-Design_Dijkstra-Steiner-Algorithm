#ifndef CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H
#define CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H


#include "graph/HananGridGraph.h"
#include "Terminal.h"

struct Instance{
	graph::HananGridGraph const &graph;
	std::vector<Terminal> const &terminals;
	Terminal const& t;
};

class DijkstraSteinerAlgorithm
{
public:
	DijkstraSteinerAlgorithm(Instance const &instance) : instance(instance)
	{}

private:
	Coord calculate_minimum_steiner_tree_length()
	{
		//TODO
		return 0;
	}

private:
	Instance const& instance;
};


#endif //CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H

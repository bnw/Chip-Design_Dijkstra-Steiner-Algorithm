#include <iostream>
#include <fstream>
#include "Reader.h"
#include "dijkstra_steiner_algorithm/DijkstraSteinerAlgorithm.h"

void print_usage(const char *argv[])
{
	std::cout << "Usage: " << argv[0] << " file" << std::endl;
}

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		print_usage(argv);
		return 1;
	}

	try {
		Reader reader;
		std::ifstream input_file(argv[1]);
		if (input_file.bad() or input_file.fail()) {
			throw std::runtime_error("Cannot open file: " + std::string(argv[1]));
		}
		auto const terminals = reader.read(input_file);

		for (auto const &terminal : terminals) {
			std::cout << terminal.get_position().to_string() << std::endl;
		}

		dijkstra_steiner_algorithm::Instance const instance = dijkstra_steiner_algorithm::Instance::create(terminals);
		dijkstra_steiner_algorithm::DijkstraSteinerAlgorithm algorithm(instance);
		std::cout << "Result: " << algorithm.calculate_minimum_steiner_tree_length();
	} catch (std::exception const &e) {
		std::cout << "Exception orccured: " << e.what();
		return 1;
	}

	return EXIT_SUCCESS;
}


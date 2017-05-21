#ifndef CHIP_DESIGN_TERMINALSUBSET_H
#define CHIP_DESIGN_TERMINALSUBSET_H

#include <vector>
#include <assert.h>
#include "Terminal.h"
#include "utils.h"

class TerminalSubset
{
public:

	TerminalSubset static create_full(Terminal::Vector const &terminals)
	{
		return TerminalSubset(terminals, 1);
	}

	TerminalSubset static create_empty(Terminal::Vector const &terminals)
	{
		return TerminalSubset(terminals, 0);
	}

	TerminalSubset static create_singleton(Terminal const &terminal, Terminal::Vector const &terminals)
	{
		auto terminal_subset = TerminalSubset::create_empty(terminals);
		terminal_subset.add(terminal);
		return terminal_subset;
	}

	TerminalSubset &minus(TerminalSubset const &subtrahend)
	{
		for (size_t i = 0; i < incidence_vector.size(); i++) {
			if (subtrahend.incidence_vector[i]) {
				incidence_vector[i] = false;
			}
		}
		return *this;
	}

	TerminalSubset &plus(TerminalSubset const &addend)
	{
		for (size_t i = 0; i < incidence_vector.size(); i++) {
			if (addend.incidence_vector[i]) {
				incidence_vector[i] = true;
			}
		}
		return *this;
	}

	void add(Terminal const &terminal)
	{
		incidence_vector[terminal.get_index()] = true;
	}

	size_t get_index() const
	{
		size_t index = 0;
		for (size_t i = 0; i < incidence_vector.size(); i++) {
			if (incidence_vector[i]) {
				index += pow2(i);
			}
		}
		return index;
	}

	bool operator==(TerminalSubset const &rhs) const
	{
		return incidence_vector == rhs.incidence_vector;
	}

	bool contains(TerminalSubset const &other) const
	{
		for (size_t i = 0; i < incidence_vector.size(); i++) {
			if (not incidence_vector[i]) {
				if (other.incidence_vector[i]) {
					return false;
				}
			}
		}
		return true;
	}

	bool contains(Terminal const& terminal) const{
		return incidence_vector[terminal.get_index()];
	}

	bool operator<(TerminalSubset const &rhs) const
	{
		return incidence_vector < rhs.incidence_vector;
	}

	size_t max_size() const
	{
		return incidence_vector.size();
	}

	//only used for unit tests
	std::vector<TerminalSubset> const create_nonempty_subsets() const
	{
		if (is_singleton()) {
			return {*this};
		}

		std::vector<TerminalSubset> non_empty_subsets;

		auto copy = *this;
		for (size_t i = 0; i < incidence_vector.size(); i++) {
			if (incidence_vector.at(i)) {
				assert(incidence_vector.at(i) == copy.incidence_vector.at(i));
				copy.incidence_vector.at(i) = false;
				auto subsets_without_i = copy.create_nonempty_subsets();
				append(non_empty_subsets, subsets_without_i);
				for (auto &subset:subsets_without_i) {
					subset.incidence_vector.at(i) = true;
				}
				append(non_empty_subsets, subsets_without_i);
				auto const i_th_singleton = TerminalSubset{*this}.minus(copy);
				non_empty_subsets.push_back(i_th_singleton);
				return non_empty_subsets;
			}
		}

		return {};
	}

	TerminalSubset complement() const{
		TerminalSubset copy = *this;
		for(size_t i = 0; i < incidence_vector.size(); i++){
			copy.incidence_vector[i] = not copy.incidence_vector[i];
		}
		return copy;
	}

private:
	bool is_singleton() const
	{
		size_t sum = 0;
		for (auto const b : incidence_vector) {
			sum += b;
		}
		return sum == 1;
	}

	TerminalSubset(Terminal::Vector const &terminals, bool initial_value) :
			incidence_vector(terminals.size(), initial_value)
	{}

	std::vector<bool> incidence_vector;
};


#endif //CHIP_DESIGN_TERMINALSUBSET_H

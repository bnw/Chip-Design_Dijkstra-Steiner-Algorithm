#include <boost/test/unit_test.hpp>
#include "../src/TerminalSubset.h"

struct TerminalSubsetFixture
{
	Terminal::Vector const terminals = {
			{{1, 1, 1}, 0},
			{{2, 2, 2}, 1},
			{{3, 3, 3}, 2}
	};
	TerminalSubset const full = TerminalSubset::create_full(terminals);
	TerminalSubset const empty = TerminalSubset::create_empty(terminals);
	TerminalSubset const singleton_0 = TerminalSubset::create_singleton(terminals.at(0), terminals);
	TerminalSubset const singleton_1 = TerminalSubset::create_singleton(terminals.at(1), terminals);
	TerminalSubset const singleton_2 = TerminalSubset::create_singleton(terminals.at(2), terminals);
};

BOOST_FIXTURE_TEST_CASE(TestTerminalSubset_get_index, TerminalSubsetFixture)
{
	BOOST_TEST(0 == empty.get_index());
	BOOST_TEST(7 == full.get_index());
	BOOST_TEST(1 == singleton_0.get_index());
	BOOST_TEST(2 == singleton_1.get_index());
	BOOST_TEST(4 == singleton_2.get_index());
}

BOOST_FIXTURE_TEST_CASE(TestTerminalSubset_contains, TerminalSubsetFixture)
{
	BOOST_TEST(not empty.contains(full));
	BOOST_TEST(not empty.contains(singleton_0));
	BOOST_TEST(not empty.contains(singleton_1));
	BOOST_TEST(not empty.contains(singleton_2));
	BOOST_TEST(empty.contains(empty));
	BOOST_TEST(singleton_0.contains(singleton_0));
	BOOST_TEST(singleton_1.contains(singleton_1));
	BOOST_TEST(singleton_2.contains(singleton_2));
	BOOST_TEST(not singleton_1.contains(full));
	BOOST_TEST(full.contains(singleton_0));
	BOOST_TEST(full.contains(singleton_1));
	BOOST_TEST(full.contains(singleton_2));
}

BOOST_FIXTURE_TEST_CASE(TestTerminalSubset_plus, TerminalSubsetFixture)
{
	BOOST_CHECK(singleton_0 == TerminalSubset(empty).plus(singleton_0));
	BOOST_CHECK(full == TerminalSubset(full).plus(singleton_0));
	BOOST_CHECK(full == TerminalSubset(singleton_0).plus(full));
}
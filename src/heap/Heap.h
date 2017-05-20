#ifndef CHIP_DESIGN_HEAP_H
#define CHIP_DESIGN_HEAP_H

#include <set>
#include <tuple>
#include <functional>
#include <assert.h>

namespace heap {

template<typename KeyType, typename DataType>
class Heap
{
private:
	struct DataEntry
	{
		KeyType key;
		DataType data;
	};

public:
	Heap(std::function<bool(DataType const &, DataType const &)> const &data_compare_function) :
			compare_function([data_compare_function](DataEntry const &lhs, DataEntry const &rhs) -> bool {
				if (lhs.key < rhs.key) {
					return true;
				} else if (lhs.key > rhs.key) {
					return false;
				} else {
					return data_compare_function(lhs.data, rhs.data);
				}
			}),
			data(compare_function)
	{}

	virtual void insert(KeyType const &key, DataType const &element)
	{
		data.insert({key, element});
	};

	virtual void key_decreased(KeyType const &old_key, DataType const &element, KeyType const &new_key)
	{
		auto const num_erased = data.erase({old_key, element});
		assert(num_erased != 0);
		data.insert({new_key, element});
	};

	virtual bool contains(KeyType const &key, DataType const &element) const
	{
		return static_cast<bool>(data.count({key, element}));
	}

	virtual DataType pop_minimum()
	{
		assert(not data.empty());
		DataType const minimum_element = data.begin()->data;
		data.erase(data.begin());
		return minimum_element;
	};

private:
	std::function<bool(DataEntry const &, DataEntry const &)> compare_function;
	std::set<DataEntry, std::function<bool(DataEntry const &, DataEntry const &)> > data;
};

}

#endif //CHIP_DESIGN_HEAP_H

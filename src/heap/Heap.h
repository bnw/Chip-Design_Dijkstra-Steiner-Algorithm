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
		bool operator<(DataEntry const &rhs) const
		{
			// This is faster than std::tie
			if (key < rhs.key) {
				return true;
			} else if (key > rhs.key) {
				return false;
			} else {
				return data < rhs.data;
			}
		}

		KeyType key;
		DataType data;
	};

public:
	Heap() :
			data()
	{}

	virtual void insert(KeyType const &key, DataType const &element)
	{
		data.insert({key, element});
	};

	virtual void erase_if_exists(KeyType const &key, DataType const &element)
	{
		data.erase({key, element});
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
	std::set<DataEntry> data;
};

}

#endif //CHIP_DESIGN_HEAP_H

#pragma once
#ifndef BINARY_HEAP
#define BINARY_HEAP

#include <vector>

template<typename T>
class binary_heap
{
private:
	std::vector<T> values;
public:

	explicit binary_heap() {};

	explicit binary_heap(std::vector<T>& in_set) {
		values = in_set;
		build();
	}

	binary_heap(std::vector<T>&& in_set) {
		values = std::move(in_set);
		build();
	}
	void insert(T value) {
		values.resize(values.size() + 1);
		values[values.size() - 1] = value;
		sift_up(values.size() - 1);
	};
	T extract_min() {

		T ans = values[0];
		std::swap(values[0], values[size() - 1]);
		values.pop_back();
		sift_down(0);
		return ans;
	};

	inline size_t size() const {
		return values.size();
	};
private:
	void sift_down(size_t node) {
		while (2 * node + 1 < size()) {

			size_t left = 2 * node + 1, right = 2 * node + 2, j = left;
			if (right < size() && values[right] < values[left]) {
				j = right;
			}
			if (values[node] <= values[j]) {
				break;
			}
			std::swap(values[node], values[j]);
			node = j;

		}
	}
	void sift_up(size_t node) {

		while (values[node] < values[(node - 1) / 2]) {

			std::swap(values[node], values[(node - 1) / 2]);
			node = (node - 1) / 2;

		}
	};
	void build() {

		for (auto node = size() / 2; node >= 0; node--) {
			sift_down(node);
		}

	};
};

#endif // !BINARY_HEAP
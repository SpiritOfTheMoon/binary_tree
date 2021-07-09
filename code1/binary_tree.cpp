#include "binary_tree.h"
#include<vector>

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>& in_set) {

	tree.resize(3 * in_set.size());
	v = in_set;
	tree_build(0, 0, in_set.size());

}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>const&& in_set) {

	tree.resize(3 * in_set.size());
	v = std::move(in_set);
	tree_build(0, 0, in_set.size());

}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>& in_set, std::function<T(T first, T second)>const&& _monoid) {

	tree.resize(3 * in_set.size());
	v = in_set;
	monoid = std::move(_monoid);
	tree_build(0, 0, in_set.size());

}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>const&& in_set, std::function<T(T first, T second)>const&& _monoid) {

	tree.resize(3 * in_set.size() + 2);
	v = std::move(in_set);
	monoid = std::move(_monoid);
	tree_build(0, 0, in_set.size());

}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>& in_set, std::function<T(T first, T second)>const& _monoid) {

	size_t const size_binary_tree = in_set.size();
	tree.resize(3 * size_binary_tree);
	v = in_set;
	monoid = _monoid;
	tree_build(0, 0, size_binary_tree);

}


#include "binary_tree.h"
#include<vector>
#include<stdexcept>

template<typename T, T null_t>
T binary_tree<T, null_t>::tree_query(
	size_t node,
	size_t left,
	size_t right,
	size_t left_user_query, // полуинтервал
	size_t right_user_query // полуинтервал
) {
	if (left >= left_user_query && right <= right_user_query) {

		return tree[node];

	}
	if (right_user_query <= left || left_user_query >= right) {

		return null_t;

	}
	size_t middle = (left + right) / 2;

	T left_result = binary_tree::tree_query(2 * node + 1, left, middle, left_user_query, right_user_query);
	T right_result = binary_tree::tree_query(2 * node + 2, middle, right, left_user_query, right_user_query);

	return monoid(left_result, right_result);

}
template<typename T, T null_t>
void binary_tree<T, null_t>::tree_update(
	size_t node,
	size_t left,
	size_t right,
	size_t position,
	T value
) {
	if (left + 1 == right)
		tree[node] = std::move(value);
	else {
		size_t middle = (left + right) / 2;
		if (position < middle)
			binary_tree::tree_update(2 * node + 1, left, middle, position, value);
		else
			binary_tree::tree_update(2 * node + 2, middle, right, position, value);
		tree[node] = monoid(tree[2 * node + 1], tree[2 * node + 2]);
	}
}

template<typename T, T null_t>
void binary_tree<T, null_t>::tree_build(size_t node, size_t left, size_t right) {
	if (right == left + 1) {
		tree[node] = v[left];
	}
	else {
		size_t middle = (left + right) / 2;
		binary_tree::tree_build(2 * node + 1, left, middle);
		binary_tree::tree_build(2 * node + 2, middle, right);
		tree[node] = monoid(tree[2 * node + 1], tree[2 * node + 2]);
	}
}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>& in_set) {

	monoid = [](T const first, T const second) -> T {
		return first + second;
	};
	tree.resize(3 * in_set.size());
	v = in_set;
	binary_tree::tree_build(0, 0, in_set.size());



}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>const&& in_set) {

	monoid = [](T const first, T const second) -> T {
		return first + second;
	};
	tree.resize(3 * in_set.size());
	v = std::move(in_set);
	binary_tree::tree_build(0, 0, in_set.size());

}


template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>& in_set, std::function<T(T first, T second)>const&& _monoid) {

	tree.resize(3 * in_set.size());
	v = in_set;
	monoid = std::move(_monoid);
	binary_tree::tree_build(0, 0, in_set.size());

}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>const&& in_set, std::function<T(T first, T second)>const&& _monoid) {

	tree.resize(3 * in_set.size() + 2);
	v = std::move(in_set);
	monoid = std::move(_monoid);
	binary_tree::tree_build(0, 0, in_set.size());

}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>& in_set, std::function<T(T first, T second)>const& _monoid) {

	size_t const size_binary_tree = in_set.size();
	tree.resize(3 * size_binary_tree);
	v = in_set;
	monoid = _monoid;
	binary_tree::tree_build(0, 0, size_binary_tree);

}

template<typename T, T null_t>
binary_tree<T, null_t>::binary_tree(std::vector<T>const&& in_set, std::function<T(T first, T second)>const& _monoid) {

	size_t const size_binary_tree = in_set.size();
	tree.resize(3 * size_binary_tree);
	v = std::move(in_set);
	monoid = _monoid;
	binary_tree::tree_build(0, 0, size_binary_tree);

}

template<typename T, T null_t>
T binary_tree<T, null_t>::query(
	size_t left_query,
	size_t right_query
) {
	if (left_query > size() || right_query < 0 || left_query < 0 || right_query > size()) {
		throw std::logic_error("exception! Left or right reference binary tree limit exceeded");
	}
	T ans = tree_query(0, 0, size(), left_query, right_query);
	return ans;

}

template<typename T, T null_t>
void binary_tree<T, null_t>::update(size_t position, T value) {
	if (position > size() - 1) {
		throw std::logic_error("exception! Left or right reference binary tree limit exceeded");
	}
	tree_update(0, 0, size(), position, value);
}

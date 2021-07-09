#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include<vector>
#include<functional>

#pragma once
template <typename T, T null_t>
class binary_tree
{
public:

	explicit binary_tree(std::vector<T>& in_set);
	explicit binary_tree(std::vector<T>const&& in_set);

	binary_tree(std::vector<T>& in_set, std::function<T(T first, T second)>const&& _monoid);
	binary_tree(std::vector<T>const&& in_set, std::function<T(T first, T second)>const&& _monoid);
	binary_tree(std::vector<T>& in_set, std::function<T(T first, T second)>const& _monoid);
	binary_tree(std::vector<T>const&& in_set, std::function<T(T first, T second)>const& _monoid);
	[[nodiscard]] T query(
		size_t left_query,
		size_t right_query
	);

	inline size_t size() const;
	void update(size_t position, T value);


private:

	std::vector<T> v;
	std::vector<T> tree;
	std::function<T(T first, T second)> monoid = [](T const first, T const second) -> T {
		return first + second;
	};

	void tree_build(size_t node, size_t left, size_t right);

	T tree_query(
		size_t node,
		size_t left,
		size_t right,
		size_t left_user_query, // полуинтервал
		size_t right_user_query // полуинтервал
	);

	void tree_update(
		size_t node,
		size_t left,
		size_t right,
		size_t position,
		T value
	);
};
#endif
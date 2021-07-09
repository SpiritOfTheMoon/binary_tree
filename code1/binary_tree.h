#pragma once

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include<vector>
#include<functional>

// class template binary tree, null_t - identity element over operation
template <typename T, T null_t>
class binary_tree
{

private:
	//values into leafs
	std::vector<T> v;
	//node of the binary tree
	std::vector<T> tree;
	//operation is monoid (operation is associative and have identity element (null_t))
	// default operation - '+'
	std::function<T(T first, T second)> monoid;

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

	inline size_t size() const {
		return v.size();
	};
	void update(size_t position, T value);


private:

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
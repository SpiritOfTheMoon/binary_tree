#pragma once

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include<vector>
#include<functional>
#include <stdexcept>

// class template binary tree, null_t - identity element over operation
template <typename T>
class binary_tree
{

private:
	//values into leafs
	std::vector<T> v;
	//node of the binary tree
	std::vector<T> tree;
	//operation is monoid (operation is associative and have identity element)
	std::function<T(T first, T second)> _operator;
	// identity element for _operator
	T identity_element;

public:

	T& operator [](size_t i) {
		return v[i];
	}

	binary_tree(
		std::vector<T>& in_set,
		std::function<T(T first, T second)>&& user_operator,
		T user_identity_element
	) {

		init_tree(in_set.size());
		identity_element = user_identity_element;
		v = in_set;
		_operator = std::move(user_operator);
		binary_tree::tree_build(0, 0, in_set.size());

	};
	binary_tree(
		std::vector<T>&& in_set,
		std::function<T(T first, T second)>&& user_operator,
		T user_identity_element
	) {

		identity_element = user_identity_element;
		init_tree(in_set.size());
		v = std::move(in_set);
		_operator = std::move(user_operator);
		binary_tree::tree_build(0, 0, in_set.size());

	};

	binary_tree(
		std::vector<T>& in_set,
		std::function<T(T first, T second)>const& user_operator,
		T user_identity_element
	) {

		identity_element = user_identity_element;
		init_tree(in_set.size());
		v = in_set;
		_operator = user_operator;
		binary_tree::tree_build(0, 0, in_set.size());

	};
	binary_tree(
		std::vector<T>const&& in_set,
		std::function<T(T first, T second)>const& user_operator,
		T user_identity_element
	) {

		identity_element = user_identity_element;
		init_tree(in_set.size());
		v = std::move(in_set);
		_operator = user_operator;
		binary_tree::tree_build(0, 0, in_set.size());

	};

	[[nodiscard]] T query(
		size_t left_query,
		size_t right_query
	) {
		if (left_query > size() || right_query < 0 || left_query < 0 || right_query > size()) {
			throw std::logic_error("exception! Left or right reference binary tree limit exceeded");
		}
		T ans = tree_query(0, 0, size(), left_query, right_query);
		return ans;

	};

	inline size_t size() const {
		return v.size();
	};
	void update(size_t position, T value) {
		if (position > size() - 1) {
			throw std::logic_error("exception! Left or right reference binary tree limit exceeded");
		}
		tree_update(0, 0, size(), position, value);
	};


private:


	void init_tree(size_t in_size) {
		size_t size = 1;
		while (size < in_size) {
			size <<= 1;
		}
		tree.resize(2 * size - 1);
	}

	void tree_build(size_t node, size_t left, size_t right) {
		if (right == left + 1) {
			tree[node] = v[left];
		}
		else {
			size_t middle = (left + right) / 2;
			binary_tree::tree_build(2 * node + 1, left, middle);
			binary_tree::tree_build(2 * node + 2, middle, right);
			tree[node] = _operator(tree[2 * node + 1], tree[2 * node + 2]);
		}
	};
	T tree_query(
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

			return identity_element;

		}
		size_t middle = (left + right) / 2;

		T left_result = binary_tree::tree_query(2 * node + 1, left, middle, left_user_query, right_user_query);
		T right_result = binary_tree::tree_query(2 * node + 2, middle, right, left_user_query, right_user_query);

		return _operator(left_result, right_result);

	};

	void tree_update(
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
			tree[node] = _operator(tree[2 * node + 1], tree[2 * node + 2]);
		}
	};
};
#endif
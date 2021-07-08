#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include<functional>

using namespace std;

template <typename T, T null_t>
class binary_tree
{
public:

	explicit binary_tree(vector<T>& in_set) {

		tree.resize(3 * in_set.size());
		v = in_set;
		tree_build(0, 0, in_set.size());

	}
	explicit binary_tree(vector<T>const&& in_set) {

		tree.resize(3 * in_set.size());
		v = std::move(in_set);
		tree_build(0, 0, in_set.size());

	}

	binary_tree(vector<T>& in_set, function<T(T first, T second)>const&& _monoid) {

		tree.resize(3 * in_set.size());
		v = in_set;
		monoid = std::move(_monoid);
		tree_build(0, 0, in_set.size());

	}
	binary_tree(vector<T>const&& in_set, function<T(T first, T second)>const&& _monoid) {

		tree.resize(3 * in_set.size() + 2);
		v = std::move(in_set);
		monoid = std::move(_monoid);
		tree_build(0, 0, in_set.size());

	}
	binary_tree(vector<T>& in_set, function<T(T first, T second)>const& _monoid) {

		size_t const size_binary_tree = in_set.size();
		tree.resize(3 * size_binary_tree);
		v = in_set;
		monoid = _monoid;
		tree_build(0, 0, size_binary_tree);

	}
	binary_tree(vector<T>const&& in_set, function<T(T first, T second)>const& _monoid) {

		size_t const size_binary_tree = in_set.size();
		tree.resize(3 * size_binary_tree);
		v = std::move(in_set);
		monoid = _monoid;
		tree_build(0, 0, size_binary_tree);

	}
	[[nodiscard]] T query(
		size_t left_query,
		size_t right_query
	) {
		;
		if (left_query > size() || right_query < 0 || left_query < 0 || right_query > size()) {
			throw logic_error("exception! Left or right reference binary tree limit exceeded");
		}
		T ans = tree_query(0, 0, size(), left_query, right_query);
		return ans;

	}

	inline size_t size() const {
		return v.size();
	}
	void update(size_t position, T value) {
		if (position > size() - 1) {
			throw logic_error("exception! Left or right reference binary tree limit exceeded");
		}
		tree_update(0, 0, size(), position, value);
	}


private:

	vector<T> v;
	vector<T> tree;
	function<T(T first, T second)> monoid = [](T const first = null_t, T const second = null_t) -> T {
		if (first == null_t) {
			if (second == null_t) {
				return null_t;
			}
			else {
				return second;
			}
		}
		else {
			if (second == null_t) {
				return first;
			}
			else {
				return first + second;
			}
		}
		return first + second;
	};

	void tree_build(size_t node, size_t left, size_t right) {
		if (right == left + 1) {
			tree[node] = v[left];
		}
		else {
			size_t middle = (left + right) / 2;
			tree_build(2 * node + 1, left, middle);
			tree_build(2 * node + 2, middle, right);
			tree[node] = monoid(tree[2 * node + 1], tree[2 * node + 2]);
		}
	}

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

			return null_t;

		}
		size_t middle = (left + right) / 2;

		T left_result = tree_query(2 * node + 1, left, middle, left_user_query, right_user_query);
		T right_result = tree_query(2 * node + 2, middle, right, left_user_query, right_user_query);

		return monoid(left_result, right_result);

	}

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
				tree_update(2 * node + 1, left, middle, position, value);
			else
				tree_update(2 * node + 2, middle, right, position, value);
			tree[node] = monoid(tree[2 * node + 1], tree[2 * node + 2]);
		}
	}
};

int main()
{

	vector<int> v = { 1, 2, 3, 4, 5 };
	binary_tree<int, 0> new_b = binary_tree<int, 0>(std::move(v));
	cout << new_b.query(1, );
	return 0;

}
/*
1
9
1 2 2 2 5 4 5 3
1 2 3 4 4 2 4 8


*/
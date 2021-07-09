#include <iostream>
#include"binary_tree.cpp"

using namespace std;

int main()
{

	vector<int> v = { 1, 2, 3, 4, 5 };
	binary_tree<int> new_b = binary_tree<int>(v, [](int a, int b) {return a + b; }, 0);
	cout << new_b[0];
	cout << new_b.query(1, 3);
	return 0;

}
/*
1
9
1 2 2 2 5 4 5 3
1 2 3 4 4 2 4 8


*/
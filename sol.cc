#include<iostream>
#include<vector>

using namespace std;

int main() {
	vector<int> init = {1, 2, 3, 4, 5};
	for(int i = 1; i < 5; ++i) {
		do {
			for(vector<int>::iterator *it = init.begin(); it < init.begin() + i; ++it) {
				cout << *it << " ";
			}
			cout << endl;
		} while (next_permutation(init.begin(), init.begin()+i);
	}
	return 0;
}
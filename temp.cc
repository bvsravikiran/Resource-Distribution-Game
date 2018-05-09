#include<iostream>
#include<vector>
using namespace std;
int permute_again(vector<int> &arr) {
	int ct = 0;
	cout << "permute_again got the following array: " << endl;

	for (int i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;

	cout << "Generating all the sub permutations with 3 elements of the received permutation" << endl;	

	do {
		for (int i = 0; i < 2; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;
		ct++;
	} while(next_permutation(arr.begin(), arr.begin()+2));

	return ct;
}



int main() {
	vector<int> arr;
	for(int i = 0; i < 3; ++i) {
		arr.push_back(i+1);
	}
	int ct = 0;
	do {
		ct += permute_again(arr);
		cout << "ct now: " << ct << endl;
	} while(next_permutation(arr.begin(), arr.end()));
	cout << endl << "counter = " << ct << endl;
	return 0;
}
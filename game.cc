#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<unordered_map>

using namespace std;

class Game {
private:
	int agents;
	vector<int> init;
	vector<vector<int> > perm;
	vector<int> res;
	int total_res;
	vector<int> util;
public:
	Game(int n) {
		agents = n;
		init_();
		get_resources();
	}

	void get_resources() {
		res.reserve(agents+1);
		res[0] = 0;
		for(int i = 1; i <= agents; ++i) {
			cin >> res[i];
			total_res += res[i];
		}
	}

	void init_() {
		for (int i = 0; i < agents; ++i) {
			init.push_back(i+1);
		}
		permute();
	}

	void permute() {
		sort(init.begin(), init.end());
		do {
			perm.push_back(init);
		} while(next_permutation(init.begin(), init.end()));
	}

	unsigned long factorial(unsigned int n) { return (n == 0) ? 1 : n * factorial(n-1); }

	bool is_greater(int n) { return (n > 50) ? true : false; }

	void util_() {
		util.reserve(agents);
		for(int i = 0; i < agents; ++i) {
			cout << "utility for the agent " << i + 1 << " is " << endl << shapley(i + 1) << endl;
		}
	}

	double shapley(int n) {
		cout << "Entered the shapley function " << endl;
		int sum = 0;
		double value = 0;
		int counter = 0;
		vector<int> arr(agents, 0);
		for (int i = 0; i < perm.size(); ++i) {
			for(int j = 0; j < perm[i].size(); ++j) {
				if (perm[i][j] == n) {

					cout << endl << "The permutation is: ";
					for(int k_i = 0; k_i < perm[i].size(); ++k_i) {
						cout << perm[i][k_i] << " ";
					}
					cout << endl;

					
					cout << endl << "Agent joined at position " << j << endl;
					if (!is_greater(sum)) {
						cout << "The sum of coalitions excluding the agent is " << sum << " and it doesnot have the majority." << endl;
						if (is_greater(sum + res[n])) {
							cout << "But when the agent is included, the sum is " << sum << " and it has the majority." << endl;
							double temp = (factorial(counter) * factorial(agents - counter - 1) * 100);
							cout << "The value at this point is " << temp << endl;
							// value += temp;
							cout << "The arr[j] was " << arr[j] << endl;
							arr[j] += temp;
							cout << "The arr[j] was " << arr[j] << endl;
						}
					}
					sum = 0;
					counter = 0;
					break;
				} else {
					sum += res[perm[i][j]];
					counter++;
				}
			}
		}
		for (int x = 0; x < arr.size(); ++x) {
			if(arr[x] > 0) {
				cout << "------------------------------------" << endl;
				cout << endl << "The agent joined at " << x << " and the factorial is " << (agents - x - 1) << " and the sum of the payoffs for the agent at that position is " << arr[x] << endl;
				arr[x] = arr[x] / factorial(agents - x - 1);
				value += arr[x];
				cout << "------------------------------------" << endl;
			}
		}
		return value / factorial(agents);
	}

};
int main() {
	int n;
	cin >> n;
	Game *g = new Game(n);
	g->util_();
	return 0;
}
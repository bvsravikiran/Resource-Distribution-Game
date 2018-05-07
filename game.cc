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
			cout << "utility for the agent " << i + 1 << " is " << shapley(i + 1) << endl;
		}
	}

	double shapley(int n) {
		int sum = 0;
		double value = 0;
		int counter = 0;
		for (int i = 0; i < perm.size(); ++i) {
			for(int j = 0; j < perm[i].size(); ++j) {
				if (perm[i][j] == n) {
					if (!is_greater(sum)) {
						if (is_greater(sum + res[n])) {
							double temp = (factorial(counter) * factorial(agents - counter - 1) * 100);
							value += temp;
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
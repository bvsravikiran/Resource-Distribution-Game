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
	long fact;
public:
	Game(int n) {
		agents = n;
		init_();
		get_resources();
		cout << "Hello!" << endl;
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

	unsigned long factorial(unsigned int n) {
		if (n == 0) return 1;
		return n * factorial(n-1);
	}

	bool is_greater(int n) {
		return ((n/total_res)*100 > 50) ? true : false;
	}

	void util_() {
		fact = factorial(agents);
		//cout << "util_ function called" << endl;
		util.reserve(agents);
		for(int i = 0; i < 1; ++i) {
			//util[i] = shapley(i+1);
			cout << shapley(i+1) << endl;
		}
		cout << "Success!" << endl;
	}

	double shapley(int n) {
		//cout << "shapley function called for agent " << n << endl;
		int sum = 0;
		double value = 0;
		int counter = 0;
		for (int i = 0; i < perm.size(); ++i) {
			cout << "For permutation ";
			for (int k = 0; k < perm[i].size(); ++k) {
				cout << perm[i][k] << " ";
			}
			cout << endl;
			for(int j = 0; j < perm[i].size(); ++j) {
				if (perm[i][j] == n) {
					if (!is_greater(sum)) {
						if (is_greater(sum + res[n])) {
							cout << counter << "! " << agents - counter - 1 << "! " << "(100 - 0)";
							double temp = (factorial(counter) * factorial(agents - counter - 1) * 100);
							cout << temp << endl;
							value += temp;
						}
					}
					sum = 0;
					counter = 0;
					break;
				} else {
					//cout << "agent " << n << " not yet encountered" << endl;
					sum += res[perm[i][j]];
					//cout << "Sum: " << sum;
					counter++;
				}
			}
		}
		return value /factorial(fact);
	}

};
int main() {
	int n;
	cin >> n;
	Game *g = new Game(n);
	g->util_();
	return 0;
}
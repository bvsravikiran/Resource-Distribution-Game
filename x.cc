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
	vector<double> shapley_util;
	vector<double> max_util;

public:	
	Game(int n) {
		agents = n;
		init_();
		get_resources();
	}
	
	void get_resources() {
		res.reserve(agents+1);
		res[0] = 0;
		total_res = 0;
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

	bool is_greater(int n) { return (((n*1.0/(total_res*1.0)) *100.0) > 50) ? true : false; }

	void util_() {
		shapley_util.reserve(agents);
		for(int i = 0; i < agents; ++i) {
			shapley_util.push_back(shapley(i+1));
		}
		for(int i = 0; i < shapley_util.size(); ++i) {
			cout << shapley_util[i] << endl;
		}
	}

	double shapley(int n) {
		int sum = 0;
		double value = 0;
		int counter = 0;
		vector<double> pos(agents, 0);
		for (int i = 0; i < perm.size(); ++i) {
			for(int j = 0; j < perm[i].size(); ++j) {
				if (perm[i][j] == n) {
					if (!is_greater(sum)) {
						if (is_greater(sum + res[n])) {
							pos[j] += (factorial(counter) * factorial(agents - counter - 1) * 100);
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
		for (int x = 0; x < pos.size(); ++x) {
			if(pos[x] > 0) {
				pos[x] = pos[x] / (factorial(agents - x - 1) * factorial (x));
				value += pos[x];
			}
		}
		return value / factorial(agents);
	}


	double shapley(int p, vector<int> &arr) {

		int sum = 0;
		double value = 0;
		int counter = 0;

		vector<int> pos(agents, 0);


		for(int i = 0; i < arr.size(); ++i) {
			if(arr[i] == p) {
				if(!is_greater(sum)) {
					if(!is_greater(sum+res[arr[i]])) {
						double temp = (factorial(counter) * factorial(arr.size() - counter - 1) * 100);
						pos[arr[i]] += temp;
					}
				}
				sum = 0;
				counter = 0;
				break;
			} else {
				sum += res[arr[i]];
				counter++;
			}
		}
		for(int x = 0; x < pos.size(); ++x) {
			if(pos[x] > 0) {
				pos[x] = pos[x] / (factorial(arr.size() - x - 1) * factorial (x));
				value += pos[x];
			}
		}

		return value / factorial(arr.size());
	}


	void core_(vector<int> &arr) {
		for(int i = 0; i < arr.size(); ++i) {
			// double value = shapley(arr[i], arr);
			// if(value > max_util[arr[i]]) max_util[arr[i]] = value;
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void stable_() {
		max_util.reserve(agents);
		for(int p = 0; p < max_util.size(); ++p) {
			max_util[p] = 0;
		}

		for (int i = 0; i < perm.size(); ++i) {
			for (int j = 0; j < perm[i].size(); ++j) {
				do {
					vector<int> arr;
					for(int x = 0; x <= j; ++x) {
						arr.push_back(perm[i][x]);
					}
					core_(arr);
				} while(next_permutation(perm[i].begin(), perm[i].begin()+j+1));
			}
		}
	}

};
int main() {
	int n;
	cin >> n;
	Game *g = new Game(n);
	g->util_();
	g->stable_();
	return 0;
}
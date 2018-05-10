#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<unordered_map>

using namespace std;


class Core {
private:
	int agents;
	vector<vector<int> > perm;
	vector<int> max_util;
	int total_res;
	vector<int> res;
public:
	Core(int n, vector<vector<int> > &v, int t, vector<int> &r) {
		agents = n;
		total_res = t;
		perm = v;
		res = r;
		max_util.reserve(n);
		for(int i = 0; i < max_util.size(); ++i) {
			max_util[i] = 0;
		}
		sub_perm();
	}

	void sub_perm() { // this function generates all the sub permutations.
		for (int i = 0; i < perm.size(); ++i) {
			vector<int> v = perm[i];
			for(int xx = 0; xx < v.size(); ++xx) {
				do {
					vector<int> sub;
					for(int j = 0; j <= xx; ++j) {
						sub.push_back(v[j]);
					}
					util_(sub);
				} while(next_permutation(v.begin(), v.begin() + xx + 1));
			}
		}
	}

	bool is_greater(int n) { return (((n*1.0/(total_res*1.0)) *100.0) > 50) ? true : false; }

	unsigned long factorial(unsigned int n) { return (n == 0) ? 1 : n * factorial(n-1); }
	
	void util_(vector<int> &v) {
		for(int i = 0; i < v.size(); ++i) {
			int agent = v[i];
			//calculate shapley value for the agent.
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





	//for all the sub permutations, calculate the shapley's value
};




























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
	
	int get_total_res() {
		return total_res;
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

	vector<vector<int> > get_perm() {
		return perm;
	}

	vector<int> resources_() {
		return res;
	}




};



int main() {
	int n;
	cin >> n;
	Game *g = new Game(n);
	g->util_();
	vector<vector<int> > perm = g->get_perm();
	int total_res = g->get_total_res();
	vector<int> res = g->resources_();
	Core *c = new Core(n, perm, total_res, res);
	return 0;
}
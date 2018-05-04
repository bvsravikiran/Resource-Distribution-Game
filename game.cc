#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

class solution {
private:
	vector<string> perm;
	unordered_map<char, long> res;
	string s;
	long n;
	long total_res;
	vector<long> util;

public:
	
	solution(long num) {
		n = num;
		perm.reserve(n);
		util.reserve(n);
		sequence();
	}

	long calc_fact(long n) {
		/*
		Calculates the factorial of a number
		*/
		if (n == 0) return 1;
		long ans = 1;
		for (long i = 1; i <= n; ++i) {
			ans = ans * i;
		}
		return ans;
	}

	void sequence() {
		/*
		Generates string sequence for all the n agents.
		*/
		int r;
		for (long i = 0; i < n; ++i) {
			cin >> r;
			total_res += r;
			char c = (char) (97 + i);
			res[c] = r;
			s += c;
		}
	}

	void permute() {
		backtrack(s.begin(), 0, s.length() - 1);
	}

	void backtrack(string::iterator it, long l, long r) {
		if (l == r) {
			perm.push_back(s);
		}
		else {
			for(long i = l; i <= r; ++i) {
				swap(*(it+l), *(it+i));
				backtrack(it, l+1, r);
				swap(*(it+l), *(it+i));
			}
		}
	}
	
	bool is_greater(long a) {
		return ((a/total_res)*100 > 50) ? true : false;
	}

	long shapely(string s, char c) {
		long util = 0;
		long set = 0;
		long set_without_agent = 0;
		long set_with_agent = 0;
		for(long i = 0; i < s.length(); ++i) {
			if (s[i] == c) {
				set_with_agent = set_without_agent + res[c];
				if (is_greater(set_without_agent)) {
					return calc_fact(set) * calc_fact(n - set - 1) * (100 - 100);
				}
				else {
					if (is_greater(set_with_agent)) {
						return calc_fact(set) * calc_fact(n - set - 1) * (0 - 100);
					}
					else return calc_fact(set) * calc_fact(n - set - 1) * (0 - 0);
				}
			}
			else {
				set_without_agent += res[s[i]];
				++set;
			}
		}
		cout <<"Error in calculating the shapely's value.. Exiting the program." << endl;
		exit(0);
		return -1;
	}

	vector<long> calc_util() {
		for(long j = 0; j < n; ++j) {
			for(long i = 0; i < perm.size(); ++i) {
				util[j] += shapely(perm[i], (char)(97 + j));
			}
			util[j] /= calc_fact(n);
		}
		return util;
	}

};

int main() {

	long n, r;
	cin >> n;
	solution *obj = new solution(n);
	obj->permute();
	//Now the perm vector should contain all the permutaions of the sequence.
	// vector<long> util = obj->calc_util();
	// cout << "The final utilities for the agents are as follows: " << endl;
	// for(long i = 0; i < n; i++) {
	// 	cout << "Agent " << (char) (97 + i) << ": " << util[i] << endl;
	// }
	return 0;

}
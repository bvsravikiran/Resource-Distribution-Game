#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class game{
private:	
	int agents; // total no.of agents
	string ids; // sequence of agents
	unordered_map<char, int> res; // resources with each agent
	vector<string> perm; // permutations of all the coalitions
	vector<int> util; // final utilities for each agent
	long total_resources = 0;

	static void generate_agents() {
		for (int i = 0; i < n; ++i) {
			ids = ids + (char) (97 + i);
		}
	}
	
	static void get_resources() {
		cout << "Enter the resources with each agent" << endl;
		for (int i = 0; i < agents; ++i) {
			int resource;
			cin >> resource; // gets the resources for an agent
			res[ids[i]] = resource; // maps agent with their resources
			total_resources += resource; // update the total resources
		}	
	}

	static long long calculate_factorial(unsigned int n) {
		if (n == 0) return 1;
		return calculate_factorial(n) * calculate_factorial(n - 1);
	}

	static void permute() {
		string sequence = ids;
		backtrack(sequence.begin(), 0, sequence.length() - 1);
	}

	static void backtrack(string::iterator it, int l, int r) {
		if (l == r) {
			perm.push_back(s);
		}
		else {
			for(int i = l; i <= r; ++i) {
				swap(*(it+l), *(it+i));
				backtrack(it, l+1, r);
				swap(*(it+l), *(it+i));
			}
		}
	}

	static bool is_greater(int a) {
		return ((a / total) * 100 > 50) ? true : false;
	}

	static bool check_flag() {
		//length of sequence should be 26
		if (ids.length() != agents) {
			cout << endl << "Error generating ids.." << endl;
			return false;
		}
		if (perm.size() != calculate_factorial(agents)) {
			cout << endl << "Error generating permutations.." << endl;
			return false;
		}

	}

public:
	game(int num_agents) {
		agents = num_agents;
		util.reserve(agents);
		generate_agents();
		get_resources();
		permute();
		if(!check_flag()) {
			cout << "Checks not passed. Exiting the game." << endl;
			cout << endl << "Bye!" << endl;
			exit(0);
		} else {
			cout << "All checks passed. OK." << endl;
		}
	}



};

int main() {
	cout << "Welcome to Resource Distribution Game!" << endl;
	cout << "Enter the number of agents: ";
	unsigned int n;
	cin >> n;
	if (n < 2) {
		cout << "At least 2 agents are required to play the game.." << endl;
		cout << endl << "Bye!";
		return 0;
	}
	game *g = new game(n);
	cout << endl << "Bye!";
	return 0;
}
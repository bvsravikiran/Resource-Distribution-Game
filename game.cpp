#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Game {
private:
    unsigned int agents;
    vector<unsigned int> init;
    vector<vector<unsigned int> > perm;
    vector<unsigned int> res;
    unsigned int total_res;
    vector<double> shapley_util;
    vector<double> max_util;

public:

    Game(unsigned int n) {
        agents = n;
        init_();
        get_resources();
    }

    void init_() {
        for (unsigned int i = 0; i < agents; ++i) {
            init.push_back(i + 1);
        }
        permute();
    }

    void permute() {
        sort(init.begin(), init.end());
        do {
            perm.push_back(init);
        } while (next_permutation(init.begin(), init.end()));
    }

    void get_resources() {
        res.reserve(agents + 1);
        res[0] = 0;
        total_res = 0;
        for (unsigned int i = 1; i <= agents; ++i) {
            cin >> res[i];
            total_res += res[i];
        }
    }

    void util_() {
        shapley_util.reserve(agents);
        for (unsigned int i = 0; i < agents; ++i) {
            shapley_util.push_back(shapley(i + 1));
        }
        for (unsigned int i = 0; i < shapley_util.size(); ++i) {
            cout << "Payoff for agent " << i+1 << ": $" << shapley_util[i] * 100 << endl;
        }
    }

    double shapley(unsigned int n) {
        unsigned int sum = 0;
        double value = 0;
        unsigned int counter = 0;
        vector<double> pos(agents, 0);
        for (unsigned int i = 0; i < perm.size(); ++i) {
            for (unsigned int j = 0; j < perm[i].size(); ++j) {
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
        for (unsigned int x = 0; x < pos.size(); ++x) {
            if (pos[x] > 0) {
                pos[x] = pos[x] / (factorial(agents - x - 1) * factorial(x));
                value += pos[x];
            }
        }
        return value / factorial(agents);
    }

    unsigned long factorial(unsigned int n) { return (n == 0) ? 1 : n * factorial(n - 1); }

    bool is_greater(unsigned int n) { return ((n * 1.0 / (total_res * 1.0)) * 100.0) > 50; }

};


int main() {
    unsigned int n;
    cin >> n;
    if (n < 2) {
        cout << "At least 2 agents are required to play the Game." << endl;
        return 0;
    }
    Game *g = new Game(n);
    g->util_();
    return 0;
}
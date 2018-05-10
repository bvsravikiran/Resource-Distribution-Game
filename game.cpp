/*
Author: Ravi Kiran Boggavarapu
Student ID: 1001541261
Email: ravi.boggavarapu@mavs.uta.edu

Description: This program calculates the 'fair' distribution of the proceedings to a grand coalition of rational agents.
*/

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
        agents = n; // initializes the total number of agents 
        init_();
        get_resources();
    }

    void init_() { // assigns each agent an id 
        for (unsigned int i = 0; i < agents; ++i) {
            init.push_back(i + 1);
        }
        permute();
    }

    void permute() { // computes and stores all the permutations of the agents
        sort(init.begin(), init.end());
        do {
            perm.push_back(init); // stores each of the permutations in a vector
        } while (next_permutation(init.begin(), init.end()));
    }

    void get_resources() { // gets the total number of resources available with each of the agent
        res.reserve(agents + 1);
        res[0] = 0;
        total_res = 0;
        for (unsigned int i = 1; i <= agents; ++i) {
            cin >> res[i];
            total_res += res[i];
        }
    }

    void util_() { // displays the proceedings for each agent
        shapley_util.reserve(agents);
        for (unsigned int i = 0; i < agents; ++i) {
            shapley_util.push_back(shapley(i + 1));
        }
        for (unsigned int i = 0; i < shapley_util.size(); ++i) {
            cout << "Payoff for agent " << i+1 << ": $" << shapley_util[i] * 100 << endl;
        }
    }

    double shapley(unsigned int n) { // calculates the shapley's value for an agent 'n'.
        unsigned int sum = 0;
        double value = 0;
        unsigned int counter = 0;
        vector<double> pos(agents, 0);
        for (unsigned int i = 0; i < perm.size(); ++i) { // over all the permutations
            for (unsigned int j = 0; j < perm[i].size(); ++j) { // in each of the individual permutation
                if (perm[i][j] == n) { // if the current agent is encountered
                    if (!is_greater(sum)) { // if the group that exists before the agent joins does not have the majority
                        if (is_greater(sum + res[n])) { // if including the agent with the group has the majority
                            pos[j] += (factorial(counter) * factorial(agents - counter - 1) * 100); // majority = 100. No majority = 0.
                        }
                    }
                    sum = 0;
                    counter = 0;
                    break; // breaks and continues with next permutation as there is no need to calculate for the agents that joins after the desiredd agent.
                } else { // add all the resources of agents before the current agent.
                    sum += res[perm[i][j]]; 
                    counter++;
                }
            }
        }
        for (unsigned int x = 0; x < pos.size(); ++x) {
            if (pos[x] > 0) {
                pos[x] = pos[x] / (factorial(agents - x - 1) * factorial(x)); // avoid double counting
                value += pos[x];
            }
        }
        return value / factorial(agents); // returns the shapley's value.
    }

    unsigned long factorial(unsigned int n) { return (n == 0) ? 1 : n * factorial(n - 1); } // returns the factorial of a number

    bool is_greater(unsigned int n) { return ((n * 1.0 / (total_res * 1.0)) * 100.0) > 50; } // checks if a group has a majority

};


int main() {
    unsigned int n;
    cin >> n;
    if (n < 2) { // should be a multiagent game
        cout << "At least 2 agents are required to play the Game." << endl;
        return 0;
    }
    Game *g = new Game(n);
    g->util_();
    delete g;
    return 0;
}
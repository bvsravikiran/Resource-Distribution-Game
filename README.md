# Resource-Distribution-Game
Resource Distribution in a Coalitional Game

# Problem Statement:
In a resource acquisition scenario, N agents have the opportunity to collaborate in purchasing an item
of value $10000. Each of the agents has a different amount of resources available that it can contribute
to the purchase and more than 50%(majority) of the total resources are required to purchase the item.
Build a system that produces a 'fair' distribution of the proceedings resulted from the purchase to all the
agents in the grand coalition.

# Constraints:
N > 1.
Resource Ri for an agent i should be a positive integer.

# Sample Input 0:
4 45 25 15 15

# Sample Output 0:
Payoff for agent 1: $5000
Payoff for agent 2: $1666.67
Payoff for agent 3: $1666.67
Payoff for agent 4: $1666.67

# Sample Input 1:
2 35 65

# Sample Output 1:
Payoff for agent 1: $0
Payoff for agent 2: $10000

# Sample Input 2:
5 20 20 20 20 20

# Sample Output 2:
Payoff for agent 1: $2000
Payoff for agent 2: $2000
Payoff for agent 3: $2000
Payoff for agent 4: $2000
Payoff for agent 5: $2000

# Sample Input 3:
5 20 30 10 10 30

# Sample Output 3:
Payoff for agent 1: $2333.33
Payoff for agent 2: $3166.67
Payoff for agent 3: $666.667
Payoff for agent 4: $666.667
Payoff for agent 5: $3166.67

# Description of Sample Test Case:
In the Sample test case #1, the agent 2 itself has the majority number of resources to purchase the
item. Hence, it gets the total proceedings.
In the Sample test case #2, each agent has same number of resources and require any other two
agents to collaborate in order to gain the majority. Hence, the proceedings are distributed equally

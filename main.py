total_res = 0
count = 0
value = 0
for k in range(0, n): # for each player
	for m in range(0, length_of_perm): # Over all permutations
		for x in range(0, n): # single permutation
			if l[m][x] == k:
				#calc the shapley's value
				if(total_res < 51):
					if(total_res + playerdetails[l[m][x]] > threshold):
						value += factorial(count) * factorial(n - count - 1) * (100 - 0)
				total_res = 0
				count = 0
				break
			else:
				total_res += playerdetails[l[m][x]]
				count++;
	return value / factorial(n)
n = int(input())
table = [[0]*n for _ in range(n)]
for i in range(n*n):
	table[i%n][i//n] = i+1
for j in range(n):
	for k in range(n):
		print(table[j][k], end = ' ')
	print()
s, e = map(int, input().split())

for i in range(s, e):
	temp = str(i)
	res = 0
	for t in temp:
		res += int(t)**3
	if res == i:
		print(i, end=' ')
n = int(input())
res = 0
for i in range(100):
	if n - i <= 0:
		break
	n -= i
lst = [str(i-j)+'/'+str(j+1) for j in range(i)]

if i % 2 != 0:
	print(lst[n-1])
else:
	print(lst[i-n])
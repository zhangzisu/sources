arr = [int] * 200
arr[1] = 1
arr[2] = 5
n = int(input())
for i in range(3, n + 1):
	arr[i] = 3 * arr[i - 1] - arr[i - 2] + 2
print(arr[n])

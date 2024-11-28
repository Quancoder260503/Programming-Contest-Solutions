n = int(input())
mod = 987654321
res =  (n - 1) * (n - 2) * (n * n - 3 * n + 12) // 24
print(res % mod)
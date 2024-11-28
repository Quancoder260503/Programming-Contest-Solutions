n, m = map(int, input().split())

a = [0 for i in range(n)]
b = [0 for i in range(n)]

for i in range(n):  
  a[i], b[i] = map(int, input().split()) 
 
def func(days) : 
  sum = 0 
  for i in range(n): 
    sum += (days - days // (b[i] + 1) ) * a[i]
  return sum >= m
  
lo = 0 
hi = 10000000000000000000

while lo < hi: 
  mid = (lo + hi) // 2
  if func(mid) : 
    hi = mid 
  else : 
    lo = mid + 1 

print(lo)

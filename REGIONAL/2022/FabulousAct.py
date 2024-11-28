import math

n, x0, y0, a, b = map(int, input().split()) 
x1 = x0 + a * n
y1 = y0 + b * n
print(math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2) / 2.0)

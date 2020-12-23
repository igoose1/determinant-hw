import numpy as np

n = int(input())

m = [None] * n
for i in range(n):
    m[i] = [float(x) for x in input().split()]

print(np.linalg.det(np.array(m)))

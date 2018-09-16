n, a, b, c = input(), 1, 1, 1
while c < n:
    a, b, c = b, a + b, c + 1
print b
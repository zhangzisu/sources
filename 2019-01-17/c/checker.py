from decimal import Decimal as D, getcontext as G
from sys import argv, exit, stderr

G().prec = 144

class TResult:
	_ok = 0
	_wa = 1
	_pe = 2
	_dirt = 4
	_points = 5

errorMap = {TResult._ok: 'ok', TResult._wa: 'wrong answer', TResult._pe: 'wrong output format', TResult._dirt: 'wrong ouput format', TResult._points: 'points'}

inf = open(argv[1], 'r')
ouf = open(argv[2], 'r')
ans = open(argv[3], 'r')

def quit(result, msg):
	errorName = errorMap.get(result, 'FAIL')
	print(errorName, msg, file = stderr)
	inf.close()
	ouf.close()
	ans.close()
	exit(result)

######## read ########
n = int(inf.readline())
p = []

for i in range(n * 2):
	x, y = map(int, inf.readline().split())
	p.append((x, y))

L = ouf.read().split()
if len(L) != n * 2:
	quit(TResult._pe, 'Expected {} element(s), but found {} element(s)'.format(n * 2, len(L)))

a = []
for s in L:
	try:
		int_s = int(s)
		if s.startswith('0') and s != '0':
			raise ValueError('leading zero')
		if not (1 <= int_s <= 2 * n):
			quit(TResult._wa, 'Integer element a[{}] equals to {}, violates the range [1, {}]'.format(len(a) + 1, int_s, 2 * n))
			break
		a.append(int_s - 1)
	except Exception as e:
		quit(TResult._pe, "Expected integer, but '{}' found".format(s))

######## validate ########
seg = []
for i in range(n * 2):
	if a[i] == i:
		quit(TResult._wa, 'a[{0}] can\'t be equal to {0}'.format(i + 1))
	if a[a[i]] != i:
		quit(TResult._wa, 'a[a[{0}]] [equals to a[{1}] = {2}] is not equal to {0}'.format(i + 1, a[i] + 1, a[a[i]] + 1))
	if i < a[i]:
		seg.append((i, a[i]))

def cross(a, b, c):
	return (b[0] - a[0]) * (c[1] - a[1]) - (c[0] - a[0]) * (b[1] - a[1])

def intersect(u, v, a, b):
	return cross(p[u], p[v], p[a]) * cross(p[u], p[v], p[b]) < 0 and \
		   cross(p[a], p[b], p[u]) * cross(p[a], p[b], p[v]) < 0

already = []
for u, v in seg:
	for a, b in already:
		if intersect(u, v, a, b):
			quit(TResult._wa, 'segment ({}, {}) intersects with segment ({}, {})'.format(a + 1, b + 1, u + 1, v + 1))
	already.append((u, v))

######## judge ########
s = D(0)
for u, v in seg:
	dis2 = (p[u][0] - p[v][0]) ** 2 + (p[u][1] - p[v][1]) ** 2
	s += D(dis2).sqrt()

u = D(ans.readline())
if s >= u:
	quit(TResult._ok, '^Accepted^ the total length of n segment(s) equals to {:.20g}'.format(s))

for i in range(9, 0, -1):
	u = D(ans.readline())
	if s >= u:
		quit(TResult._points, '{:.2f} the total length of n segment(s) equals to {:.20g}'.format(i / 10, s))

quit(TResult._wa, '!Poor! the total length length of n segment(s) equals to {:.20g}'.format(s))


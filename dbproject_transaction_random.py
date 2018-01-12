import random, csv, datetime, math
random.seed("dbproject1")

with open(R'goods.csv', encoding = 'utf-8') as file:
	l = [*csv.DictReader(file)]

goods = {int(i['商品ID']):{'名稱': i['商品名稱'], '金額': int(i['商品金額']), '存量': int(i['商品存量'])} for i in l}
goodsnum = len(l)

transaction = 3000

startdate = datetime.date(2017, 11, 1)
nowdate = startdate #immutable object

opentime = [(datetime.time(10), datetime.time(20))] * 5 + [(datetime.time(9), datetime.time(21))] * 2

#print(goods)

import matplotlib.pyplot as plt, numpy as np
import scipy.optimize as op
from scipy.constants import golden
np.random.seed(48763)
def f(x, a, b, c, d):
    return b*np.exp(d*(x - a))+c
def g(x, m, n, p):
	return n*(x-m)**2+p

start = 6
high = 12
balance = 10
dd1 = 7
D3 = 6 * 4
dd3 = 11
D4 = 12 * 4

b = 1 #?????
alpha = 6.551 * 4
beta = 0.53

fail = False
default_delta = -1
#compute delta
if dd3 - balance == beta:
	if D3 != alpha:
		print("fatal error 1")
		fail = True
	else:
		print("warning: set delta =", default_delta)
		delta = default_delta
else:
	if D3 == alpha:
		print("fatal error 2")
		fail = True
	else:
		delta = (np.log(dd3 - balance) - np.log(beta)) / (D3 - alpha)
		if delta > 0:
			print("fatal error 3: positive delta")
			fail = True
#compute m
if not fail:
	print(delta)
	tmp_a = beta * delta * np.exp(delta * (D3 - alpha))
	m = D3 - 2 * (dd3 - high) / tmp_a
	n = (dd3 - high) / (D3 - m)**2
	D1 = [m + np.sqrt((dd1 - high) / n), m - np.sqrt((dd1 - high) / n)]
	D1 = [i if i < m else None for i in D1]
	if D1[0] != None and D1[1] != None:
		print("warning two D1 nonnone")
	d = [op.broyden1((lambda d: n * (2 * D - 2 * m) * (1 - 1 / np.exp(d * D)) - d * (dd1 - start)), 1) if D != None else None for D in D1]
	if D1[0] == None:
		D1 = D1[1]
		d = d[1]
	else:
		D1 = D1[0]
		d = d[0]

print(d)
a = D1 - np.log(2 * n * (D1 - m) / (b * d)) / d
c = start - b * np.exp(-a * d)
def F(x):
	if x < D1:
		return f(x, a, b, c, d)
	elif x <= D3:
		return g(x, m, n, high)
	else:
		return f(x, alpha, beta, balance, delta)

fout_tran = open("dbrandom_tran.txt", 'w', encoding = 'utf-8')
fout_order = open("dbrandom_ord.txt", 'w', encoding = 'utf-8')
fout_ord_id = open("dbrandom_ord_id.txt", 'w', encoding = 'utf-8')
fout_tra_ord = open("dbrandom_tra_ord.txt", 'w', encoding = 'utf-8')

def total_price(l):
	sol = 0
	for i, n in zip(range(len(goods)), l):
		sol += goods[i + 1]['金額'] * n
	return sol

def buy_list(okane):
	sol, n = [], len(goods)
	while sum(sol) == 0:
		sol = [0] * len(goods)
		"""for i in range(n):
			price = goods[i + 1]['金額']
			t = random.paretovariate(price / (np.pi * golden) / okane) - 1
			sol.append(round(t))"""
		tane = 0
		while tane < okane:
			a = random.randint(1, len(goods))
			pick = random.randint(1, goods[a]['金額'])
			if pick == 1:
				sol[a - 1] += 1
			else:
				continue
			tane = random.random() * 10
	return sol

now_ord = 0
now_tra = 0
num_of_user = 106

while transaction > 0:
	now_time, end_time = (datetime.datetime.combine(nowdate, t) for t in opentime[nowdate.weekday()])
	mean = F((nowdate - startdate).days)
	today_trans = []
	print(mean)
	while transaction > 0:
		wait_time = random.expovariate(mean) * datetime.timedelta(hours = 1)
		now_time += wait_time
		if now_time > end_time:
			break
		order_n, okane = 0, 0
		while order_n == 0:
			order_n = np.random.poisson(1)
		while okane <= 0:
			okane = random.normalvariate(3, 1)
		order = []
		for _ in range(order_n):
			order.append(buy_list(okane))
		#print(now_time.strftime("%Y-%m-%d %H:%M:%S"))
		#print(*[(sum(i), total_price(i)) for i in order])
		today_trans.append((now_time, order))
		transaction -= 1
	nowdate += datetime.timedelta(days = 1)
	people = random.sample(range(1, num_of_user + 1, 1), num_of_user)
	while len(people) < len(today_trans):
		people.extend(random.sample(range(1, num_of_user + 1, 1), num_of_user))
	for (now, orders), person in zip(today_trans, people):
		now_tra += 1
		fout_tran.write("""INSERT INTO `交易` (`交易時間`, `交易金額`) VALUES ('{}', {});\n""".format(now.strftime("%Y-%m-%d %H:%M:%S"), sum(total_price(i) for i in orders)))
		for order in orders:
			now_ord += 1
			fout_order.write("""INSERT INTO `點餐` (`會員ID`) VALUES ({});\n""".format(person))
			fout_tra_ord.write("""INSERT INTO `交易-點餐對應` (`交易編號`, `點餐代碼`) VALUES ({}, {});\n""".format(now_tra, now_ord))
			for goodid, num in enumerate(order, 1):
				if num > 0:
					fout_ord_id.write("""INSERT `點餐資訊` (`點餐代碼`, `商品ID`, `商品數量`) VALUES ({}, {}, {});\n""".format(now_ord, goodid, num))
fout.close()

"""z1 = np.linspace(0,D1,abs(D1-0)*600+1)
z2 = np.linspace(D1,D3,abs(D3-D1)*600+1)
z3 = np.linspace(D3,D4,abs(D4-D3)*600+1)
plt.plot(z1, f(z1, a, b, c, d))
plt.plot(z2, g(z2, m, n, high))
plt.plot(z3, f(z3, alpha, beta, balance, delta))
plt.show()"""
"""
start = 6
high = 12
balance = 10
D1 = 2
dd1 = 8
D2 = 4
D3 = 6
dd3 = 11

def bezier(K, l, t):
	if len(l) + 1 != K:
		if len(l) + 1 > K:
			l = l[:len(l) + 1]
		else:
			return None
	sol = []
	for (x1, y1), (x2, y2) in zip(l, l[1:]):
		sol.append((x1 * (1 - t) + x2 * t, y1 * (1 - t) + y2 * t))
	if K == 1:
		return sol[0]
	else:
		return bezier(K - 1, sol, t)

tmp = np.sqrt(high * (-dd1 + high - dd3) + dd1 * dd3)
y = [high + tmp, high - tmp]
t_bar = [(dd1 - yi) / (dd1 + dd3 - 2 * yi) for yi in y]
y = [y[i] for i in range(len(y)) if t_bar[i] >= 0 and t_bar[i] <= 1]
t_bar = [t_bar[i] for i in range(len(t_bar)) if t_bar[i] >= 0 and t_bar[i] <= 1]
x = [(-D1 + D2 - 2 * D1 * t + D1 * t**2 + D3 * t**2) / (2 * (1 - t**2)) for t in t_bar]
z = np.linspace(0, 1, 1001)
print(x, y, t_bar, sep='\n')

for xi, yi in zip(x, y):
	plt.plot(*bezier(2, [(D1, dd1), (xi, yi), (D3, dd3)], z))

plt.show()
"""

"""Reference: http://www.csie.ntnu.edu.tw/~u91029/State.html"""
"""Reference: http://mathworld.wolfram.com/15Puzzle.html"""
import keyboard, heapq, time, os
from itertools import chain, count as infseries
from operator import itemgetter
from copy import deepcopy
class Puzzle:
	heng = 0
	shu = 0
	matrix = []
	anchor = (0, 0)
	sign = '--'
	def __init__(self, heng, shu, anchor_x = -1, anchor_y = -1, anchor_sign = '--', matrix = None):
		self.heng = heng
		self.shu = shu
		if matrix == None:
			self.matrix = [[chr(a) + str(i) for a in range(ord('A'), ord('A') + heng)] for i in range(1, 1 + shu)]
		else:
			self.matrix = deepcopy(matrix)
		if anchor_x >= heng or anchor_x < -heng: anchor_x = -1
		if anchor_y >= shu or anchor_y < -shu: anchor_y = -1
		self.sign = anchor_sign
		self.matrix[anchor_y][anchor_x] = anchor_sign
		self.anchor = (anchor_x if anchor_x >= 0 else heng + anchor_x, anchor_y if anchor_y >= 0 else shu + anchor_y)
	def __str__(self):
		s = '\n\n'.join([''.join(['{:<3}'.format(j) for j in i]) for i in self.matrix])
		return s
	def _moveone(self, _x, _y):
		self.matrix[self.anchor[1]][self.anchor[0]] = self.matrix[self.anchor[1] + _y][self.anchor[0] + _x]
		self.matrix[self.anchor[1] + _y][self.anchor[0] + _x] = self.sign
		self.anchor = (self.anchor[0] + _x, self.anchor[1] + _y)
	def move(self, x = 0, y = 0):
		if x == 0 and y == 0:
			return
		if x > 0:
			if self.anchor[0] >= self.heng - 1:
				return self.move(0, y)
			self._moveone(1, 0)
			return self.move(x - 1, y)
		if x < 0:
			if self.anchor[0] <= 0:
				return self.move(0, y)
			self._moveone(-1, 0)
			return self.move(x + 1, y)
		if y > 0:
			if self.anchor[1] >= self.shu - 1:
				return self.move(x, 0)
			self._moveone(0, 1)
			return self.move(x, y - 1)
		if y < 0:
			if self.anchor[1] <= 0:
				return self.move(x, 0)
			self._moveone(0, -1)
			return self.move(x, y + 1)


def f(p, x_, y_):
	p.move(x_, y_)
	print(p, '\n')

p = Puzzle(4, 4)
"""f(p, 0, 0)
keyboard.add_hotkey('up', f, [p, 0, -1])
keyboard.add_hotkey('down', f, [p, 0, 1])
keyboard.add_hotkey('left', f, [p, -1, 0])
keyboard.add_hotkey('right', f, [p, 1, 0])
record = keyboard.record('esc')
mapping = lambda i: '上' if i == 'up' else ('下' if i == 'down' else ('左' if i == 'left' else '右'))
print(*map(mapping, (i.name for i in record[:-1] if i.event_type == 'down')))"""
def catch_matrix(p):
	if isinstance(p, Puzzle):
		return p.matrix
	return p

def catch_anchor(p, anchor_sign = '--'):
	if isinstance(p, Puzzle):
		return p.anchor
	else:
		for y, l in enumerate(p):
			for x, c in enumerate(l):
				if c == anchor_sign:
					return (x, y)

def catch_hengshu(p):
	if isinstance(p, Puzzle):
		return (p.heng, p.shu)
	else:
		return (len(p[0]), len(p))

def catch_anchorsign(p):
	if isinstance(p, Puzzle):
		return p.sign
	else:
		return '--'

def build_puzzle_from_matrix(m, anchor_sign = '--'):
	heng, shu = catch_hengshu(m)
	anchor = catch_anchor(m, anchor_sign)
	p = Puzzle(heng, shu, anchor[0], anchor[1], anchor_sign = anchor_sign, matrix = m)
	return p

def build_puzzle_samesize(p, anchor_x = -1, anchor_y = -1):
	return Puzzle(p.heng, p.shu, anchor_x, anchor_y)

def chain_puzzle(p, delete_anchor = False, anchor_sign = '--'):
	p = catch_matrix(p)
	return chain(*p) if not delete_anchor else (i for i in chain(*p) if i != anchor_sign)

def permutation_inversion(l, target = None):
	if target == None:
		target = list(range(l))
	d = {i: j for j, i in enumerate(target)}
	l = list(map(lambda i: d[i], l))
	sol = sum(l[i] > l[j] for i in range(len(l)) for j in range(i + 1, len(l)))
	return sol

#same anchor sign
def puzzle_heuristic(p, pright, anchor_sign = None):
	if anchor_sign == None: anchor_sign = catch_anchorsign(p)
	p = catch_matrix(p)
	pright = catch_matrix(pright)
	s = set(chain_puzzle(p, True, anchor_sign))
	dp = {c: [] for c in s}
	dpright = {c: [] for c in s}
	for P, D in (p, dp), (pright, dpright):
		for j, l in enumerate(P):
			for i, c in enumerate(l):
				if c != anchor_sign:
					D[c].append((i, j))
	return sum(sum(min(abs(o1_x - o2_x) + abs(o1_y - o2_y) for o2_x, o2_y in dpright[c]) for o1_x, o1_y in dp[c]) for c in s)

def puzzle_heuristic_another(p, pright, anchor_sign = None):
	if anchor_sign == None: anchor_sign = catch_anchorsign(p)
	return sum(a != b for a, b in zip(chain_puzzle(p), chain_puzzle(pright)) if a != anchor_sign)

def can_move_puzzle(p, way):
	anchor = catch_anchor(p)
	heng, shu = catch_hengshu(p)
	if way == 'up' and anchor[1] <= 0: return False
	if way == 'down' and anchor[1] + 1 >= shu: return False
	if way == 'left' and anchor[0] <= 0: return False
	if way == 'right' and anchor[0] + 1 >= heng: return False
	return True

def move_puzzle(p, way):
	if way == 'up': p.move(0, -1)
	elif way == 'down': p.move(0, 1)
	elif way == 'left': p.move(-1, 0)
	elif way == 'right': p.move(1, 0)
	return 1 #return cost

#return (bool, int)
#@post: now_state is same as beginning
def _IDAstar(now_state, target_state, bound, h, can_move_state, move_state, now_gx, transfer_way, now_ans, printf, **kwargs):
	is_reversed = lambda l: (l[-1], l[-2]) in transfer_way if len(l) >= 2 else False
	hx = h(now_state, target_state)
	if now_gx + hx > bound:
		return (False, now_gx + hx) #next bound
	if hx == 0: return (True, now_gx) #find solution
	found_bound = []
	for way, reversed_way in transfer_way:
		if not can_move_state(now_state, way, **kwargs):
			#print(now_state, way, sep = '\n')
			continue
		now_ans.append(way)
		if is_reversed(now_ans):
			now_ans.pop()
			continue
		cost = move_state(now_state, way, **kwargs)
		printf(now_gx + cost, bound, now_state, **kwargs)
		is_ans, c = _IDAstar(now_state, target_state, bound, h, can_move_state, move_state, now_gx + cost, transfer_way, now_ans, printf, **kwargs)
		move_state(now_state, reversed_way, **kwargs)
		if is_ans: return (True, c)
		printf(now_gx, bound, now_state, **kwargs)
		if c != None: found_bound.append(c)
		now_ans.pop()
	return (False, min(found_bound)) if len(found_bound) > 0 else (False, None)

def IDAstar(now_state, target_state, h, can_move_state, move_state, transfer_way, printf = None, **kwargs):
	if printf == None:
		printf1 = lambda *a, **kwargs: None
	else:
		#printf1 = lambda g, b, state, **kwargs: (os.system('cls'), print('bound = {}   now cost = {}'.format(b, g)), printf(state))
		printf1 = lambda g, b, state, **kwargs: (print('\n' * 30), print('bound = {}   now cost = {}'.format(b, g)), printf(state))
	bound = 0
	#start = time.time()
	now_ans = []
	while True:
		#print(bound)
		is_ans, bound = _IDAstar(now_state, target_state, bound, h, can_move_state, move_state, 0, transfer_way, now_ans, printf1, **kwargs)
		#end = time.time()
		#print(bound, end - start)
		#start = time.time()
		if is_ans: return now_ans

def is_reasonable_puzzles(p, q, anchor_sign = '--'):
	for i in Counter(chain_puzzle(p, False, anchor_sign)).values():
		if i >= 2: return True
	return (permutation_inversion(list(chain_puzzle(p, True, anchor_sign)), list(chain_puzzle(q, True, anchor_sign))) + ((p.heng - 1) * (p.anchor[1] - q.anchor[1]))) % 2 == 0
	#return (permutation_inversion(list(chain_puzzle(p, anchor_sign)), list(chain_puzzle(q, anchor_sign))) + ((p.anchor[0] - q.anchor[0]) + (p.anchor[1] - q.anchor[1]))) % 2 == 0

def optimize_puzzle(p, istarget = True, anchor_x = -1, anchor_y = -1, visual = False):
	"""matrix following a naming rule"""
	if not isinstance(p, Puzzle):
		p = build_puzzle_from_matrix(p)
	if istarget:
		now_puzzle, target_puzzle = build_puzzle_samesize(p, anchor_x, anchor_y), p
	else:
		target_puzzle, now_puzzle = build_puzzle_samesize(p, anchor_x, anchor_y), p
	#print(permutation_inversion(list(chain_puzzle(target_puzzle, True)), list(chain_puzzle(now_puzzle, True))))
	#print(list(chain_puzzle(target_puzzle, True)))
	if not is_reasonable_puzzles(now_puzzle, target_puzzle): return None
	return IDAstar(now_puzzle, target_puzzle, puzzle_heuristic, can_move_puzzle, move_puzzle, [('up', 'down'), ('down', 'up'), ('left', 'right'), ('right', 'left')], printf = (None if not visual else lambda s: (print(s), print('\n' * 10), time.sleep(0.01))))

def optimize_puzzle_matrix(start, end, anchor_sign = '--', visual = False):
	"""NO REPEATED ELEMENT"""
	start_puzzle, end_puzzle = build_puzzle_from_matrix(start, anchor_sign), build_puzzle_from_matrix(end, anchor_sign)
	if not is_reasonable_puzzles(start_puzzle, end_puzzle, anchor_sign): return None
	return IDAstar(start_puzzle, end_puzzle, puzzle_heuristic, can_move_puzzle, move_puzzle, [('up', 'down'), ('down', 'up'), ('left', 'right'), ('right', 'left')], printf = (None if not visual else lambda s: (print(s), print('\n' * 10), time.sleep(0.01))))

target = [['B2', 'C2', 'C1', 'A4'],
          ['A2', 'B3', 'D1', 'B1'],
          ['A3', 'D3', 'C4', 'B4'],
          ['C3', 'A1', 'D2', '--']]
#print(optimize_puzzle(target, visual = True))
#['left', 'up', 'left', 'down', 'left', 'up', 'right', 'down', 'right', 'right',
# 'up', 'up', 'up', 'left', 'left', 'down', 'right', 'down', 'left', 'left',
# 'up', 'up', 'right', 'down', 'left', 'down', 'down', 'right', 'right', 'right',
# 'up', 'left', 'left', 'up', 'right', 'right', 'down', 'left', 'up', 'up',
# 'right', 'down', 'left', 'down', 'down', 'left', 'up', 'right', 'down', 'right']

fromm = [[7, 0, 1, 9],
         [6, 3, 2, 10],
         [5, 4, 8, 11]]
tom =   [[1, 2, 3, 11],
         [4, 5, 6, 9],
         [7, 8, 0, 10]]
print(optimize_puzzle_matrix(fromm, tom, 0, visual = True))

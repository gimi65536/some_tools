"""Reference: http://www.csie.ntnu.edu.tw/~u91029/State.html"""
import keyboard
from itertools import chain
from operator import itemgetter
class Puzzle:
	heng = 0
	shu = 0
	matrix = []
	anchor = (0, 0)
	def __init__(self, heng, shu, anchor_x = -1, anchor_y = -1):
		self.heng = heng
		self.shu = shu
		self.matrix = [[chr(a) + str(i) for a in range(ord('A'), ord('A') + heng)] for i in range(1, 1 + shu)]
		if anchor_x >= heng or anchor_x < -heng: anchor_x = -1
		if anchor_y >= shu or anchor_y < -shu: anchor_y = -1
		self.matrix[anchor_y][anchor_x] = '--'
		self.anchor = (anchor_x if anchor_x >= 0 else heng + anchor_x, anchor_y if anchor_y >= 0 else shu + anchor_y)
	def __str__(self):
		s = '\n\n'.join([''.join(['{:<3}'.format(j) for j in i]) for i in self.matrix])
		return s
	def _moveone(self, _x, _y):
		self.matrix[self.anchor[1]][self.anchor[0]] = self.matrix[self.anchor[1] + _y][self.anchor[0] + _x]
		self.matrix[self.anchor[1] + _y][self.anchor[0] + _x] = '--'
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

def catch_anchor(p):
	if isinstance(p, Puzzle):
		return p.anchor
	else:
		for y, l in enumerate(p):
			for x, c in enumerate(l):
				if c == '--':
					return (x, y)

def catch_hengshu(p):
	if isinstance(p, Puzzle):
		return (p.heng, p.shu)
	else:
		return (len(p[0]), len(p))

def build_puzzle_from_matrix(m):
	heng, shu = catch_hengshu(m)
	anchor = catch_anchor(m)
	p = Puzzle(heng, shu, anchor[0], anchor[1])
	p.matrix = m.copy()
	return p

def build_puzzle_samesize(p, anchor_x = -1, anchor_y = -1):
	return Puzzle(p.heng, p.shu, anchor_x, anchor_y)

def chain_puzzle(p):
	p = catch_matrix(p)
	return chain(*p)

def permutation_inversion(l, target = None):
	if target == None:
		target = list(range(l))
	d = {i: j for j, i in enumerate(target)}
	l = list(map(lambda i: d[i], l))
	sol = sum(i[0] > i[1] for i in zip(l, l[1:]))
	return sol

def puzzle_heuristic(p, pright):
	p = catch_matrix(p)
	pright = catch_matrix(pright)
	dp = {c: (i, j) for j, l in enumerate(p) for i, c in enumerate(l) if c != '--'}
	dpright = {c: (i, j) for j, l in enumerate(pright) for i, c in enumerate(l) if c != '--'}
	return sum(abs(dp[c][0] - dpright[c][0]) + abs(dp[c][1] - dpright[c][1]) for c in chain_puzzle(p) if c != '--')

def puzzle_heuristic_another(p, pright):
	return sum(a != b for a, b in zip(chain_puzzle(p), chain_puzzle(pright)) if a != '--')

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
	return 1

#return (bool, int)
#@post: now_state is same as beginning
def _IDAstar(now_state, target_state, bound, h, can_move_state, move_state, now_gx, transfer_way, now_ans, **kwargs):
	def is_reversed(now_ans):
		for i in range(1, len(now_ans) // 2 + 1):
			ite = zip(now_ans[(-i):], reversed(now_ans[(-2 * i):(-i)]))
			success = True
			for t in ite:
				if t not in transfer_way:
					success = False
					break
			if success: return True
		return False
	hx = h(now_state, target_state)
	if now_gx + hx > bound: return (False, now_gx + hx) #next bound
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
		"""if len(now_ans) >= 2 and (now_ans[-1], now_ans[-2]) in transfer_way:
			now_ans.pop()
			continue"""
		cost = move_state(now_state, way, **kwargs)
		is_ans, c = _IDAstar(now_state, target_state, bound, h, can_move_state, move_state, now_gx + cost, transfer_way, now_ans, **kwargs)
		move_state(now_state, reversed_way, **kwargs)
		if is_ans: return (True, c)
		if c != None: found_bound.append(c)
		now_ans.pop()
	return (False, min(found_bound)) if len(found_bound) > 0 else (False, None)

def IDAstar(now_state, target_state, h, can_move_state, move_state, transfer_way, **kwargs):
	bound = 0
	now_ans = []
	while True:
		is_ans, bound = _IDAstar(now_state, target_state, bound, h, can_move_state, move_state, 0, transfer_way, now_ans, **kwargs)
		print(bound)
		if is_ans: return now_ans

def optimize_puzzle(p, istarget = True, anchor_x = -1, anchor_y = -1):
	if not isinstance(p, Puzzle):
		p = build_puzzle_from_matrix(p)
	if istarget:
		now_puzzle, target_puzzle = build_puzzle_samesize(p, anchor_x, anchor_y), p
	else:
		target_puzzle, now_puzzle = build_puzzle_samesize(p, anchor_x, anchor_y), p
	return IDAstar(now_puzzle, target_puzzle, puzzle_heuristic, can_move_puzzle, move_puzzle, [('up', 'down'), ('down', 'up'), ('left', 'right'), ('right', 'left')])

target = [['B2', 'C2', 'C1', 'A4'], ['A2', 'B3', 'D1', 'B1'], ['A3', 'D3', 'C4', 'B4'], ['C3', 'A1', 'D2', '--']]
print(optimize_puzzle(target))
#['left', 'up', 'left', 'down', 'left', 'up', 'right', 'down', 'right', 'right', 'up', 'up', 'up', 'left', 'left', 'down', 'right', 'down', 'left', 'left', 'up', 'up', 'right', 'down', 'left', 'down', 'down', 'right', 'right', 'right', 'up', 'left', 'left', 'up', 'right', 'right', 'down', 'left', 'up', 'up', 'right', 'down', 'left', 'down', 'down', 'left', 'up', 'right', 'down', 'right']

#模擬拼圖
#Python 3.6.3
#為了碧藍航線茶會活動的拼圖而寫
#前提：你得知道你最終的目標，以及手工拼出拼圖的耐心
#拼完之後按esc以終止
#最後會輸出一串中文代表你按過的按鈕
#他會擷取你所有敲鍵盤的紀錄，就算不在視窗內
import keyboard
class puzzle:
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
p = puzzle(4, 4)
f(p, 0, 0)
keyboard.add_hotkey('up', f, [p, 0, -1])
keyboard.add_hotkey('down', f, [p, 0, 1])
keyboard.add_hotkey('left', f, [p, -1, 0])
keyboard.add_hotkey('right', f, [p, 1, 0])
record = keyboard.record('esc')
mapping = lambda i: '上' if i == 'up' else ('下' if i == 'down' else ('左' if i == 'left' else '右'))
print(*map(mapping, (i.name for i in record[:-1] if i.event_type == 'down')))

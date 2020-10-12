import heapq #Them vao thu vien heapq
import itertools #Them thu vien cho object iterators
import math
import sys #De su dung command line arguments

#Do neu ta reprioritize thi se pha vo tinh invariant cua heap.
#Giai phap thay the: Mark entry la da Removed va them 1 entry moi vao voi revised priority
class PriorityQueue:
	def __init__(self):
		self.pq = [] #List cac entry (priority, task) duoc xay dung boi heap 
		self.found_entry = {} #Chua cac entry da duoc duyet qua roi
		self.mark_removed = 'Removed-Task' #Placeholder cho cac muc danh dau la Removed
		self.counter = itertools.count() #Unique sequence number nhu la stt cho cac entry
		#de giup cho truong hop co 2 entry có cùng priority thi ta se lay theo thứ tự như lúc thêm vào
	
	#Them vao 1 task moi hoac la thay doi priority neu nhu task nay da lam trong pq
	def push(self, priority, task):
		
		if task in self.found_entry: #Neu task nay da ton tai trong pq thi ta se danh dau task 
			#nay la da removed
			self.removed_task(task)
			
		count = next(self.counter) #Lay so thu tu tiep theo cho entry moi nay
		entry = [priority, count, task] #Tao 1 list
		self.found_entry[task] = entry #Danh dau entry nay da co trong dict
		heapq.heappush(self.pq, entry) #Push entry nay vao pq

	#Xoa task ra khoi dict found_entry va danh dau task cua entry nay la Removed-Task
	#Raise error if this task doesn't exist
	def removed_task(self, task):
		entry = self.found_entry.pop(task) #Pop this entry
		entry[-1] = self.mark_removed #Mark its task as being removed

	#Remove and return the lowest priority task in this pq.
	#Raise error if this entry pq is empty
	def pop(self):
		while self.pq:
			priority, count, task = heapq.heappop(self.pq) #Pop and retrive 1 entry

			#Check this entry is marked as Removed-Task or not
			if task is not self.mark_removed: #If this entry is not marked as Removed-Task
				del self.found_entry[task] #Delete this entry from found_entry
				return task
		return None
		#raise KeyError('Pop from an empty PriorityQueue')

	def empty(self):
		if self.pq:
			return False
		else:
			return True

class Graph:
	def __init__(self):
		self.G = []
		
	def input(self, file_name):
	
		with open(file_name, 'rt') as f:
			self.n = int(f.readline())
			#Doc 1 dong va bo di ki tu \n va tach cac phan tu trong chuoi thanh list
			self.start = f.readline().rstrip('\n').split()
			self.goal = f.readline().rstrip('\n').split()

			#Chuyen doi start va goal thanh tuple kieu so nguyen bang comprehension
			self.start = tuple(int(x) for x in self.start)
			self.goal = tuple(int(x) for x in self.goal)

			#Doc tung line trong f va bien cac line thanh tung list
			for line in f:
				#Bien doi 1 list gom cac phan tu la chuoi thanh list gom cac so nguyen
				tmp = list(int(x) for x in line.split())
				self.G.append(tmp) #Them vao G

	#Ham kiem tra xem diem hien tai nay co di toi duoc khong?
	def isPassable(self, current):
		(x, y) = current
		return self.G[x][y] != 1

	#Ham kiem tra xem diem hien tai dang xet co vuot qua bien cua ban do hay khong?
	def isBound(self, current):
		(x, y) = current
		return 0 <= x < self.n and 0 <= y < self.n

	#Ham tim cac diem lan can 8 co the di duoc tu current
	#Tra ve 1 list cac diem di duoc tu diem current	
	def get8Neighbors(self, current): 
		x, y = current
		#Cac diem lan can 8 cua current
		points8 = [(x-1, y-1), (x-1, y), (x-1, y+1), (x, y+1), (x+1, y+1), (x+1, y), (x+1, y-1), 
		(x, y-1)]

		#Loc ra cac diem khong vuot ra ngoai bien
		points8 = filter(self.isBound, points8)

		#Loc ra cac diem co the di toi duoc
		points8 = filter(self.isPassable, points8)
		
		return points8

	def aStar(self):
		#Tree search
		#Check if start or goal are not passable
		if not self.isPassable(self.start) or not self.isPassable(self.goal):
			return -1, -1

		#Init Priority Queue:
		pq = PriorityQueue()
		pq.push(heuristic(self.start, self.goal), self.start) #Push start va f(n) vao
		
		backtracking = {} #Truy vet path		
		#Truy vet cua dinh start = None, goal = None
		backtracking[self.start] = None
		backtracking[self.goal] = None #Gia su chua tim duoc duong di
		
		g_n = {} #Luu cost den cac diem hien tai
		#Cost tai start bang 0
		g_n[self.start] = 0

		while not pq.empty():
			cur = pq.pop() #Lay 1 diem trong pq
			
			if cur == self.goal or cur == None:
				break

			feasiblePoint = list(self.get8Neighbors(cur))
			
			#Lay cac diem lan can 8 co the di duoc cua cur
			for next in feasiblePoint:

				newg_n = g_n[cur] + 1
				f_n = newg_n + heuristic(next, self.goal)
				#Neu diem next chua duoc duyet hoac neu next da duoc mo thi kiem tra 
				#xem f'(n) < f(n) hay khong?
				if next not in g_n or newg_n < g_n[next]:
					g_n[next] = newg_n #Cap nhat lai g_n
					pq.push(f_n, next) #Push diem next nay vao stack
					backtracking[next] = cur

		#Neu khong tim thay duong di => return -1
		if backtracking[self.goal] == None:
			return -1, -1

		#Neu co duong di => return cost va path 
		p = self.goal
		path = []
		while p != None:
			path.append(p)
			p = backtracking[p]

		#Dao nguoc lai path cho dung huong
		path.reverse()
		return g_n[self.goal] + 1, path

	def output(self, cost, path, file_name):
		f = open(file_name, 'wt')

		if cost == -1:
			print(-1, file = f)
			return

		#In cost
		print(cost, file = f)
		#In ra cac diem di qua
		for x in path:
			if path.index(x) == len(path) - 1:
				print(x, end = '', file = f)
			else:
				print(x, end = ' ', file = f)
		print(file = f)

		#Draw grid path
		for i in range(self.n):
			for j in range(self.n):
				if j != self.n - 1:
					space = ' '
				else:
					space = ''

				if (i, j) in path:
					if (i, j) == self.start:
						print('S', end = space, file = f)
					elif (i, j) == self.goal:
						print('G', end = space, file = f)
					else:
						print('x', end = space, file = f)
				elif self.G[i][j] == 1:
					print('o', end = space, file = f)
				else:
					print('-', end = space, file = f)

			if i != self.n - 1:
				print(file = f) #print newline


		
#Ham heuristic la khoang cach Euclide tu diem hien tai den diem dich
def heuristic(a, b):
	x1, y1 = a
	x2, y2 = b
	return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

#Main driver
def main(argv):
	a = Graph()
	a.input(argv[0])
	cost, path = a.aStar()
	a.output(cost, path, argv[1])

	print('Success!')

if __name__ == '__main__':
	main(sys.argv[1:])



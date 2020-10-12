#include "PriorityQueue.h"
#include <stack>
int **G; // Matrix do thi
int n; // So luong dinh (Trang thai)
int *backPointers; // Con tro quay lui
int start, goal; // Diem xuat phat va dich
int *colour; // Bang danh dau dinh da duyet

struct P {
	int ver;
	int value;
};

void input() {
	freopen("input.txt", "rt", stdin);
	// Nhap n, start, end
	cin >> n >> start >> goal;
	// Khoi tao do thi, con tro quay lui va bang danh dau
	G = new int*[n];
	backPointers = new int[n];
	colour = new int[n];

	// Khoi tao cac phan tu bang 0
	for (int i = 0; i < n; i++) {
		backPointers[i] = 0;
		colour[i] = 0;
	}

	// Vi tri quay lui cua start se la -1
	backPointers[start] = -1;
	

	for (int i = 0; i < n; i++)
	{
		G[i] = new int[n];
	}

	// Nhap do thi
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			cin >> G[i][j];
		}
	}

}
void output() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
}

void UCS_forward() {
	// Khoi tao hang doi uu tien
	CPriorityQueue Q;
	Q.initQueue();
	// Cap nhat trang thai dau tien la dinh start
	Q.enQueue(start, 0);
	// Khoi tao CNode
	CNode p;

	int pathCost;
	// Duyet cho den khi Q rong
	while (!Q.empty()) {
		p = Q.front(); // Lay Node dau trong hang doi co do uu tien nho nhat
		Q.deQueue(); // Pop dinh ra khoi hang doi
		// Lay dinh thu i
		int i = p.getVer();
		int costI = p.getCost();

		// Danh dau dinh thu i
		colour[i] = 1;

		// Neu nhu dinh goal da duoc danh dau
		// luu lai path cost
		if (i == goal)
			pathCost = costI;

		for (int j = 0; j < n; j++)
		{
			// Neu nhu co succs(i) && dinh j chua duoc danh dau
			if (G[i][j] != 0 && colour[j] == 0) {
				// Kiem tra xem diem j da nam trong Q chua?
				// Neu co: thi check Cost cua j trong Q co lon hon Cost moi cua dinh (i den j) ? Update : Pass
				// Neu khong: thi push vao queue
				if (Q.findCost(j) == -1) {
					// Luu lai con tro quay lui de truy vet
					backPointers[j] = i;
					// Them dinh j vao Queue
					Q.enQueue(j, costI + G[i][j]);
				}
				else if (Q.findCost(j) > (costI + G[i][j])) { // Neu da co trong Queue thi update
					// Luu lai con tro quay lui de truy vet
					backPointers[j] = i;
					// Update dinh j vao Queue
					Q.set(j, costI + G[i][j]);
				}
			}

		}
	}

	cout << "Path cost: " << pathCost << endl;
	// Neu dinh goal duoc danh dau thi tuc la co ket qua
	if (colour[goal]) {
		// Duyet nguoc
		int i = goal;

		do {
			cout << i << " "; // In dinh nay
			i = backPointers[i]; // Quay lui nguoc ve dinh tro toi
		} while (i != -1); // Neu duyet den start thi ket thuc
		cout << endl;
	}
	else
		cout << "Cannt find a result!" << endl;
}

// UCS suy dien lui
// Uu diem: Khong can dung mang luu con tro quay lui
// Khuyet diem: Do khong dung con tro quay lui, nen thu tu cua path se khong theo dung lo trinh
// Do mang colour duyet tu 0 - n
// Cai tien dung stack de luu path
void UCS_backward() {
	// Khoi tao hang doi uu tien
	CPriorityQueue Q;
	Q.initQueue();
	// Cap nhat trang thai dau tien la dinh start
	Q.enQueue(goal, 0);
	// Khoi tao CNode
	CNode p;
	// Dung stack de luu path
	stack<int> visited;


	// Luu chi phi
	int pathCost;
	// Duyet cho den khi Q rong
	while (!Q.empty()) {
		p = Q.front(); // Lay Node dau trong hang doi co do uu tien nho nhat
		Q.deQueue(); // Pop dinh ra khoi hang doi
		// Lay dinh thu i
		int i = p.getVer();
		int costI = p.getCost();

		// Danh dau dinh thu i
		colour[i] = 1;		
		// push vao stack
		visited.push(i);

		// Neu nhu dinh goal da duoc danh dau
		// luu lai path cost va thoat ra khoi vong lap
		if (i == start) {
			pathCost = costI;
			break;
		}
		for (int j = n - 1; j >= 0; j--)
		{
			// Neu nhu co duong di tu j - i && dinh j chua duoc danh dau
			if (G[j][i] != 0 && colour[j] == 0) {
				// Kiem tra xem diem j da nam trong Q chua?
				// Neu co: thi check Cost cua j trong Q co lon hon Cost moi cua dinh (j den i) ? Update : Pass
				// Neu khong: thi push vao queue
				if (Q.findCost(j) == -1) {
					// Them dinh j vao Queue
					Q.enQueue(j, costI + G[j][i]);
				}
				else if (Q.findCost(j) > (costI + G[j][i])) { // Neu da co trong Queue thi update
					// Update dinh j vao Queue
					Q.set(j, costI + G[j][i]);
				}
			}

		}
	}

	cout << "Path cost: " << pathCost << endl;
	// Neu dinh goal duoc danh dau thi tuc la co ket qua
	if (colour[goal]) {
		// Duyet stack
		// UCS backward: Khong can con tro quay lui vi cac dinh duoc danh dau la ket qua cua bai toan

		while (!visited.empty()) {
			// In dinh tren cung cua stack
			cout << visited.top() << " ";
			// pop ra khoi stack
			visited.pop();
		}
		cout << endl;
	}
	else
		cout << "Cannt find a result!" << endl;
}

int main() {
	input();
	/*UCS_forward();*/
	UCS_backward();
	return 0;
}
#include <iostream>
#include <queue>
using namespace std;

int **G; // Matrix do thi
int n; // So luong dinh (Trang thai)
int *backPointers; // Con tro quay lui
int start, goal; // Diem xuat phat va dich
int *colour; // Bang danh dau dinh da duyet


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

// BFS - Breadth-first search
void BFS() {
	// Khoi tao Q
	queue<int> Q;
	// Cap nhat trang thai dau tien la dinh start
	Q.push(start);
	// Duyet cho den khi Q rong
	while (!Q.empty()) {
		int i = Q.front(); // Lay diem dau trong hang doi
		Q.pop(); // Pop dinh ra khoi hang doi
		// Danh dau dinh moi lay ra
		colour[i] = 1;

		for (int j = 0; j < n; j++)
		{
			// Neu nhu co succs(i) && dinh j chua duoc danh dau
			if (G[i][j] != 0 && colour[j] == 0) {
				// Luu lai con tro quay lui de truy vet
				backPointers[j] = i;
				// Them dinh j vao Queue
				Q.push(j);
				// Danh dau dinh i
				colour[j] = 1;
			}
		}
	}

	// Neu dinh goal duoc danh dau thi tuc la co ket qua
	if (colour[goal]) {
		// Duyet nguoc
		int i = goal;
		
		do {
			cout << i << " "; // In dinh nay
			i = backPointers[i]; // Quay lui nguoc ve dinh tro toi
		} while (i != -1); // Neu duyet den start thi ket thuc
		
	}
	else
		cout << "Cannt find a result!";
}

int main() {

	input();
	
	BFS();


	return 0;
}
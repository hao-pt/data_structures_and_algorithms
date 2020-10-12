#include <iostream>
#include <stack>
using namespace std;

int **G; // Matrix do thi
int n; // So luong dinh (Trang thai)
int *backPointers; // Con tro quay lui
int start, goal; // Diem xuat phat va dich
int *color; // Danh dau cac diem dang duyet

void input() {
	freopen("input.txt", "rt", stdin);
	// Nhap n, start, end
	cin >> n >> start >> goal;
	// Khoi tao do thi, con tro quay lui va bang danh dau
	G = new int*[n];
	backPointers = new int[n];
	color = new int[n];

	// Khoi tao cac phan tu bang 0
	for (int i = 0; i < n; i++) {
		backPointers[i] = 0;
		color[i] = 0;
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

// Deep-first search
void DFS_recursion(int i) {
	if (i == goal) {
		int pos = i;
		do {
			cout << pos << " ";
			pos = backPointers[pos];
		} while (pos != - 1);
		cout << endl;
		exit(0);
	}
	

	for (int j = 0; j < n; j++)
	{
		if (G[i][j] != 0) {
			backPointers[j] = i;
			DFS_recursion(j);
			backPointers[j] = 0;
		}
	}
}

// Path checking DFS
// Ý tưởng: Không gọi lại trạng thai đã duyệt qua để tranh cac chu trinh lap vo han lan
void PC_DFS(int i) {
	if (i == goal) {
		int pos = i;
		do {
			cout << pos << " ";
			pos = backPointers[pos];
		} while (pos != -1);
		cout << endl;
		exit(0);
	}

	for (int j = 0; j < n; j++)
	{
		if (G[i][j] != 0 && color[j] != 1) {
			backPointers[j] = i;
			color[j] = 1;
			DFS_recursion(j);
			backPointers[j] = 0;
			color[j] = 0; // Neu MEM-DFS thi bo dong nay
		}
	}
}

// Deep-first search
bool DFS_recursion_limit(int i, int limit) {
	if (i == goal) {
		return true;
	}

	if (limit <= 0)
		return false;

	for (int j = 0; j < n; j++)
	{
		if (G[i][j] != 0 && DFS_recursion_limit(j, limit - 1)) {
			backPointers[j] = i;
			return true;
		}
	}

	return false;
}

// Iterative deepening search
bool IDS(int start, int maxDepth) {
	for (int i = 1; i < maxDepth; i++)
	{
		if (DFS_recursion_limit(start, i)) {
			int pos = goal;
			do {
				cout << pos << " ";
				pos = backPointers[pos];
			} while (pos != -1);
			cout << endl;
			
			return true;
		}
	}
	return false;
}

//void DFS_stack() {
//	// Khoi tao stack luu cac trang thai ban dau
//	stack<int> state;
//	// Them dinh start vao stack
//	state.push(start);
//	// Tim cac expand cua dinh start
//	// stack theo co che LIFO nen ta phai duyet tu duoi len
//	for (int j = n - 1; j >= 0; j--)
//	{
//		if (G[start][j] != 0)
//			state.push(j);
//	}
//	
//	int previous = start; // Luu vi tri cua dinh da duyet truoc do
//
//	while (!state.empty() && state.top() != goal) {
//		// Lay dinh tren top cua stack
//		int i = state.top();
//		
//		int flag = 0; // Kiem tra xem i co successor khong?
//		// Co: thi duyet tiep
//		// Khong: pop ra khoi stack
//		// Tim cac expand cua i
//		
//		// Luu lai vi tri de quay lui
//		backPointers[i] = previous;
//		// Cap nhat previous
//		previous = i;
//
//		for (int j = n - 1; j >= 0; j--) {
//			if (G[i][j] != 0 && previous != j) {
//				flag = 1;
//				state.push(j);
//				
//			}
//
//		}
//
//		// Neu dinh i khong co successor
//		// Ta se pop i ra khoi stack
//		// Luu dinh i vao previous de duyet sang nhanh khac
//		// Xoa luon ca con tro quay lui cua i
//		if (flag == 0) {
//			state.pop();
//			previous = i;
//			backPointers[i] = 0;
//		}
//	}
//	
//	if (state.empty())
//		cout << "Can find a result!\n";
//	else {
//		int pos = goal;
//		do {
//			cout << pos << " ";
//			pos = backPointers[pos];
//		} while (pos != -1);
//		cout << endl;
//	}
//
//}

int main() {
	input();
	//// Dung de qui
	//DFS_recursion(start);
	/*PC_DFS(start);*/
	IDS(start, 6);
	return 0;
}
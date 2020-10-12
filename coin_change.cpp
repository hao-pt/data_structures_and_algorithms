#include <iostream>
using namespace std;

int** arr2D_alloc(int m, int n){
	int *data = NULL, **a = NULL;
	void *buf = NULL;
	size_t sz1, sz2;
	sz1 = m*sizeof(int*);
	sz2 = m*size_t(n)*sizeof(int);
	buf = calloc(sz1 + sz2, 1);
	if (buf == NULL)
		return NULL;
	a = (int**)buf;
	a[0] = data = (int*)((char*)buf + sz1);
	for (int i = 1; i < m; i++)
	{
		data += n; a[i] = data;
	}
	return a;
}
void arr2D_free(int **a){
	if (a != NULL)
		free(a);
}
void arr1D_push_back(int *&a, int &n, int x){
	int m = n + 1;
	int *anew = NULL;
	anew = (int*)realloc(a, m *sizeof(int));
	if (anew != NULL){
		anew[n] = x;
		a = anew;
		n = m;
	}
}
void arr1D_pop_back(int *&a, int &n, int &x){
	x = a[n - 1];
	int m = n - 1;
	if (m == 0){
		a = NULL;
		n = 0;
		return;
	}
	int *anew = NULL;
	anew = (int*)realloc(a, m *sizeof(int));
	if (anew != NULL){
		a = anew;
		n = m;
	}
}
int coins_change(int a[], int m, int n){
	int **table = arr2D_alloc(m + 1, n + 1);
	// base case: no money to change so number of way is 1
	for (int i = 0; i <= m; i++)
	{
		table[i][0] = 1;
	}
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++){
			// count of solution include a[i]:
			if (j >= a[i - 1])
				table[i][j] = table[i - 1][j] + table[i][j - a[i - 1]];
			// count of solution exclude a[i]:
			else
				table[i][j] = table[i - 1][j];
		}
	}
	return table[m][n]; // The number of distinct sets
}
// optimal - DP solution
int coin_change_on_space(int a[], int m, int n){
	int *table = new int[n + 1];
	memset(table, 0, (n + 1)*sizeof(int));
	// base case
	table[0] = 1;
	for (int i = 0; i < m; i++)
	{
		for (int j = 1; j < n + 1; j++){
			if (j >= a[i])
				table[j] += table[j - a[i]];
		}
	}
	return table[n];
}
void print_actual_solution(int a[], int m, int total, int pos, int *&result, int n);
void print_coins_change_solution(int a[], int m, int total){
	int *result = NULL, n = 0;
	print_actual_solution(a, m, total, 0, result, n);
}
void print_actual_solution(int a[], int m, int total, int pos, int *&result, int n){
	int x;
	if (total == 0){
		for (int i = 0; i < n; i++)
		{
			cout << *(result + i) << " ";
		}
		cout << endl;
	}
	else{
		for (int i = 0; i < m; i++)
		{
			if (total >= a[i]){
				arr1D_push_back(result, n, a[i]);
				print_actual_solution(a, m, total - a[i], i, result, n);
				arr1D_pop_back(result, n, x);
			}
		}
	}
}
int main(){
	int a[] = { 1, 2};
	int total, m = sizeof(a)/sizeof(a[0]);
	cout << "Enter the total of coins you want to change: ";
	cin >> total;
	cout << "The number of method to change coins: ";
	cout << coins_change(a, m, total) << endl;
	cout << coin_change_on_space(a, m, total) << endl;
	cout << "The method of changing coins actually print all distinct sets: " << endl;
	print_coins_change_solution(a, m, total);
	return 0;
}
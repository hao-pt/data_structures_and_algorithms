#include <iostream>
using namespace std;

void arr2D_alloc(int **&a, int m, int n) {
	if (m <= 0 || n <= 0)
		return;
	void *buffer = NULL; int *data = NULL;
	size_t sz1, sz2;
	sz1 = m * sizeof(int*);
	sz2 = m*(size_t)n * sizeof(int);
	buffer = calloc(sz1 + sz2, 1);
	if (buffer == NULL)
		return;
	a = (int**)buffer;
	a[0] = data = (int*)((char*)buffer + sz1);
	for (int i = 1; i < m; i++)
	{
		data += n; a[i] = data;
	}
}
int mod(int x, int j, int k) {
	if (x > j)
		return j - x + k;
	return j - x;
}
void traceAndPrintResult(int **T, int *a, int n, int k);
int build_solution_table(int *a, int n, int k) {
	int **T = NULL;
	arr2D_alloc(T, n + 1, k);
	// base case
	for (int i = 1; i < k; i++)
		T[0][i] = INT_MIN;
	T[0][0] = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			T[i][j] = T[i - 1][j] > T[i - 1][mod(a[i], j, k)] + 1 ? T[i - 1][j] : T[i - 1][mod(a[i], j, k)] + 1;
		}
	}
	traceAndPrintResult(T, a, n, k);
	return T[n][0]; // largest length of subsequence
}
void traceAndPrintResult(int **T, int *a, int n, int k) {
	cout << "The largest length of subsequence is " << T[n][0];
	int i = n, j = 0;
	while (i) {
		if (T[i - 1][mod(a[i], j, k)] > 0 && T[i][j] > T[i - 1][mod(a[i], j, k)]) {
			cout << a[i] << " ";
			j = mod(a[i], j, k);
		}
		i--;
	}
}
int main() {
	int *a, n;
	printf("Enter n = ");
	scanf("%d", &n);
	a = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 100;
	}
	printf("Array after inputting: ");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
	int k;
	printf("Enter k = ");
	scanf("%d", &k);
	printf("The largest length of subsequence has maximum sum mod %d: %d", k, build_solution_table(a, n, k));

	return 0;
}
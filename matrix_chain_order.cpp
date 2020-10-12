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
int matrix_chain_order(int a[], int n, int **&s){
	int **temp = arr2D_alloc(n, n);
	s = arr2D_alloc(n, n);
	int j, q;
	for (int l = 2; l < n; l++)
	{
		for (int i = 1; i < n - l + 1; i++)
		{
			j = l + i - 1;
			temp[i][j] = INT_MAX; // set infinite
			for (int k = i; k < j; k++)
			{
				q = temp[i][k] + temp[k+1][j] + a[i-1] * a[k] * a[j];
				if (q < temp[i][j]){
					temp[i][j] = q; // update new value
					s[i][j] = k; // save value so as to trace and print result
				}
			}
		}
	}
	return temp[1][n - 1]; // the best result
}
void trace_and_print_result(int **s, int i, int j){
	if (i == j)
		cout << "A" << i;
	else{
		cout << "(";
		trace_and_print_result(s, i, s[i][j]);
		trace_and_print_result(s, s[i][j] + 1, j);
		cout << ")";
	}
}
int main(){
	int a[] = { 2,3,6,4,5 };
	int n = sizeof(a) / sizeof(a[0]);
	int **s = NULL;
	int d = matrix_chain_order(a, n, s);
	cout << "The best way to multiply scalar matrix is " << d << endl;
	trace_and_print_result(s, 1, n - 1);
	arr2D_free(s);
	return 0;
}
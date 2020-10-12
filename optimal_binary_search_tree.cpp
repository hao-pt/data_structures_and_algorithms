#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/optimal-binary-search-tree-dp-24/

int **arr2D_alloc(int m, int n){
	if (m == 0 || n == 0)
		return NULL;
	int**a = NULL, *data = NULL;
	void *buff = NULL;
	size_t sz1, sz2;
	sz1 = m*sizeof(int*);
	sz2 = m*(size_t)n*sizeof(int);
	buff = calloc(sz1 + sz2, 1);
	if (buff == NULL)
		return NULL;
	a = (int**)buff;
	a[0] = data = (int*)((char*)buff + sz1);
	for (int i = 1; i < m; i++)
	{
		data += m;
		a[i] = data;
	}
	return a;
}
int binary_search(int *a, int n, int x){
	int left = 0, right = n - 1;
	int mid;
	while (left <= right){
		mid = left + (right - left) / 2;
		if (a[mid] == x)
			return mid;
		if (a[mid] > x)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}
int recur_binary_search(int *a, int n, int x, int left, int right){
	if (left > right)
		return -1;
	int mid = left + (right - left) / 2;
	if (a[mid] == x)
		return mid;
	else if (a[mid] > x)
		return recur_binary_search(a, n, x, left, mid - 1);
	else
		return recur_binary_search(a, n, x, mid + 1, right);
}
int recur_opt_cost(int *k, int *freq, int n, int left, int right, int level);
int recur_opt_binary_search(int *key, int *freq, int n){
	return recur_opt_cost(key, freq, n, 0, n - 1, 1);
}
int recur_opt_cost(int *k, int *freq, int n, int left, int right, int level){
	if (left > right)
		return 0;
	int min_cost = INT_MAX;
	for (int i = left; i <= right; i++)
	{
		int val = recur_opt_cost(k, freq, n, left, i - 1, level + 1) +
			recur_opt_cost(k, freq, n, i + 1, right, level + 1) + level*freq[i];
		if (val < min_cost)
			min_cost = val;
	}
	return min_cost;
}
int get_sum(int *f, int i, int j){
	int s = 0;
	while (i <= j){
		s += f[i];
		i++;
	}
	return s;
}
void trace_and_print_root(int *key, int **r, int i, int j);
// using DP to solve this problem
int opt_binary_search(int *key, int *freq, int n){
	int **table = arr2D_alloc(n, n);
	int **r = arr2D_alloc(n, n); // store the root 
	// base case: 
	for (int i = 0; i < n; i++){
		table[i][i] = freq[i];
		r[i][i] = i;
	}
	int sum = 0;
	// build table solution
	for (int l = 2; l <= n; l++){
		for (int i = 0; i < n - l + 1; i++)
		{
			int j = l + i - 1;
			sum = get_sum(freq, i, j);
			table[i][j] = INT_MAX;
			// Donald Knuth: r[i][j-1] <= r[i][j] <= r[i + 1][j]. O(n2) Instead of browsing from i to j, we only browse from r[i][j-1] to r[i + 1][j]
			for (int k = r[i][j - 1]; k <= r[i + 1][j]; k++)
			{
				int val = (k - 1 < i ? 0 : table[i][k - 1]) + (k + 1 > j ? 0 : table[k + 1][j]) + sum;
				if (val < table[i][j]){
					table[i][j] = val;
					r[i][j] = k;
				}
			}
		}
	}
	trace_and_print_root(key, r, 0, n - 1);
	cout << endl;
	return table[0][n - 1];
}
void trace_and_print_root(int *key, int **r, int i, int j){
	if (i > j)
		return;
	cout << "(";
	trace_and_print_root(key, r, i, r[i][j] - 1); // print left subtree
	cout << key[r[i][j]]; // print root
	trace_and_print_root(key, r, r[i][j] + 1, j); // print right subtree
	cout << ")";
}
int main(){
	int key[] = { 1, 2, 3, 4, 5, 6 };
	int freq[] = { 1, 5, 3, 4, 2, 3 };
	int n = sizeof(key) / sizeof(key[0]);
	int pos = 2;
	cout << "The location of " << pos << " in the array is" << endl;
	cout << binary_search(key, n, pos) << endl;
	cout << recur_binary_search(key, n, pos, 0, n - 1) << endl;
	cout << "The minimum cost is " << endl;
	cout << recur_opt_binary_search(key, freq, n) << endl;
	cout << opt_binary_search(key, freq, n) << endl;
}


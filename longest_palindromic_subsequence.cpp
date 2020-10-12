#include <iostream>
using namespace std;
int **arr2D_alloc(int m, int n){
	if (m <= 0 || n <= 0)
		return NULL;
	int **a = NULL, *data = NULL;
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
		data += m; a[i] = data;
	}
	return a;
}
void trace_and_print_result(char* s, int **t, int m, int n);
int longest_palindromic_subsequence(char *s){
	int len = strlen(s);
	int **table = arr2D_alloc(len, len);
	// length = 1
	for (int i = 0; i < len; i++)
		table[i][i] = 1;
	for (int l = 2; l <= len; l++)
	{
		for (int i = 0; i <= len - l; i++){
			int j = i + l - 1;
			if (s[i] == s[j]){
				if (l == 2)
					table[i][j] = 2;
				else
					table[i][j] = 2 + table[i + 1][j - 1];
			}
			else{
				table[i][j] = (table[i][j - 1] > table[i + 1][j]) ? table[i][j - 1] : table[i + 1][j];
			}
		}
	}
	trace_and_print_result(s, table, 0, len - 1);
	return table[0][len - 1];
}
void trace_and_print_result(char* s, int **t, int m, int n){
	int len = t[0][n];
	char *palindromic = new char[len];
	int i = 0;
	while (1){
		if (s[m] == s[n]){
			palindromic[i] = palindromic[len - 1 - i] = s[m];
			if (m == n)
				break;
			m++; n--;
			i++;
		}
		else if (t[m][n - 1] > t[m + 1][n]){
			n--;
		}
		else
			m++;
	}
	palindromic[len] = 0;
	printf("%s\n", palindromic);
}
int main(){
	char s[] = "abfdba";
	int n = longest_palindromic_subsequence(s);
	printf("The longest length of palindromic subsequence is %d\n", n);
	return 0;
}
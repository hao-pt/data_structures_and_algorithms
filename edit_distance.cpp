#include <iostream>
#include <string.h>
using namespace std;
int **arr2D_alloc(int m, int n){
	if (m <= 0 || n <= 0)
		return NULL;
	int **a = NULL, *data = NULL;
	void *buf = NULL;
	size_t sz1, sz2;
	sz1 = m*sizeof(int*);
	sz2 = m*(size_t)n*sizeof(int);
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
int min(int a, int b, int c){
	int min = a;
	if (min > b)
		min = b;
	if (min > c)
		min = c;
	return min;
}
/*
Edit distance includes 3 way to edit two string has the same str1, str2
- Delete i: table[i - 1][j]
- Insert j into str1: table[i][j - 1]
- Replace i by j: table[i-1][j-1]
*/
void Insert(char *s, int pos, char c){
	int len = strlen(s);
	for (int i = len + 1; i > pos; i--)
	{
		s[i] = s[i - 1];
	}
	s[pos] = c;
}
void Delete(char *s, int pos){
	int len = strlen(s);
	for (int i = pos + 1; i < len; i++)
	{
		s[pos - 1] = s[pos];
	}
}
void Replace(char *s, int pos, char c){
	s[pos] = c;
}
void trace_and_print_result(char* str1, char* str2, int **table, int m, int n);
int edit_distance(char *str1, char *str2){
	int len1 = strlen(str1), len2 = strlen(str2);
	int **table = arr2D_alloc(len1 + 1, len2 + 1);
	// base case
	for (int i = 0; i <= len1; i++)
		table[i][0] = i;
	for (int j = 0; j <= len2; j++)
		table[0][j] = j;
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (str1[i - 1] == str2[j - 1])
				table[i][j] = table[i - 1][j - 1];
			else{
				table[i][j] = min(table[i - 1][j], table[i][j - 1], table[i - 1][j - 1]) + 1;
			}
		}
	}
	trace_and_print_result(str1, str2, table, len1, len2);
	return table[len1][len2];
}
// optimal- DP to solve this problem 
int optimal_edit_distance(char *str1, char *str2){
	int len1 = strlen(str1), len2 = strlen(str2);
	int *table = new int[len2 + 1];
	// idea: de y ta thay chi su dung 3 gia tri de giai bai toan do la left, dig, cur
	// base case
	for (int j = 0; j <= len2; j++)
		table[j] = j;
	int left = 0, diag = 0, cur = 0;
	for (int i = 1; i <= len1; i++)
	{
		left = i;
		diag = i - 1;
		for (int j = 1; j <= len2; j++)
		{
			if (str1[i - 1] == str2[j - 1])
				table[j] = diag;
			else{
				cur = table[j];
				table[j] = min(left, diag, cur) + 1;
			}
			left = table[j];
			diag = cur;
		}
	}
	return table[len2];
}
void trace_and_print_result(char* str1, char* str2, int **table, int m, int n){
	while (m || n){
		if (str1[m - 1] == str2[n - 1]){
			m--;
			n--;
		}
		else {
			cout << str1 << " -> ";
			if (table[m][n] == table[m - 1][n - 1] + 1){
				cout << "Replace(" << m - 1 << ", " << str2[n - 1] << ")";
				Replace(str1, m - 1, str2[n - 1]);
				m--; n--;
			}
			else if (table[m][n] == table[m][n - 1] + 1){
				cout << "Insert(" << m - 1 << ", " << str2[n - 1] << ")";
				Insert(str1, m, str2[n - 1]);
				n--;
			}
			else{
				cout << "Delete(" << m - 1 << "): " << str1[m - 1];
				Delete(str1, m - 1);
				m--;
			}
			cout << " -> " << str1 << endl;
		}
	}
}
int main(){
	char s1[10000] = "FOOD"; char s2[10000] = "MONEY";
	char *dup1 = strdup(s1); char *dup2 = strdup(s2);
	cout << "The minimum way to edit distance: " << endl;
	cout << edit_distance(s1, s2) << endl;
	cout << optimal_edit_distance(dup1, dup2) << endl;
	return 0;
}
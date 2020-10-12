#include <iostream>
using namespace std;
int minimum_coins(int a[], int n, int v, int *&t){
	int *s = new int[v + 1];
	t = new int[v + 1];
	for (int i = 1; i <= v; i++)
		s[i] = INT_MAX;
	s[0] = 0; // base case
	for (int i = 1; i <= v; i++)
	{
		for (int j = 0; j < n; j++){
			if (a[j] <= i){ // test case
				int sub_res = s[i - a[j]];
				if (sub_res != INT_MAX && s[i] > sub_res + 1){
					s[i] = sub_res + 1;
					t[i] = j;
				}
			}
		}
	}
	return s[v];
}
void trace_and_print_result(int a[], int t[], int n){
	int i = n;
	printf("Coins used to from total: ");
	while (i != 0){
		cout << a[t[i]] << " ";
		i = i - a[t[i]];
	}
	cout << endl;
}
int main(){
	int a[] = {1, 2, 5};
	int n = sizeof(a) / sizeof(a[0]);
	int v = 4;
	int *t = NULL;
	int min = minimum_coins(a, n, v, t);
	cout << "Minimum coins is " << min << endl;
	trace_and_print_result(a, t, v);
	return 0;
}
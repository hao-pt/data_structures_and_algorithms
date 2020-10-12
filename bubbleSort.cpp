#include <iostream>
using namespace std;
void bubble_sort(int *a, int n){
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j > i; j--)
			if (a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
	}
}
void arr1D_output(int *a, int n){
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
int main(){
	int a[] = { 5, 1, 7, 3, 2, 7, 8, 3 };
	int b[] = { 9, 7, 5, 4, 8, 1, 6, 7, 3 };
	int n = sizeof(a) / sizeof(a[0]);
	int m = sizeof(b) / sizeof(b[0]);
	bubble_sort(a, n);
	arr1D_output(a, n);
	bubble_sort(b, m);
	arr1D_output(b, m);
	return 0;
}
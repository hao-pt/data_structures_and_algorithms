#include <iostream>
using namespace std;
void insertion_sort(int *a, int n){
	for (int i = 1; i < n; i++)
	{
		int j = i - 1;
		int t = a[i];
		while (j > 0 && a[j] > t){ // kiem tra co nghich the khong, co thi doi cai phan tu truoc do sang phai
			a[j++] = a[j];
			j--;
		}
		a[j + 1] = t; // place t into right place
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
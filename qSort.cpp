#include <iostream>
using namespace std;
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller(smaller than pivot)
to left of pivot and all greater elements to right
of pivot */;
int partition(int *a, int low, int high){
	int pivot = a[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (a[j] <= pivot){// if a[j] smaller then pivot place a[j] to left of pivot
			i++; // increment index of smaller element
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[high]); // put pivot to right place
	return i + 1;
}
void quickSort(int *a, int low, int high){
	if (low < high){
		int pi = partition(a, low, high); // pi is partitioning index. so pi is now at right place.
		quickSort(a, low, pi - 1); // test left side
		quickSort(a, pi + 1, high); // test right side
	}
}
void arr1D_output(int *a, int n);
void quickSort2(int *a, int low, int high){
	int i = low, j = high, pivot = a[low + (high - low)/2]; // random selection
	do{
		while (a[i] < pivot) i++; // find the wrong position of element on the left
		while (a[j] > pivot) j--; // find the wrong position of element on the right
		if (i <= j){ // if a wrong pair is found
			swap(a[i], a[j]);
			i++; j--; // increment next index
		}
	} while (i <= j);
	arr1D_output(a, 8);
	/*Arrange the subsequense if there are many elements*/
	if (low < j)
		quickSort2(a, low, j);
	if (i < high)
		quickSort2(a, i, high);
}
void arr1D_output(int *a, int n){
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
int main(){
	/*int a[] = { 5, 1, 7, 3, 2, 7, 8, 3 };
	int b[] = { 9, 7, 5, 4, 8, 1, 6, 7, 3 };
	int n = sizeof(a) / sizeof(a[0]);
	int m = sizeof(b) / sizeof(b[0]);
	quickSort(a, 0, n - 1);
	arr1D_output(a, n);
	quickSort2(b, 0, m - 1);
	arr1D_output(b, m);*/
	int a[] = { 22, 12, 9, 7, 31, 19, 2, 27 };
	quickSort2(a, 0, sizeof(a) / 4 - 1);
	return 0;
}
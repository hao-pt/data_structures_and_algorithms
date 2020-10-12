#include <iostream>
using namespace std;
void mergeArray(int *a, int lo, int mid, int hi){
	int i = lo; // index of first subarray
	int	j = mid + 1; // index of second subarray
	int n1 = mid + 1; // length of first subarray
	int n2 = hi + 1; // length of second subarry
	int n = hi - lo + 1; // length of a[]
	int *b = new int[n]; // Create sub-array for a
	int k = 0; // index of merged array
	// Compare each element in first and second subarray
	while (i < n1 && j < n2){
		if (a[i] < a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	// Copy the remaining elements of first array if there are any elements
	while (i < n1)
		b[k++] = a[i++];
	// Copy the remaining elements of first array if there are any elements
	while (j < n2)
		b[k++] = a[j++];
	// Copy elements after sorting into a[]
	i = lo;
	for (k = 0; k < n; k++)
		a[i++] = b[k];

	delete[] b;
}
void mergeSort(int *a, int lo, int hi){
	if (lo >= hi) 
		return;
	int mid = lo + (hi - lo)/2; // Same as (hi + lo)/2 but avoiding overflow 
	mergeSort(a, lo, mid); // sort left side
	mergeSort(a, mid + 1, hi); // sort right side
	mergeArray(a, lo, mid, hi); // Sort two subarray
}
void arr1D_output(int *a, int n){
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
int main(){
	int a[] = { 9, 7, 5, 4, 8, 1, 6, 7, 3, 11, 2 };
	int n = sizeof(a) / sizeof(a[0]);
	mergeSort(a, 0, n - 1);
	arr1D_output(a, n);
	return 0;
}
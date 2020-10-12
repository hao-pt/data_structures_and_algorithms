#include <malloc.h>
#include <stdio.h>
void show_array(int a[], int n){
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
void longest_increasing_subsequence(int a[], int n){
	int *l = (int*)calloc(n, sizeof(int));
	l[0] = 1;
	int *d = (int*)calloc(n, sizeof(int));
	int lmax, jmax;
	for (int i = 1; i < n; i++){
		lmax = 0;
		jmax = 0;
		for (int j = 0; j < i; j++){
			if (a[i] > a[j] && l[j] > lmax){
				lmax = l[j];
				jmax = j;
			}
		}
		l[i] = lmax + 1;
		d[i] = jmax;
	}
	jmax = 0;
	for (int i = 1; i < n; i++){
		if (l[i] > l[jmax])
			jmax = i;
	}
	show_array(a, n);
	show_array(l, n);
	show_array(d, n);
	int m = l[jmax];
	int *b = (int*)calloc(m, sizeof(int));
	int idx = m - 1;
	while (1){
		int i = jmax;
		b[idx--] = a[i];
		jmax = d[i];
		if (jmax == 0){
			b[idx] = a[jmax];
			break;
		}
	}
	show_array(b, m);
}

int main(){
	int a[] = { 8, 3, 9, 1, 7, 6, 2, 10 }; 
	int n = sizeof(a) / sizeof(a[0]);
	longest_increasing_subsequence(a, n);

}
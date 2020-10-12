#include <stdio.h>
/*
Ta van co n vat, wmax khoi luong toi da de cho vao balo. Nhung so luong cua 1 mon vat khong han che
Ta co: F[n][wmax]: gia tri lon nhat cua cac mon hang da cho vao balo
Ta co 2 TH:
TH1: Kh nhan goi hang thu i: F[i][j] = F[i][j-1];
TH2: Nhan goi hang thu i: F[i][j] = max(F[i,j], F[i-1][j-k*w[i]] + k*v[i]); 
voi k la so luong goi hang thu i da chon (1 <= k <= j div w[i])
Luu y: Can phai them mang cout so luong mon hang thu i duoc chon c[i][j] de truy vet
CSQHD: F[0][j] = 0
*/
#define MAX 100
int w[MAX], v[MAX], F[MAX][MAX], c[MAX][MAX];
void arr1D_input(int *a, int n){
	for (int i = 0; i < n; i++)
	{
		scanf("%d", a + i);
	}
}
void build_solution_table(int n, int wmax){
	for (int j = 0; j <= wmax; j++) // Base case
		F[0][j] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= wmax; j++){
			F[i][j] = F[i - 1][j];
			if (j >= w[i - 1]){
				for (int k = 1; k <= j/w[i-1]; k++)
				{
					if (F[i][j] < F[i - 1][j - k*w[i - 1]] + k*v[i - 1]){
						F[i][j] = F[i - 1][j - k*w[i - 1]] + k*v[i - 1];
						c[i][j] = k;
					}
				}
			}
		}
	}
}
void trace_and_print_results(int n, int wmax){
	printf("Max value: %d\n", F[n][wmax]);
	int i = n, j = wmax;
	while (i){
		if (c[i][j]){
			printf("%d(%d times) ", i, c[i][j]);
			j -= c[i][j]*w[i - 1];
		}
		i--;
	}
}
int main(){
	int n, wmax;
	printf("Enter quantity of the item and the maximum weight to put in the balo: ");
	scanf("%d%d", &n, &wmax);
	printf("Enter the weight of the item: ");
	arr1D_input(w, n);
	printf("Enter the value of the item: ");
	arr1D_input(v, n);
	build_solution_table(n, wmax);
	trace_and_print_results(n, wmax);
	printf("\n");
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= wmax; j++){
			printf("%2d ", F[i][j]);
		}
		printf("\n");
	}
}
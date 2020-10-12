/*
Ta co n vat va Wmax
Ta co: w[]: mang khoi luong && v[]: mang gia tri
Ta co gia tri lon nhat dat duoc la F[n][Wmax] thoa dk bai toan
Ta se co 2 TH de xet cho F[i][j] voi 0 < i <= n, 0 <= j <= Wmax
TH1: Khong nhan mon hang i thi ta se co F[i][j] = F[i-1][j];
TH2: Nhan mon hang i: F[i][j] = F[i-1][j-w[i]] + v[i];
~~~Co so quy hoạch dong~~~
F[0][j] = 0; vi khi kh chon mon do nao thi gia tri se la 0
*/
#include <stdio.h>
#define MAX 100
int w[MAX], v[MAX], F[MAX][MAX];
void arr1D_input(int *a, int n){
	for (int i = 0; i < n; i++)
	{
		scanf("%d", a + i);
	}
}
void build_solution(int n, int wmax){
	for (int j = 0; j < wmax; j++)
		F[0][j] = 0;
	int temp;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= wmax; j++){
			F[i][j] = F[i - 1][j]; // gia su ban dau khong lay mon hang thu i
			temp = F[i - 1][j - w[i - 1]] + v[i - 1];
			if (j >= w[i - 1] && F[i - 1][j] < temp) // dieu kien de lay mon hang thu i
				F[i][j] = temp;

		}
	}
}
void trace_and_print_solution(int n, int wmax){
	// F[n][wmax]: gia tri lon nhat cua cac mon hang ta da lay
	printf("Max value: %d\n", F[n][wmax]);
	int i = n, j = wmax;
	while (i){
		if (F[i][j] != F[i-1][j]){
			printf("%d ", i);
			j = j - w[i - 1];
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
	build_solution(n, wmax);
	trace_and_print_solution(n, wmax);
	printf("\n");
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= wmax; j++){
			printf("%2d ", F[i][j]);
		}
		printf("\n");
	}

}
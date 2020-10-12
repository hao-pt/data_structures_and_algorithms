#include <stdio.h>
#define MAX 100
/*
	Dung mang 2d de giai quyet cac bai toan co so: s[n+1][sum + 1]
	Co so QHD: s[i][0] = 1; // do 0 + voi so gi cung bang so do
	s[0][j] = 0;
	Ton tai tap con S \ {x} ma S = T - x;
	Ton tai tap con S \ {x} ma S = T;
	3 TH xay ra:
	- TH1 : false if T < 0 || i < 0
	- TH2: true if T = 0
	- s[i][j] = s[i-1][j] V s[i-1][j - x[i]]
	*/
void trace_and_print_solution(int s[][MAX], int n, int T, int x[]);
void build_solution(int x[], int n, int T){
	int s[MAX][MAX] = { 0 };
	for (int i = 0; i <= n; i++)
		s[i][0] = 1;
	for (int j = 1; j <= T; j++)
		s[0][j] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= T; j++){
			s[i][j] = s[i - 1][j]; // gia su khong chon phan tu thu i
			for (int t = j; t <= T && j >= x[i - 1]; t++)
			{
				s[i][j] = s[i - 1][j] + s[i - 1][j - x[i - 1]] ? 1 : 0;
			}
		}
	}
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= T; j++)
			printf("%d ", s[i][j]);
		printf("\n");
	}
	trace_and_print_solution(s, n, T, x);
}
void trace_and_print_solution(int s[][MAX], int n, int T, int x[]){
	if (s[n][T]){
		printf("Subset sum has existed\n");
		int i = n, j = T;
		while (i){
			if (s[i - 1][j] != s[i][j]){
				printf("%d ", x[i - 1]);
				j -= x[i - 1];
			}
			i--;
		}
	}
	else
		printf("Subset sum hasn't existed\n");
}
int main(){
	int a[100], n;
	printf("Enter n = ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Enter a[%d] = ", i);
		scanf("%d", a + i);
	}
	build_solution(a, n, 10);
	return 0;
}
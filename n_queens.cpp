#include <stdio.h>
#include <stdlib.h>
void print_result(int S[], int n){
	for (int i = 1; i <= n; i++){
		printf("[%d][%d]\n", i, S[i]);
	}
}
void n_Queen(int S[], int n, int r){
	int flag;
	if (r == n + 1){
		print_result(S, n);
		exit(0);
	}
	for (int j = 1; j <= n; j++){ // quet cac cot kha di
		flag = 1;
		for (int i = 1; i <= r - 1 && flag; i++){ // kiem tra cac dong tu 1 -> r - 1
			if (S[i] == j || S[i] == j + r - i || S[i] == j - r + i)
				flag = 0;
		}
		if (flag){
			S[r] = j;
			n_Queen(S, n, r + 1);
		}
	}
}
int main(){
	int S[9] = {0};
	n_Queen(S, 8, 1);
}
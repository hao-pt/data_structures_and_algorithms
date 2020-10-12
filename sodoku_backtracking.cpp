#include <stdio.h>
#include <stdlib.h>
void print_solution(int s[][9]){
	for (int i = 0; i < 9; i++)
	{
		if (i % 3 == 0)
			printf("--------------------\n");
		for (int j = 0; j < 9; j++){
			if (j % 3 == 0)
				printf("|");
			printf("%d ", s[i][j]);
			
		}
		printf("\n");
	}
}
bool feasible(int s[][9], int x, int y, int k){
	for (int j = 0; j < 9; j++)
	{
		if (s[x][j] == k)
			return 0;
	}
	for (int i = 0; i < 9; i++)
	{
		if (s[i][y] == k)
			return 0;
	}
	int a = x / 3, b = y / 3;
	for (int i = 3 * a; i < 3 * a + 3; i++)
	{
		for (int j = 3 * b; j < 3 * b + 3; j++){
			if (s[i][j] == k)
				return 0;
		}
	}
	return 1;
}
void solve_soduku(int a[][9], int x = 0, int y = 0);
void solve_soduku(int a[][9], int x, int y){
	if (y == 9){
		if (x == 8){
			print_solution(a);
			exit(0);
		}
		else
			solve_soduku(a, x + 1, 0);
	}
	else if (a[x][y] == 0){
		for (int i = 1; i <= 9; i++)
		{
			if (feasible(a, x, y, i)){
				a[x][y] = i;
				solve_soduku(a, x, y + 1);
				a[x][y] = 0;
			}
		}
	}
	else
		solve_soduku(a, x, y + 1);
}
int main(){
	int a[9][9];
	FILE *fp = fopen("soduku.txt", "rt");
	if (fp){
		int x;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++){
				fscanf(fp, "%d ", &x);
				a[i][j] = x;
			}
		}
		solve_soduku(a);
		fclose(fp);
	}
}
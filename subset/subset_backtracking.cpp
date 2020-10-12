#include <stdio.h>
bool check_subset_sum(int *a, int n, int sum){
	if (sum == 0)
		return 1;
	if (sum < 0 || n == 0)
		return 0;
	if (check_subset_sum(a, n - 1, sum - a[n - 1]))
		return 1;
	if (check_subset_sum(a, n - 1, sum))
		return 1;
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
	bool t = check_subset_sum(a, n, 7);
	if (t)
		printf("Subset sum exists!\n");
	else
		printf("Subset sum doesn't exist!\n");
}
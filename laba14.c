#include <stdio.h>

int main()

{
	int n;
	scanf("%d", &n);
	long long v[n][n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%lld", &v[i][j]);
		}
	}
	int i, j, k;
	for (k = 0; k < n / 2; k++)

	{
		for (j = k; j <= n - k - 1; j++)
			printf("%lld ", v[k][j]);
		for (i = k + 1; i < n - k; i++)
			printf("%lld ", v[i][n - k - 1]);

		for (j = n - k - 2; j >= k; j--)
			printf("%lld ", v[n - k - 1][j]);
		for (i = n - k - 2; i >= k + 1; i--)
			printf("%lld ", v[i][k]);
	}
	if (n % 2 == 1)
		printf("%lld ", v[n / 2][n / 2]);
	return 0;
}
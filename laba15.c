#include <stdio.h>
#include <limits.h>
int main()
{
	long long n, m, min = LLONG_MAX;
	scanf("%lld %lld", &n, &m);
	long long v[n][m], z[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%lld", &v[i][j]);
			if (min > v[i][j])
			{
				min = v[i][j];
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		z[i] = 0;
		for (int j = 0; j < m; j++)
		{
			if (min == v[i][j])
				z[i] = 1;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (z[i] == 1)
			for (int j = 0; j < m / 2; j++)
			{
				int b = v[i][j];
				v[i][j] = v[i][m - j - 1];
				v[i][m - j - 1] = b;
			}
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%lld ", v[i][j]);
		printf("\n");
	}
	return 0;
}
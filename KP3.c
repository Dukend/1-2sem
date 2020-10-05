#include <stdio.h>
#include <math.h>
double eps()
{
	double eps = 1;
	while (1 + (eps / 2) != 1)
		eps /= 2;
	return eps;
}

int main()
{
	double a = 0.0, b = 0.5;
	long long n, k = 1;
	printf("delta = EPS * K   k = ");
	scanf("%lld", &k);
	printf("How much to divide the decision?   n = ");
	scanf("%lld", &n);
	double delta = eps() * k;
	printf("delta = %15e\n------------------------------------------------------------------------\n", delta);
	printf("  x        f(x)              Taylor         iteration    difference\n");
	for (int i = 0; i <= n; i++)
	{
		double x = a + i / (double)n * (b - a);
		double sum = 0, prevx = 1;
		long long prev3 = 3, count = 0;

		for (int j = 1; j <= 100; j++)
		{
			double next = -1 * prevx * (1 + (double)2 / prev3);
			sum += next;
			if (abs(next) < delta)
			{
				count = j;
				break;
			}
			prev3 *= 3, prevx *= x;
		}
		double func = (3 * x - 5) / (x * x - 4 * x + 3);
		printf("  %.4f   %.10lf    %.10lf     %lld      %15e\n",
			   x, func, sum, count, func - sum);
	}
	printf("------------------------------------------------------------------------\n");
	return 0;
}

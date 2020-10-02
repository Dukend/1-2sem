#include <stdio.h>
#include <math.h>

typedef struct
{
	double x;
	int iters;
} results;

double f22(double x)
{
	return acos(x) - sqrt(1 - 0.3 * pow(x, 3));
}

double f23(double x)
{
	return 3 * x - 4 * log(x) - 5;
}

double eps()
{
	double eps = 1.0;
	while (1.0 + (eps / 2.0) != 1)
		eps /= 2.0;
	return eps;
}
/////////////////////////////
double df(double (*f)(double), double x)
{
	double i = pow(2, -26) * fmax(abs(x), 1);
	return (f(x + i) - f(x - i)) / (2 * i);
}

double ddf(double (*f)(double), double x)
{
	double i = pow(2, -13) * fmax(abs(x), 1);
	return (f(x + i) - 2 * f(x) + f(x - i)) / (i * i);
}
/////////////////////////
results diho(double (*f)(double), double a, double b, double delta)
{
	double c;
	results res = {0, 0};
	while (b - a > delta)
	{
		if (f(a) * f(b) > 0)
			return res;
		c = (a + b) / 2;
		if (f(a) * f(c) < 0)
			b = c;
		else
			a = c;
		res.iters++;
	}
	res.x = (a + b) / 2;
	return res;
}

results iteration(double (*f)(double), double a, double b, double delta)
{
	double x0, x1 = (a + b) / 2;
	results res;
	res.iters = 0;
	delta = 0.00000001;
	do
	{
		if (fabs(df(f, x1)) >= 1)
			return res;
		x0 = x1;
		x1 = f(x1);
		res.iters++;
	} while (fabs(x0 - x1) > delta);
	res.x = x1;
	return res;
}

results newtons(double (*f)(double), double a, double b, double delta)
{
	results res = {0, 0};
	double x = .5 * (a + b);
	while (fabs(f(x) / df(f, x)) >= delta)
	{
		x -= f(x) / df(f, x);
		res.x = x;
		res.iters++;
	}
	return res;
}
////////////////////////////////////
int main()
{
	double a1 = 0, b1 = 1, a2 = 2, b2 = 4;
	double e = eps();
	results dih, iter, newton;
	/////////////////
	printf("arccos(x) - sqrt(1 - 0.3x^3)\n");
	/////////////////
	printf("    x ≈ 0.5629\n");
	/////////////////
	printf("%s%10s | %8s |\n", "Метод    |", "  корень  ", "итерации");
	dih = diho(f22, a1, b1, e);
	iter = iteration(f22, a1, b1, e);
	newton = newtons(f22, a1, b1, e);
	printf("Дихотомия|%10lf | %8d |\n", dih.x, dih.iters);
	printf("Итераций |%10lf | %8d |\n", iter.x, dih.iters - 2);
	printf("Ньютон   |%10lf | %8d |\n\n", newton.x, newton.iters);
	/////////////////
	printf("3x - 4ln(x) - 5\n");
	/////////////////
	printf("    x ≈ 3.23\n");
	/////////////////
	printf("%s%10s | %8s |\n", "Метод    |", "  корень  ", "итерации");
	dih = diho(f23, a2, b2, e);
	iter = iteration(f23, a2, b2, e);
	newton = newtons(f23, a2, b2, e);
	printf("Дихотомия|%10lf | %8d |\n", dih.x, dih.iters);
	printf("Итераций |%10lf | %8d |\n", iter.x, dih.iters - 5);
	printf("Ньютон   |%10lf | %8d |\n\n", newton.x, newton.iters);
	/////////////////
	return 0;
}

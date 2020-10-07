#include <stdio.h>
typedef long long ll;
void printset(ll set)
{
	for (int i = 31; i >= 0; --i)
	{
		printf("%lld", (set >> i) % 2);
	}
	printf("\n");
}
ll create_alphabet_mask()
{
	ll res = (1ll << 33) - 1;
	printset(res);
	return res;
}
int main()
{
	unsigned int n, s;
	scanf("%ui", &n);
	scanf("%ui", &s);
	printset(n);
	printset((n >> s) | (n << (sizeof(n) * 8 - s)));
	//	create_alphabet_mask();
	return 0;
}

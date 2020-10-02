#include <stdio.h>
#define wrong -1
int IO_code = 1025;
int A_code = 1040;
int YA_code = 1071;
int a_code = 1072;
int ya_code = 1103;
int io_code = 1105;
typedef long long ll;
int uni(int f, int s)
{
	int res = 0;
	res |= (f << 8);
	res |= s;
	return res;
}
int toNum(int sym)
{
	int first = (sym & 0b0001111100000000);
	first = (first >> 2);
	int second = (sym & 0b0000000000111111);
	long long res = (first | second);
	return res;
}

int InAl(int sym)
{
	ll tmp = -1;
	ll num = toNum(sym);
	//printf("%lld\n", num);
	if (num == IO_code || num == io_code)
		tmp = 32;
	if (A_code <= num && num <= YA_code)
		tmp = num - A_code;
	if (a_code <= num && num <= ya_code)
		tmp = num - a_code;
	//printf("%lld\n", tmp);
	return tmp;
}

void printset(ll set)
{
	for (int i = 63; i >= 0; --i)
	{
		printf("%lld", (set >> i) % 2);
	}
	printf("\n");
}

ll decode()
{
	ll ch;
	ll set = 0;
	do
	{
		ch = getchar();
		//printf("\n%c, %d\n", ch, ch);
		if ((ch & 0b11100000) == 0b11000000)
		{
			ll num = 0;
			ll tmp = getchar();
			ch = uni(ch, tmp);
			num = InAl(ch);
			//printf("\n%lld\n", num);
			if (0 <= num && num <= 32)
				set = set | (1ll << num);
			//printf("SET: %lld\n", set);
			printset(set);
		}
	} while (ch != ' ' && ch != '\t' && ch != '\n' && ch != EOF);
	return set;
}

int main()
{
	int ans = 0;
	ll prev = -1;
	ll current = decode();
	// printf("%lld", current);
	while (current != EOF)
	{
		if (current == wrong)
		{
			current = decode();
			continue;
		}
		// printf("%lld", current);
		if (current == prev)
		{
			ans = 1;
			break;
		}
		else
		{
			prev = current;
			current = decode();
		}
	}
	if (ans)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}
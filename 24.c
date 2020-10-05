#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef long long ll;
typedef enum bracket bracket;
typedef enum operator operator;
typedef struct item item;
typedef struct token token;
typedef struct vector vector;
typedef struct node node;

enum bracket
{
	open,
	close
};
enum operator
{
	sum,
	diff,
	multi,
	divis,
	power
};
struct item
{
	ll val;
	operator op;
	bracket br;
	char var;
};
struct token
{
	int type;
	item el;
};
struct vector
{
	int n;
	token *data;
};
struct node
{
	struct node *left;
	struct node *right;
	token data;
	ll res;
	bool calculatable;
};
void print(token tok)
{
	if (tok.type == 1)
		printf("%lli", tok.el.val);
	if (tok.type == 2)
	{
		if (tok.el.op == sum)
			printf("+");
		if (tok.el.op == diff)
			printf("-");
		if (tok.el.op == multi)
			printf("*");
		if (tok.el.op == divis)
			printf("/");
		if (tok.el.op == power)
			printf("^");
	}
	if (tok.type == 3)
		printf("%c", (tok.el.br == open ? '(' : ')'));
	if (tok.type == 4)
		printf("%c", tok.el.var);
}

ll binpow(ll x, ll y)
{
	ll ans = 1;
	while (y > 0)
	{
		if (y & 1)
			ans *= x;
		x *= x;
		y = y >> 1;
	}
	return ans;
}

vector create(vector vect, int n_)
{
	vect.n = n_;
	vect.data = malloc(sizeof(token) * vect.n);
	return vect;
}

vector push_back(vector vect, token tok)
{
	vect.n++;
	vect.data = realloc(vect.data, sizeof(token) * vect.n);
	(vect.data)[vect.n - 1] = tok;
	return vect;
}

node *build(node *cur, vector v, int l, int r)
{
	if (l == r)
	{
		cur = malloc(sizeof(node));
		cur->data = v.data[r];
		cur->left = NULL;
		cur->right = NULL;
		cur->res = 0;
		cur->calculatable = false;
		return cur;
	}
	if (l + 1 == r)
	{
		cur = malloc(sizeof(node));
		cur->data = v.data[l];
		cur->left = NULL;
		cur->right = build(cur->right, v, l + 1, r);
		cur->res = 0;
		cur->calculatable = false;
		return cur;
	}
	int *index = malloc(sizeof(int) * (r - l + 2));
	index[0] = 0;
	int flag = -1;
	for (int i = 1; i < r - l + 2; i++)
	{
		index[i] = index[i - 1];
		if (v.data[l + i - 1].type == 1 || v.data[l + i - 1].type == 4)
			index[i]++;
		if (v.data[l + i - 1].type == 2)
			index[i]--;
		if (v.data[l + i - 1].type == 3 && v.data[l + i - 1].el.br == close)
			index[i]--;
		if (v.data[l + i - 1].type == 3 && v.data[l + i - 1].el.br == open)
			index[i]++;
	}
	for (int i = r - l + 1; i > 0; i--)
	{
		if (flag != -1)
			break;
		if (flag == -1 && index[i] == 0 && v.data[l + i - 1].type == 2 &&
			(v.data[l + i - 1].el.op == sum || v.data[l + i - 1].el.op == diff))
			flag = l + i - 1;
	}
	for (int i = r - l + 1; i > 0; i--)
	{
		if (flag != -1)
			break;
		if (flag == -1 && index[i] == 0 && v.data[l + i - 1].type == 2 &&
			(v.data[l + i - 1].el.op == multi || v.data[l + i - 1].el.op == divis))
			flag = l + i - 1;
	}
	for (int i = 1; i < r - l + 2; i++)
	{
		if (flag != -1)
			break;
		if (flag == -1 && index[i] == 0 &&
			v.data[l + i - 1].type == 2 && v.data[l + i - 1].el.op == power)
			flag = l + i - 1;
	}
	if (flag == -1)
		return build(cur, v, l + 1, r - 1);
	cur = malloc(sizeof(node));
	cur->left = build(cur->left, v, l, flag - 1);
	cur->right = build(cur->right, v, flag + 1, r);
	cur->data = v.data[flag];
	cur->res = 0;
	cur->calculatable = false;
	free(index);
	return cur;
}

bool bi(node *cur, int t)
{
	if ((cur->data).type == 2 && (cur->data).el.op == t)
	{
		return bi(cur->left, t) | bi(cur->right, t);
	}
	return cur->calculatable;
}

node *add(node *cur, int t, ll val)
{
	if (cur->calculatable)
	{
		cur->res = (t == 0 ? cur->res + val : cur->res * val);
		(cur->data).el.val = cur->res;
		return cur;
	}
	if ((cur->data).type == 2 && (cur->data).el.op == t)
	{

		if (bi(cur->left, t))
			cur->left = add(cur->left, t, val);
		else
			cur->right = add(cur->right, t, val);
	}
	return cur;
}

node *cp(node *cur)
{
	if (cur == NULL)
		return NULL;
	node *ans = malloc(sizeof(node));
	ans->data = cur->data;
	ans->res = cur->res;
	ans->calculatable = cur->calculatable;
	ans->left = cp(cur->left);
	ans->right = cp(cur->right);
	return ans;
}

node *delete (node *cur)
{
	if (cur == NULL)
		return NULL;
	cur->left = delete (cur->left);
	cur->right = delete (cur->right);
	free(cur);
	return cur;
}

node *mul(node *cur, node *t)
{
	if ((cur->data).type == 2 && ((cur->data).el.op == sum || (cur->data).el.op == diff))
	{
		cur->right = mul(cur->right, t);
		cur->left = mul(cur->left, t);
		return cur;
	}
	else
	{
		node *mmult = malloc(sizeof(node));
		(mmult->data).type = 2;
		(mmult->data).el.op = multi;
		mmult->right = cur;
		mmult->left = cp(t);
		mmult->calculatable = false;
		return mmult;
	}
}

node *calc(node *cur)
{
	if ((cur->data).type == 1)
	{
		cur->res = (cur->data).el.val;
		cur->calculatable = true;
	}
	if ((cur->data).type == 2)
	{
		if ((cur->data).el.op == multi && (cur->right->data).type == 2 && ((cur->right->data).el.op == sum || (cur->right->data).el.op == diff))
		{
			cur->right = mul(cur->right, cur->left);
			node *ccur = cur->right;
			cur->left = delete (cur->left);
			free(cur);
			return calc(ccur);
		}
		if ((cur->data).el.op == multi && (cur->left->data).type == 2 && ((cur->left->data).el.op == sum || (cur->left->data).el.op == diff))
		{
			cur->left = mul(cur->left, cur->right);
			node *ccur = cur->left;
			cur->right = delete (cur->right);
			free(cur);
			return calc(ccur);
		}
		cur->left = calc(cur->left);
		cur->right = calc(cur->right);
		cur->calculatable = (cur->left->calculatable) & (cur->right->calculatable);
		if (cur->calculatable == false)
		{
			if ((cur->data).el.op == diff || (cur->data).el.op == divis || (cur->data).el.op == power || ((cur->right->calculatable) == false && (cur->left->calculatable) == false))
				return cur;
			if (cur->right->calculatable == true)
			{
				if (bi(cur->left, (cur->data).el.op))
				{
					cur->left = add(cur->left, (cur->data).el.op, cur->right->res);
					node *ccur = cur->left;
					free(cur->right);
					free(cur);
					return ccur;
				}
			}
			else
			{
				if (bi(cur->right, (cur->data).el.op))
				{
					cur->right = add(cur->right, (cur->data).el.op, cur->left->res);
					node *ccur = cur->right;
					free(cur->left);
					free(cur);
					return ccur;
				}
			}
			return cur;
		}
		ll l = cur->left->res;
		ll r = cur->right->res;
		if ((cur->data).el.op == sum)
			cur->res = l + r;
		if ((cur->data).el.op == diff)
			cur->res = l - r;
		if ((cur->data).el.op == multi)
			cur->res = l * r;
		if ((cur->data).el.op == divis)
			cur->res = l / r;
		if ((cur->data).el.op == power)
			cur->res = binpow(l, r);
		free(cur->left);
		free(cur->right);
		cur->left = NULL;
		cur->right = NULL;
		(cur->data).type = 1;
		(cur->data).el.val = cur->res;
	}
	return cur;
}

node *multiply(node *f, node *g)
{
	if (f == NULL || g == NULL)
		return NULL;
	node *ans = malloc(sizeof(node));
	(ans->data).type = 2;
	(ans->data).el.op = multi;
	ans->left = cp(f);
	ans->right = cp(g);
	ans->res = 0;
	ans->calculatable = false;
	return ans;
}

void printt(node *cur)
{
	if (cur == NULL)
		return;
	if (!(((cur->data).type == 1 && (cur->data).el.val >= 0) || (cur->data).type == 4))
		printf("(");
	printt(cur->left);
	print(cur->data);
	printt(cur->right);
	if (!(((cur->data).type == 1 && (cur->data).el.val >= 0) || (cur->data).type == 4))
		printf(")");
}
void answer(node *f, node *g)
{
	printf("f=");
	printt(f);
	printf("\n");
	printf("g=");
	printt(g);
	printf("\n");
	f = calc(f);
	g = calc(g);
	node *ans = multiply(f, g);
	printf("f*g = ");
	printt(ans);
	printf("\n");
	ans = calc(ans);
	printf("f*g = ");
	printt(ans);
	printf("\n");
}

int main()
{
	node *f = NULL;
	node *g = NULL;
	char c;
	int mult = 1;
	vector v;
	token cur;
	cur.type = 0;
	v = create(v, 0);
	while (scanf("%c", &c) > 0)
	{
		if (c == '#')
		{
			if (cur.type > 0)
			{
				if (cur.type == 1)
					cur.el.val *= mult;
				if (cur.type == 4)
				{
					if (mult < 0)
					{
						cur.type = 1;
						cur.el.val = -1;
						v = push_back(v, cur);
						cur.type = 2;
						cur.el.op = multi;
						v = push_back(v, cur);
					}
				}
				v = push_back(v, cur);
			}
			f = build(f, v, 0, v.n - 1);
			free(v.data);
			v = create(v, 0);
			mult = 1;
			cur.type = 0;
			continue;
		}
		if (c == '\n' || c == '\t' || c == ' ')
			continue;
		if ('0' <= c && c <= '9')
		{
			if (cur.type == 1)
			{
				cur.el.val = 10 * cur.el.val + c - '0';
			}
			else
			{
				cur.type = 1;
				cur.el.val = c - '0';
			}
			continue;
		}
		if (c == '+' || c == '-')
		{
			if (cur.type == 1)
			{
				cur.el.val *= mult;
				v = push_back(v, cur);
				mult = 1;
			}
			if (v.data[v.n - 1].type == 2 || v.n == 0 || (v.data[v.n - 1].type == 3 && v.data[v.n - 1].el.br == open))
			{
				mult *= (c == '+' ? 1 : -1);
			}
			else
			{
				cur.type = 2;
				cur.el.op = (c == '+' ? sum : diff);
				v = push_back(v, cur);
				cur.type = 0;
			}
			continue;
		}
		if (c == '*' || c == '/' || c == '^')
		{
			if (cur.type == 1)
			{
				cur.el.val *= mult;
				v = push_back(v, cur);
				mult = 1;
			}
			cur.type = 2;
			if (c == '*')
				cur.el.op = multi;
			if (c == '/')
				cur.el.op = divis;
			if (c == '^')
				cur.el.op = power;
			v = push_back(v, cur);
			cur.type = 0;
			continue;
		}
		if (c == '(' || c == ')')
		{
			if (cur.type == 1)
			{
				cur.el.val *= mult;
				v = push_back(v, cur);
				mult = 1;
			}
			if (c == '(' && mult < 0)
			{
				cur.type = 1;
				cur.el.val = -1;
				v = push_back(v, cur);
				cur.type = 2;
				cur.el.op = multi;
				v = push_back(v, cur);
				mult = 1;
			}
			cur.type = 3;
			cur.el.br = (c == '(' ? open : close);
			v = push_back(v, cur);
			cur.type = 0;
			continue;
		}
		if (mult < 0)
		{
			cur.type = 3;
			cur.el.br = open;
			v = push_back(v, cur);
			cur.type = 1;
			cur.el.val = -1;
			v = push_back(v, cur);
			cur.type = 2;
			cur.el.op = multi;
			v = push_back(v, cur);
			cur.type = 4;
			cur.el.var = c;
			v = push_back(v, cur);
			cur.type = 3;
			cur.el.br = close;
			v = push_back(v, cur);
			mult = 1;
		}
		else
		{
			cur.type = 4;
			cur.el.var = c;
			v = push_back(v, cur);
		}
		cur.type = 0;
	}
	if (cur.type > 0)
	{
		if (cur.type == 1)
			cur.el.val *= mult;
		if (cur.type == 4)
		{
			if (mult < 0)
			{
				cur.type = 1;
				cur.el.val = -1;
				v = push_back(v, cur);
				cur.type = 2;
				cur.el.op = multi;
				v = push_back(v, cur);
			}
		}
		v = push_back(v, cur);
	}
	g = build(g, v, 0, v.n - 1);
	answer(f, g);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct tree tree;
typedef struct tree *treeptr;
typedef enum distribution distribution;
enum distribution
{
	Aptosid,
	Bastille,
	Centos,
	Debian,
	Endian,
	RedHat,
	Kubuntu,
	Mageia,
	Mint,
	Slackware,
	Ubuntu,
	Kali,
	BlackBox,
	Samurai,
	OpenSUSE
};
struct tree
{
	treeptr l;
	treeptr r;
	distribution val;
};
enum compare
{
	NOT_EQUAL,
	EQUAL
};
enum menu
{
	END,
	ADD,
	DELETE,
	B,
	PRINT,
	MENU,
	WAIT
};

char *distribution_str[] = {"Aptosid", "Bastille", "Centos", "Debian",
							"Endian", "RedHat", "Kubuntu", "Mageia",
							"Mint", "Slackware", "Ubuntu", "Kali",
							"BlackBox", "Samurai", "OpenSUSE"};
treeptr *find(treeptr *t, distribution val);
bool insert_before(treeptr *pos, distribution val);
void node_delete(treeptr *pos);
void print_tree(treeptr t, int lvl);
bool is_B(treeptr t);
void t_delete(treeptr *t);
bool compare(char *a, char *b);
unsigned long _max(unsigned long a, unsigned long b);
unsigned long _abs(unsigned long a, unsigned long b);
bool is_empty();
int str_to_int(char *str);

treeptr root = NULL;

unsigned long _max(unsigned long a, unsigned long b)
{
	return (a > b) ? a : b;
}

unsigned long _abs(unsigned long a, unsigned long b)
{
	return (a > b) ? a - b : b - a;
}

bool compare(char *a, char *b)
{
	unsigned long l1 = (a == NULL) ? 0 : strlen(a);
	unsigned long l2 = (b == NULL) ? 0 : strlen(b);
	if (l1 * l2 == 0)
		return NOT_EQUAL;
	for (int i = 0; i < _max(l1, l2); ++i)
		if (a[i] != b[i])
			return NOT_EQUAL;
	return EQUAL;
}
char *enum_to_str(distribution val)
{
	return distribution_str[val];
}

distribution str_to_enum(char *str)
{
	if (compare(str, "Aptosid"))
		return Aptosid;
	if (compare(str, "Bastille"))
		return Bastille;
	if (compare(str, "Centos"))
		return Centos;
	if (compare(str, "Debian"))
		return Debian;
	if (compare(str, "Endian"))
		return Endian;
	if (compare(str, "RedHat"))
		return RedHat;
	if (compare(str, "Kubuntu"))
		return Kubuntu;
	if (compare(str, "Mageia"))
		return Mageia;
	if (compare(str, "Mint"))
		return Mint;
	if (compare(str, "Slackware"))
		return Slackware;
	if (compare(str, "Ubuntu"))
		return Ubuntu;
	if (compare(str, "Kali"))
		return Kali;
	if (compare(str, "BlackBox"))
		return BlackBox;
	if (compare(str, "Samurai"))
		return Samurai;
	if (compare(str, "OpenSUSE"))
		return OpenSUSE;
	return -1;
}
void menu()
{

	printf("\t+-------------+------------------------------+\n");
	printf("\t|  commands   |     description              |\n");
	printf("\t|-------------|------------------------------|\n");
	printf("\t|  end or 0   |     close programm           |\n");
	printf("\t|-------------|------------------------------|\n");
	printf("\t|  add (int)  |     add n in binary tree     |\n");
	printf("\t|  or 1 val   |     add 1 -> add el.'1'      |\n");
	printf("\t|-------------|------------------------------|\n");
	printf("\t|  delete val |     delete an element        |\n");
	printf("\t|  or 2 val   |     delete 1 -> delete el.'1'|\n");
	printf("\t|-------------|------------------------------|\n");
	printf("\t|  b or 3     |     check is tree B          |\n");
	printf("\t|-------------|------------------------------|\n");
	printf("\t|  print or 4 |     print binary tree        |\n");
	printf("\t|-------------|------------------------------|\n");
	printf("\t|  menu or 5  |     print menu               |\n");
	printf("\t|-------------|------------------------------|\n");
	printf("\t|Aptosid, Bastille, Centos, Debian, Endian,  |\n");
	printf("\t|RedHat, Kubuntu, Mageia, Mint, Slackware,   |\n");
	printf("\t|Ubuntu, Kali, BlackBox, Samurai, OpenSUSE   |\n");
	printf("\t+-------------+------------------------------+\n\n");
}

bool is_empty()
{
	char a;
	int isinit = 0;
	bool check = true;
	while (scanf("%c", &a))
	{
		if ((a == ' ' || a == '\t') && isinit == 0)
			continue;
		else if (a == '\n')
			break;
		else
		{
			check = false;
			isinit = 2;
		}
	}
	return check;
}

bool insert_before(treeptr *pos, distribution val)
{
	if (*pos != NULL)
		return false;
	treeptr new_node = (treeptr)malloc(sizeof(tree));
	if (new_node == NULL)
		return false;
	new_node->val = val;
	new_node->l = NULL;
	new_node->r = NULL;
	*pos = new_node;
	return true;
}

void print_tree(treeptr t, int lvl)
{
	if (t == NULL)
		return;
	print_tree(t->l, lvl + 1);
	for (int i = 0; i < lvl; ++i)
		printf("\t");
	printf("%s\n", enum_to_str(t->val));
	print_tree(t->r, lvl + 1);
}

bool is_B(treeptr t)
{
	if ((t->l != NULL && t->r == NULL) || (t->r != NULL && t->l == NULL))
		return false;
	if (t->l == NULL && t->r == NULL)
		return true;
	if (t->l != NULL && t->r != NULL)
		return (is_B(t->l) && is_B(t->r));
}

treeptr *find(treeptr *t, distribution val)
{
	if ((*t) == NULL || (*t)->val == val)
		return t;
	else if ((*t)->val > val)
		return find(&(*t)->l, val);
	else
		return find(&(*t)->r, val);
}

void node_delete(treeptr *pos)
{
	treeptr tofree = *pos;
	treeptr l = (*pos)->l;
	treeptr r = (*pos)->r;

	if (r == NULL)
		*pos = l;
	else if (l == NULL)
		*pos = r;
	else
	{
		treeptr *new_node = &(*pos)->l;
		while ((*new_node)->r != NULL)
		{
			new_node = &(*new_node)->r;
		}

		treeptr l_max = *new_node;
		treeptr check = l_max->l;
		*new_node = (*new_node)->l;
		if (l_max == l)
			l_max->l = check;
		else
			l_max->l = l;
		l_max->r = r;
		*pos = l_max;
	}

	free(tofree);
}

void t_delete(treeptr *t)
{
	while (*t != NULL)
		node_delete(t);
}

char *parser()
{
	char a;
	int isinit = 0;
	char *str = NULL;
	while (scanf("%c", &a))
	{
		if (a == ' ')
		{
			if (isinit == 0)
				isinit = 1;
			else if (isinit == 1 && str != NULL)
				isinit = 3;
		}
		else if (a == '\n' || a == '\t')
		{
			if (isinit != 1 && isinit != 3)
				str = NULL;
			break;
		}
		else if (isinit == 1)
		{
			unsigned long pos = str == NULL ? 0 : strlen(str);
			char *tmp = realloc(str, sizeof(char) * (pos + 1));
			if (!tmp)
				isinit = 2;
			str = tmp;
			str[pos] = a;
		}
		else
			isinit = 2;
	}
	return str;
}
// int str_to_int(char *str)
// {
// 	int n = 0, k = 1;
// 	while (*str)
// 	{
// 		if (*str == '-')
// 			k = -1;
// 		if ((*str >= '0') && (*str <= '9'))
// 			n = 10 * n + *str - '0';
// 		str++;
// 	}
// 	n *= k;
// 	return n;
// }
char interface()
{
	char comm[10];
	scanf("%s", comm);
	if (compare(comm, "add") || compare(comm, "1"))
	{
		char *arg;
		arg = parser();
		int res = str_to_enum(arg);
		if (res != -1)
		{
			treeptr *pos = find(&root, res);
			insert_before(pos, res);
		}
		else
			printf("Invalid argument.\n");
		return ADD;
	}
	else if (compare(comm, "delete") || compare(comm, "2"))
	{
		char *arg;
		arg = parser();
		int res = str_to_enum(arg);
		if (res != -1)
		{
			treeptr *pos = find(&root, res);
			if ((*pos) && root)
				node_delete(pos);
		}
		else
			printf("Invalid argument.\n");
		return DELETE;
	}
	if (compare(comm, "menu") || compare(comm, "5"))
	{
		menu();
		return MENU;
	}
	bool flag = is_empty();
	if (flag)
	{
		if (compare(comm, "b") || compare(comm, "3"))
		{
			if (!root)
			{
				printf("Tree is empty.");
				return B;
			}
			if (is_B(root))
				printf("This is a B tree.\n");
			else
				printf("This is NOT a B tree.\n");
			return B;
		}
		else if (compare(comm, "print") || compare(comm, "4"))
		{
			print_tree(root, 0);
			return PRINT;
		}
		else if (compare(comm, "end") || compare(comm, "0"))
			return END;
		else
			printf("Invalid command.\n");
	}
	return WAIT;
}

int main()
{
	menu();
	while (interface())
	{
	}
	t_delete(&root);
	return 0;
}

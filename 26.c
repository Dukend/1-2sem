#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef long long ll;

typedef struct
{
	ll val;
} data;

typedef struct
{
	data item;
} v_el;

typedef struct
{
	v_el *buf;
	size_t size;
	size_t capacity;
} v_type;

typedef struct
{
	size_t size;
	v_type *buf;
} s_type;

ll v_init(v_type *v)
{
	v->buf = malloc(sizeof(v_el) * 10);
	if (v->buf == NULL)
		return 1;
	v->capacity = 10;
	v->size = 0;
	return 0;
}

bool v_is_empty(v_type *v)
{
	return v->size == 0;
}

ll v_change_cap(v_type *v, size_t new_cap)
{
	v_el *old_buffer = v->buf;
	v->buf = realloc(v->buf, new_cap * sizeof(v_el));
	if (v->buf == NULL)
	{
		v->buf = old_buffer;
		return 1;
	}
	v->capacity = new_cap;
	return 0;
}

ll v_set_size(v_type *v, size_t size)
{
	if (size == v->size)
		return 0;
	if (size > v->capacity)
	{
		if (v_change_cap(v, (size * 3) / 2) != 0)
			return 1;
		else if (size * 9 < v->capacity * 4)
			if (v_change_cap(v, (size * 2) / 3) != 0)
				return 1;
	}
	v->size = size;
	return 0;
}
ll v_push_back(v_type *v, data data)
{
	if (v_set_size(v, v->size + 1) != 0)
		return 1;
	v->buf[v->size - 1].item = data;
	return 0;
}

ll v_pop_back(v_type *v, data *data)
{
	*data = v->buf[v->size - 1].item;
	if (v_set_size(v, v->size - 1) != 0)
		return 1;
	return 0;
}

ll v_set(v_type *v, size_t index, data data)
{
	if (index < 0 || index >= v->size)
		return 1;
	v->buf[index].item = data;
	return 0;
}

ll v_get(v_type *v, size_t index, data *data)
{
	if (index < 0 || index >= v->size)
		return 1;
	*data = v->buf[index].item;
	return 0;
}

ll v_set_capacity(v_type *v, size_t capacity)
{
	if (capacity >= v->size)
	{
		if (capacity > v->capacity)
			return v_change_cap(v, capacity);
		else
			return 0;
	}
	return 1;
}

//////////////////////////////

ll s_init(s_type *s)
{
	s->size = 0;
	s->buf = malloc(sizeof(v_type));
	if ((s->buf == NULL))
		return 1;
	ll ret_code;
	if ((ret_code = v_init(s->buf)))
		return ret_code;
	return 0;
}

bool s_is_empty(s_type *s)
{
	return s->size == 0;
}

size_t s_get_size(s_type *s)
{
	return s->size;
}

ll s_push(s_type *s, data data)
{
	ll ret_code = v_push_back(s->buf, data);
	if (ret_code != 0)
		return ret_code;
	s->size++;
	return 0;
}

ll s_pop(s_type *s, data *data)
{
	if (s_is_empty(s))
		return 1;
	if (v_pop_back(s->buf, data) != 0)
		return 1;
	s->size--;
	return 0;
}

ll s_print(s_type *s)
{
	for (int i = s->buf->size - 1; i >= 0; --i)
	{
		data data;
		ll ret_code = v_get(s->buf, i, &data);
		if (ret_code != 0)
			return ret_code;
		printf("%lld ", data.val);
	}
	printf("\n");
	return 0;
}

void swap(data *a, data *b)
{
	data tmp = *a;
	*a = *b;
	*b = tmp;
}

int comp(data *a, data *b)
{
	if (a->val > b->val)
		return 1;
	if (a->val < b->val)
		return -1;
	return 0;
}

bool bubble(s_type *s)
{
	s_type c;
	if (s_init(&c) != 0)
		return 0;
	data a;
	data b;
	if (s_pop(s, &a) != 0)
		return 0;
	bool ans = 0;
	while (s_pop(s, &b) == 0)
	{
		if (comp(&a, &b) > 0)
		{
			swap(&a, &b);
			s_push(s, b);
			ans = 1;
			break;
		}
		else
		{
			s_push(&c, a);
			a = b;
			continue;
		}
	}
	s_push(s, a);
	while (s_pop(&c, &a) == 0)
		s_push(s, a);
	return ans;
}

void sort(s_type *s)
{
	if (s_is_empty(s))
		return;
	bool flag = 1;
	while (flag)
		flag = bubble(s);
}

int main()
{
	s_type *s = malloc(sizeof(s_type));
	s_init(s);
	int n, c;
	printf("Amount of elements:\n");
	scanf("%d", &n);
	printf("Choose:\n");
	printf("1 - random stack\n");
	printf("2 - given stack\n");
	scanf("%d", &c);
	if (c == 2)
		printf("Еnter integer numbers");
	for (int i = 0; i < n; ++i)
	{
		data data;
		if (c == 1)
		{
			data.val = rand() % 50;
		}
		else if (c == 2)
		{
			scanf("%lld", &data.val);
		}
		else
		{
			printf("Ok. It will be random\n");
			data.val = rand() % 50;
		}
		s_push(s, data);
	}

	printf("Stack:\n");
	s_print(s);
	sort(s);
	printf("Sorted by bubble:\n");
	s_print(s);

	return 0;
}
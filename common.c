#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"
int get_first(void)
{
    int ch;
    do
    {
        ch = tolower(getchar());
    } while (isspace(ch));
    eatline();
    return ch;
}
void eatline(void)
{
    while (getchar() != '\n')
        continue;
}
void show_array(const double ar[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%-8g", ar[i]);
        if (0 == (i + 1) % 8)
        {
            putchar('\n');
        }
    }
    putchar('\n');
    return;
}

char* s_gets(char* st, int n)
{
    char* ret_val;
    char* find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
        {
            *find = '\0';
        }
        else
        {
            while (getchar() != '\n')
                continue;
        }
    }
    return ret_val;
}



/*#include"queue.h"
#define MIN_PER_HR 60.0

bool newcustomer(double x);
Item customertime(long when);
int main()
{
	Queue line;
	Item temp;
	int hours, perhour, wait_time=0;
	long cycle, cyclelimit, turnaways=0;
	long customers=0, served=0, sum_line=0, line_wait=0;
	double min_per_cust;
	InitializeQueue(&line);
	srand((unsigned int)time(0));
	puts("enter hour");
	scanf("%d", &hours);
	cyclelimit = MIN_PER_HR*hours;
	puts("ernter new customers number");
	scanf("%d", &perhour);
	min_per_cust = MIN_PER_HR / perhour;
	for (cycle = 0;cycle < cyclelimit;cycle++)
	{
		if (newcustomer(min_per_cust))
		{
			if (QueueIsFull(&line))
				turnaways++;
			else
			{
				customers++;
				temp = customertime(cycle);
				EnQueue(temp, &line);
			}
		}
		if (wait_time <= 0 && !QueueIsEmmpty(&line))
		{
			DeQueue(&temp, &line);
			wait_time = temp.processtime;
			line_wait += cycle - temp.arrive;
			served++;
		}
		if (wait_time > 0)
			wait_time--;
		sum_line += QueueItemCount(&line);
	}
	if (customers > 0)
	{

	}
	else
		EmptyTheQueue(&line);




	return 0;
}
bool newcustomer(double x)
{
	if (rand() * x / RAND_MAX < 1)
		return true;
	else return false;
}
Item customertime(long when)
{
	Item cust;
	cust.arrive = when;
	cust.processtime = rand() % 3 + 1;
	return cust;
}
*/
/*#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
static unsigned int next = 1;
int rand1()
{
	next = next * 1245 +12345;
	return ((next % 10)+1);
}
int vit(int n)
{
	next = n;
}*/
/*#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void InitializeList(List* plist)
{
	(*plist).items = 0;
}

bool ListIsEmpty(const List* plist)
{
	//if ((*plist).items == 0)
		///return true;
	//else
		//return false;
	return 0 == plist->items;
}

bool ListIsFull(const List* plist)
{
	return MAXSIZE == plist->items;
}

unsigned int ListItemCount(const List* plist)
{
	return plist->items;
}

bool AddItem(Item item, List* plist)
{
	if (plist->items == MAXSIZE)
		return false;
	else
	{
		plist->entries[plist->items++] = item;
		return true;
	}
}

void Traverse(const List* plist, void (*pfun)(Item item))
{
	for (int i = 0;i < plist->items;i++)
	{
		(*pfun)(plist->entries[i]);
	}
	return;
}

void EmptyTheList(List* plist)
{
	plist->items = 0;
}
*/
/*#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>
#define TSIZE 45

struct film
{
    char title[TSIZE];
    int rating;
};

typedef struct film Item;

#define MAXSIZE 100
typedef struct list
{
    Item entries[MAXSIZE];
    int items;
} List;

void InitializeList(List* plist);

bool ListIsEmpty(const List* plist);

bool ListIsFull(const List* plist);

unsigned int ListItemCount(const List* plist);

bool AddItem(Item item, List* plist);

void Traverse(const List* plist, void (*pfun)(Item item));

void EmptyTheList(List* plist);

#endif*/
/*#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>
#define TSIZE 45

struct film
{
    char title[TSIZE];
    int rating;
};

typedef struct film Item;

typedef struct node
{
    Item item;
    struct node *next;
} Node;

typedef struct list
{
    Node *head;
    Node *end;
}
List;

void InitializeList(List *plist);

bool ListIsEmpty(const List *plist);

bool ListIsFull(const List *plist);

unsigned int ListItemCount(const List *plist);

bool AddItem(Item item, List *plist);

void Traverse(const List *plist, void (*pfun)(Item item));

void EmptyTheList(List *plist);

#endif
*/
/*#include <stdio.h>
#include <stdlib.h>
#include "list.h"
void InitializeList(List* plist)
{
	(*plist).head = NULL;
	(*plist).end = NULL;
	return;
}

bool ListIsEmpty(const List* plist)
{
	return NULL == (*plist).head;
}

bool ListIsFull(const List* plist) 
{
	Node* p;
	bool full;
	p = (Node*)malloc(sizeof(Node));
	if (p == NULL)
		full = true;
	else
		full = false;
	free(p);
	return full;
}

unsigned int ListItemCount(const List* plist)
{
	unsigned int count = 0;
	Node* p = (*plist).head;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

bool AddItem(Item item, List* plist)
{
	Node* pnew;
	Node* scan = (*plist).head;
	pnew = malloc(sizeof(Node));
	if (pnew == NULL)
		return false;
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (scan == NULL)
	{
		(*plist).head = pnew;
		(*plist).end = pnew;
	}
	else
	{
		(*plist).end->next = pnew;
		(*plist).end = pnew;
	}
	return true;
}

void Traverse(const List* plist, void (*pfun)(Item item))
{
	Node* p = (*plist).head;
	while (p->next != NULL)
	{
		(*pfun)(p->item);
		p=p->next;
	}
	return;
}

void EmptyTheList(List* plist)
{
	Node* psave;
	while ((*plist).head != NULL)
	{
		psave = (*plist).head->next;
		free((*plist).head);
		(*plist).head = psave ;
	}
	return;
}

static void CopyToNode(Item item, Node* pnode)
{
	pnode->item = item;
}*/
/*
void InitializeList(List* plist)
{
	plist = NULL;
}

bool ListIsEmpty(const List* plist)
{
	if (plist == NULL)
		return true;
	else
		return false;
}

bool ListIsFull(const List* plist)
{
	Node* pt;
	bool full;
	pt = (Node*)malloc(sizeof(Node));
	if (pt == NULL)
		full = true;
	else
		full = false;
	free(pt);
	return full;
}

unsigned int ListItemCount(const List* plist)
{
	unsigned int count = 0;
	Node *pnode = *plist;
	while (pnode != NULL)
	{
		count++;
		pnode = pnode->next;
	}
}

bool AddItem(Item item, List* plist)
{
	Node* pnew;
	Node* scan = *plist;
	pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
		return false;
	pnew->next = NULL;
	CopyToNode(item, pnew);
	if (scan == NULL)
		*plist = pnew;
	else
	{
		while (scan->next != NULL)
			scan = scan->next;
		scan->next = pnew;
	}
	return true;
}

void Traverse(const List* plist, void (*pfun)(Item item))
{
	Node* p = *plist;
	while (p != NULL)
	{
		(*pfun)(p->item);
		p = p->next;
	}
}

void EmptyTheList(List* plist)
{
	Node* psave;
	while (*plist != NULL)
	{
		psave = (*plist)->next;
		free(*plist);
		*plist = psave;
	}
}
*/
/*
#define TSIZE 45
void show(struct film* s);
struct film
{
	char title[TSIZE];
	int rating;
	struct film* next;
};
int main()
{
	struct film* head = NULL;
	struct film* current,* prev;
	char input[TSIZE];
	//搜集信息
	while (s_gets(input, TSIZE) != NULL && input[0] != '\0')
	{
		current = (struct film*)malloc(sizeof(struct film));
		if (current == NULL)
			exit(0);
		if (head == NULL)
			head = current;
		else
			prev->next=current;
		current->next = NULL;
		strcpy(current->title, input);
		scanf("%d",&current->rating);
		eatline();
		prev = current;
	}
	//显示每个信息
	if (head==NULL)
	{
		puts("no data");
	}
	else
	{
		puts("here is the data");
	}
	current = head;
	while(current!=NULL)
		{
			printf("title=%s  tating=%d\n",current->title,current->rating);
			current = current->next;
		}
	//释放内存
	current = head;
	while (current != NULL)
	{
		head = current->next;
		free(current);
		current = head;
	}
	return 0;
}
void show(struct film* s)
{
	struct film* current = s;
	if (current->next != NULL)
		show(current->next);
	printf("title=%s  tating=%d\n", current->title, current->rating);
	return;
}*/
/*
double* new_d_array(int n, ...);

int main()
{
	double* p1;
	double* p2;

	p1 = new_d_array(5, 1.2, 2.3, 3.4, 4.5, 5.6);
	p2 = new_d_array(4, 100.0, 20.00, 8.08, -1890.0);
	show_array(p1, 5);
	show_array(p2, 4);
	free(p1);
	free(p2);

	return 0;
}
double* new_d_array(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	double* p = (double*)malloc(n * sizeof(double));
	if (p == NULL)
		exit(EXIT_FAILURE);
	for (int i = 0;i < n;i++)
		p[i] = va_arg(ap, double);
	va_end(ap);
	return p;
}*/
/*
#define LEN 40
struct names {
	char first[LEN];
	char last[LEN];
};
int comp(const void* p1, const void* p2);
void showarry(const struct names* begin, int n);
int main()
{

	return 0;
}
int comp(const void* p1, const void* p2)
{
	const struct names* ps1 = (const struct names*)p1;
	const struct names* ps2 = (const struct names*)p2;
	int i;
	i = strcmp(ps1->last, ps2->last);
	if (i != 0)
		return i;
	else
		return strcmp(ps1->first, ps2->first);
}*/
/*
void ranp(int s[],int n,int m);
int main()
{
	int i, ch;
	int choices[20];

	for (i = 0; i < 20; i++)
	{
		choices[i] = i + 1;
	}
	
		ranp(choices, 20, 10);




	return 0;
}
void ranp(int s[], int n, int m)
{
	int i,j=0;
	int* p;
	p = (int*)malloc(n * sizeof(int));
	if (p == NULL)
	{
		exit(EXIT_FAILURE);
	}
	memcpy(p, s, n * sizeof(int));
	srand((unsigned int) time(0));
	while (m > 0)
	{
		i = rand() % n;
		if (p[i] == 0)
			continue;
		else
		{
			printf("%d  ",s[i]);
			p[i] = 0;
			--m;
		}
	}
	free(p);

}*/
/*
double f(double t);
int main()
{
	double t;
	scanf("%lf",&t);
	f(t);
	return 0;
}
double f(double t)
{
	clock_t  a, b,c;
	a=(double) clock();
	b=(double) clock();
	c = (b - a) / CLOCKS_PER_SEC;
	for (int i=0;c<=t;i++, c = (b - a) / CLOCKS_PER_SEC)
	{
		printf("%d ",i);
		b = (double)clock();
	}
}*/
/*
struct jz 
{
	double mo;
	double ag;
};
struct zz
{
	double x;
	double y;
};
struct zz transf(struct jz j);
int main()
{
	struct jz j = { 10.0,6.28 };
	printf("x=%lf , y=%lf\n",transf(j).x,transf(j).y);

	return 0;
}
struct zz transf(struct jz j)
{
	struct zz r={0,0};
	r.x = j.mo * cos(j.ag);
	r.y = j.mo * sin(j.ag);
	return r;
}*/
/*
#define TIAOHE(X,Y) 2/X+2/Y
int main()
{
	printf("%f",TIAOHE(1.0,2.0));

	return 0;
}*/
/*
#define LEN 12
typedef struct 
{
	int id;
	bool status;
	char last[10];
	char first[10];
} plane;
void fa(plane* s);
void fd(plane* s);
int getmenu(void);
int main()
{
	int i;
	char choice;
	plane seat [LEN];
	for (i = 0;i < LEN;i++)
	{
		seat[i].id = i + 1;
		seat[i].status = true;
	}
	while ((choice = getmenu() )!= 'f')
	{
		switch (choice)
		{
		case 'a':fa(seat);break;
		case 'd':fd(seat);break;
		
		}
	}
	return 0;
}
void fa(plane* s)
{
	int i;
	int n = 0;
	int a[LEN] = {0};
	for (i = 0;i < LEN;i++)
	{
		if (s[i].status == true)
		{
			a[i] = i+1;
		}
		n += a[i];
	}
	if (n == 0)
		puts("there's no empty seat!");
	else
	{
		puts("there's the empty seat:  ");
		for (i = 0;i < LEN;i++)
		{
			if (a[i] != 0)
				printf("%-3d",a[i]);
		}
		putchar('\n');
	}
		

			
	

}
void fd(plane* s)
{
	int n;
	fa(s);
	puts("enter your seat:");
	while (scanf("%d", &n) != 1 || --n < 0 || n >= 12 || s[n].status != true)
	{ 
		eatline();
		puts("wrong seat,enter again:");
		continue;
	}eatline();
	//makelist
	puts("your last name and first name:");
	s[n].status = false;
	while(scanf("%9c  %9c",s[n].last,s[n].first)!=2)
	{
		eatline();
		puts("wrong message,enter again:");
		continue;
	}eatline();
	return;
}
int getmenu(void)//显示菜单
{
	int ch;

	puts("To choose a function, enter its letter label:");
	puts("a) Show number of empty seats");
	puts("b) Show list of empty seats");
	puts("c) Show alphabetical list of seat");
	puts("d) Assign a customer to a seat");
	puts("e) Delete a seat assignment");
	puts("f) Quit");
	printf("Please you enter to choose: ");
	while (ch = get_first(), NULL == strchr("abcdef", ch))
	{
		printf("Invalid data! Please you choose again: ");
	}
	return ch;
}
*/
/*
struct month
{
	char name[10];
	char abbr[4];
	int days;
	int num;
};
const struct month months[12] =
{
	 {"January", "Jan", 31, 1},
	{"February", "Feb", 28, 2},
	{"March", "Mar", 31, 3},
	{"April", "Apr", 30, 4},
	{"May", "May", 31, 5},
	{"June", "Jun", 30, 6},
	{"July", "Jul", 31, 7},
	{"August", "Aug", 31, 8},
	{"September", "Sep", 30, 9},
	{"October", "Oct", 31, 10},
	{"November", "Nov", 30, 11},
	{"December", "Dec", 31, 12}
};
int days(char *s);
int main()
{
	int m;
	int s[10];
	scanf("%s",s);
	printf("%d\n",days(s));
	return 0;
}
int days(char* s)
{
	int i = 0;
	int m;
	for (;i < 12;i++)
	{
		if (strcmp(s, months[i].name) == 0)
		{
			m = i+1;
			break;
		}
		if (i == 11)
			exit(EXIT_FAILURE);
	}
	int t = 0;
	for (i = 0;i < m;i++)
	{
		t += months[i].days;
	}
	return t;
}*/
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 256
int main(void)
{
	static char temp[LEN];
	char** p;
	int i, n, len;
	puts("words:");
	scanf("%d",&n);
	if ((p = (char**)malloc(n * sizeof(char*))) != NULL)
	{
		for (i = 0;i < n;i++)
		{
			scanf("%255s",temp);
			len = strlen(temp) + 1;
			p[i] = (char*)malloc(len * sizeof(char));
			if (p[i] != NULL)
				strcpy(p[i], temp);
			else
				exit(EXIT_FAILURE);
		}
		putchar('\n');
		for (i = 0;i < n;i++)
		{
			puts(p[i]);
			free(p[i]);
			p[i] = NULL;
		}
		free(p);
		p = NULL;
	}
	else
		exit(EXIT_FAILURE);

	return 0;
}*/
/*
int* make_array(int elem, int val);
void show_array(const int ar[], int n);
int main(void)
{
	int* pa;
	int size;
	int value;
	printf("Enter the number of elements: ");
	while (scanf("%d", &size) == 1 && size > 0)
	{
		printf("Enter the initialization value: ");
		scanf("%d", &value);
		pa = make_array(size, value);
		if (pa)
		{
			show_array(pa, size);
			free(pa);
		}
		printf("Enter the number of elements (<1 to quit): ");
	}
	printf("Done.\n");
	return 0;
}
int* make_array(int elem, int val)
{
	int* p;
	p = (int*)malloc(elem * sizeof(int));
	for (int i = 0;i < elem;i++)
		p[i] = val;
	return p;
}
void show_array(const int ar[], int n)
{
	for (int i = 0;i < n;i++)
	{
		printf("%3d", ar[i]);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
}*/
/*
extern int vit(int n);
extern int rand1();
int main()
{
	int n=1;
	for(int i=1;i<=10;i++)
	{
		n++;
		vit(n);
	
		int m1, m2, m3, m4, m5, m6, m7, m8, m9 , m10;
			m1 = m2 = m3 = m4 = m5 = m6 = m7 = m8 = m9 = m10 = 0;
		for (int i = 0;i < 1000;i++)
		{
		switch (rand1())
			{
			case 1:m1++;break;
			case 2:m2++;break;
			case 3:m3++;break;
			case 4:m4++;break;
			case 5:m5++;break;
			case 6:m6++;break;
			case 7:m7++;break;
			case 8:m8++;break;
			case 9:m9++;break;
			case 10:m10++;break;
			default:break;
			}
		}
		printf("1=%d 2=%d 3=%d 4=%d 5=%d\n6=%d 7=%d 8=%d 9=%d 10=%d", m1, m2, m3, m4, m5, m6, m7, m8, m9, m10);
		puts("\n");
	}
	return 0;
}*/
/*
extern int rand1();
extern int vit(int n);
int main()
{
	int n;
	int s[100];
	scanf("%d", &n);
	vit(n);
	for (int i = 1;i <= 100;i++)
	{	
		s[i - 1] = rand1();
		printf("%5d", s[i - 1]);
		if (i % 10 == 0)
			puts("\n");
	}
	int m;
	puts("\n");
	for (m = 0;m < 99;m++)
	{
		for (int i = m + 1;i < 100;i++)
		{
			if (s[m] > s[i])
			{
				int j = s[m];
				s[m] = s[i];
				s[i] = j;
			}
		}
	}
	for (int i = 1;i <= 100;i++)
	{
		printf("%5d", s[i - 1]);
		if (i % 10 == 0)
			puts("\n");
	}
	return 0;
}*/
/*
int c = 0;
void count();
int main()
{
	int i = 0;
	scanf("%d",&i);
	for (int j = 0;j < i;j++)
	{
		count();
		printf("%d\n",c);
	}



	return 0;
}
void count()
{
	c++;
}*/
/*//int i;
//	for(i=argc-1;i>0;i--)
	//{
	//	printf("%s",argv[i]);

	//}*/
/*char ch;
	int word, upw, low, pun, dig;
	word = upw = low = pun = dig = 0;
	bool in = false;
	while ((ch = getchar()) != EOF)
	{
		if (!isspace(ch) && !in)
		{
			word++;
			in = true;
		}
		if (isspace(ch) && in)
		{
			in = false;
		}
		if (isupper(ch))
			upw++;
		else if (ispunct(ch))
			pun++;
		else if (isdigit(ch))
			dig++;
		else if (islower(ch))
			low++;
	}
	printf("word=%d\n",word);
	printf("low=%d\n",low);
	printf("dig=%d\n", dig);
	printf("pun=%d\n", pun);
	printf("upw=%d\n", upw);*/
/*
void es(char* s)
{
	char* p = s;
	while (*s)
	{
		if (*s != ' ')
		{
			*p++ = *s++;
		}
		else
		{
			s++;
		}
	}
	*p = '\0';
}*/
/*
void es(char* s);
char* s_gets(char* st, int n);
int main()
{
	char s[10];
	while (s_gets(s, 10) != NULL && s[0] != '\0')
	{
		es(s);
		puts(s);
	}


	return 0;
}
void es(char* s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			for (int j = i;s[j] != '\0';j++)
				s[j] = s[j + 1];
			i++;
		}
		else
			i++;	
	}
}
char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
		{
			*find = '\0';
		}
		else
		{
			while (getchar() != '\n')
				continue;
		}
	}
	return ret_val;
}*/
/*
char* reverse(char* s)
{
	int i = 0;
	int j = strlen(s);
	char temp;
	for (;i < j/2;i++)
	{
		temp = s[i];
		s[i] = s[j - i - 1];
		s[j - i - 1] = temp;
	}
	return s;

}*/
/*
char* string_in(char* da, char* x);
int main()
{

	return 0;
}
char* string_in(char* da, char* x)
{
	int i = 0;
	int j = 0;
	int ld = strlen(da);
	int lx = strlen(x);
	while (i < ld && j < lx)
	{
		if (da[i] == x[j])
		{
			i++;
			j++;
		}
		else
		{//差值是累计不同数
			i = i - j + 1;
			j = 0;
		}
	}
	return j == lx ? x : NULL;
}*/
/*
char* mystrncpy(char* s, char* sa, int n);
void eatline(void);
char* s_gets(char* st, int n);
int main()
{
	char sour[10];
	char targ[10];
	int n;
	while (s_gets(sour, 10) != NULL)
	{
		while ((scanf("%d", &n)) != 1 || n < 1)
		{
			eatline();
		}
		eatline();
		printf("%s\n",mystrncpy(targ,sour,n));
	}
	return 0;
}
char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
		{
			*find = '\0';
		}
		else
		{
			eatline();
		}
	}
	return ret_val;
}

void eatline(void)
{
	while (getchar() != '\n')
		continue;
	return;
}
char* mystrncpy(char* s, char* sa, int n)
{
	int t = 0;
	while (*sa != '\0' && t < n)
	{
		*(s + t) = *sa++;
		t++;
	}
	*(s + t) = '\0';
	return s;
}*/
/*
#define LEN 10
char* s_gets(char* st, int n);
char* is_within(char ch, char* s);
int main()
{
	char ch;
	char s[LEN];
	while (s_gets(s, LEN) != NULL)
	{
		puts("input your char:");
		ch = getchar();
		while (getchar() != '\n')
			continue;
		if (is_within(ch, s))
			printf("there is %c in the %s", ch,s);
		else
			puts("none!");
	}
	puts("done");
	return 0;
}


char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
		{
			*find = '\0';
		}
		else
		{
			while (getchar() != '\n')
				continue;
		}
	}
	return ret_val;
}
char* is_within(char ch, char* s)
{
	while (*s != '\0')
	{
		if (*s != ch)
		{
			s++;
		}
		else
			return s;
	}
	return NULL;
}*/
/*
char* s_gets(char* s, int n);
char* sch(char* s, char ch);
int main()
{
	char s[10];
	char ch;
	while (s_gets(s, 10) != NULL)
	{
		ch = getchar();
		while (getchar() != '\n')
			continue;
		if (sch(s, ch) != NULL)
			printf("%c", ch);
		else
			printf("none");


	}
		

	return 0;
}
char* s_gets(char* s, int n)
{
	char* p;
	char* e;
	p = fgets(s, n, stdin);
	if (p)
	{
		e = strchr(s, '\n');
		if (e)
		{
			*e = '\0';
		}
		else
		{
			while (getchar() != '\n')
				continue;
		}
	}
	return p;
}
char* sch(char* s, char ch)
{
	while (*s != '\0')
	{
		if (*s != ch)
			++s;
		else
			return s;
	}
	return NULL;
}*/
/*
int main()
{
	int n = 10;
	char st[10];
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
		{
			*find = '\0';
		}
		else
		{
			while (getchar() != '\n')
				continue;
		}
	}
	puts(st);
	return 0;
}*/
/*
char* getword(char *s, int n);
int main()
{
	char s[10];
	while (getword(s, 10) != NULL)
		puts(s);
	puts("done!\n");

	return 0;
}
char* getword(char *s, int n)
{
	int ch;
	char *p= s;
	int i = 0;
	while ((ch = getchar()) != EOF && isspace(ch))
		continue;
	if (ch == EOF)
		return NULL;
	else
	{
		*s++ = ch;
		i++;
	}
	while ((ch = getchar()) != EOF && i < (n - 1) && !isspace(ch))
	{
		*s++ = ch;
		i++;
	}
	*s = '\0';
	if (ch == EOF)
		return NULL;
	else
	{
		while (getchar() != '\n')
			continue;
		return p;
	}



}*/
/*
int main()
{
	char w[5];
	while (fgets(w, 5, stdin) != NULL && w[0] != '\n')
		fputs(w, stdout);


	return 0;
}*/
/*
void getstr(char s[], int n);
int main()
{
	int p[10];
	getstr(p, 10);
	puts(p);
	return 0;
}
void getstr(char s[], int n)
{
	int i = 0;
	for (;i < n - 1;i++)
	{
		s[i] = getchar();
		if (isspace(s[i]))
			break;
	}
	s[i] = '\0';
}*/
/*
#define LEN 10
void getstr(char s[],int n);
int main()
{
	int p[LEN];
	getstr(p, LEN);
	puts(p);




	return 0;
}
void getstr(char s[], int n)
{
	int i = 0;
	for (;i < n-1;i++)
		s[i] = getchar();
	s[i] = '\0';
}*/
/*
#define LEN 5
void getnchar(char a[], int n);
int main()
{
	printf("input %d char:\n",LEN-1);
	char s[LEN];
	getnchar(s, LEN);
	puts(s);
	return 0;
}
void getnchar(char a[], int n)
{
	int i;
	for (i = 0;i < n-1;i++)
		a[i] = getchar();
	a[i] = '\0';
}*/
/*
double f1(double a[][5]);
double f2(double a[]);
double f3(double a[][5]);
double f4(double a[][5]);
int main()
{
	double s[3][5] = { 0 };
	f1(s);
	for (int i = 0;i < 3;i++)
		printf("第%d行平均数为%lf\n",i+1, f2(s[i]));
	printf("总平均数：%lf\n",f3(s));
	printf("最大数：%lf\n",f4(s));
	return 0;
}
double f1(double a[][5])
{
	printf("输入3*5个double数\n");
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 5;j++)
			scanf("%lf", &a[i][j]);
}
double f2(double a[])
{
	double tot = 0;
	for (int i = 0;i < 5;i++)
		tot += a[i];
	return tot/5;
}
double f3(double a[][5])
{
	double tot = 0;
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 5;j++)
			tot += a[i][j];
	return tot / 15;
}
double f4(double a[][5])
{
	double max = a[0][0];
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 5;j++)
			if (max < a[i][j])
				max = a[i][j];
	return max;
}*/
/*
#define n 5
show_arry(int(*p)[n], int l);
two_time(int(*p)[5], int l);

void main()
{
	int s[3][5] = { {1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7} };
	show_arry(s, 3);
	two_time(s, 3);
	show_arry(s, 3);

	return 0;
}
show_arry(int(*p)[n], int l)
{
	for (int i = 0;i < l;i++)
	{
		for (int j = 0;j < n;j++)
			printf("%-5d", p[i][j]);
		putchar('\n');
	}
}
two_time(int(*p)[5], int l)
{
	for (int i = 0;i < l;i++)
	{
		for (int j = 0;j < n;j++)
			p[i][j] *= 2;
	}

}*/
/*
int f(int a[], int  b[], int  c[], int n);
int main()
{



	return 0;
}
int f(int a[], int  b[], int  c[], int n)
{
	for (int i = 0;i < n;i++)
		c[i] = a[i] + b[i];



}*/
/*
int copy(int y[], int s[], int n);
int main()
{
	int ar[3][4] = { { 1,2,3,4 }, { 5,6,7,8 }, { 9,10,11,12 } };
	int s[3][4] = {0};
	for (int i = 0;i < 3;i++)
		copy(ar[i], s[i], 4);
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 4;j++)
			printf("%d\t", s[i][j]);
		printf("\n");
	}
	return 0;
}
int copy(int y[],int s[], int n)
{
	for (int i = 0;i < n;i++)
		s[i] = y[i];
}
*/
/*
int f(double s[], int n);
int main()
{
	double ar[5] = { 1.0,2.3,8.9,5.1,9.0 };
	int m=f(ar, 5);
	printf("%d",m);
	return 0;
}
int f(double s[], int n)
{
	double m = s[0];
	int x=0;
	for (int i = 0;i < n;i++)
		if (m < s[i])
		{
			m = s[i];
			x = i;
		}
	return x;

}*/
/*
#define LEN 10
int r(int*a,int b);
int main()
{

	int ar[LEN] = {1,6,5,10,28,26,54,78,99,8};
	int m= r(ar,LEN);
	printf("max=%d\n\n",m);
	return 0;
}
int r(int*a,int b)
{
	int m=0;
	for (int i = 0;i < LEN;i++,a++)
		if (m < *a)
			m = *a;


	return m;
}*/
/*
f1(double a[], double s[],int n);
f2(double a[], double s[],int n);
f3(double a[], double s[],double* n);



int main(void)
{
	double s[5] = { 1,2,3,4,5 };
	double a2[5], a3[5];
	double a1[5] = { 6,7,8,9,10 };
	double* p;
	f1(a1, s, sizeof(s) / sizeof(s[0]));
	f2(a2, s, sizeof(s) / sizeof(s[0]));
	f3(a3, s,s+ sizeof(s) / sizeof(s[0])-1);
	for (int i = 0;i < 5;i++)
		printf("数组a1:%lf\n",a1[i]);
	for (int i = 0;i < 5;i++)
		printf("数组a2:%lf\n",a2[i]);
	for (int i = 0;i < 5;i++)
		printf("数组a3:%lf\n",a3[i]);
	



	return 0;
}
f1(double a[], double s[], int n)
{
	for (int i = 0;i < n;i++)
		a[i] = s[i];


}
f2(double a[], double s[], int n)
{
	for (int i = 0;i < n;i++,a++,s++)
		*a = *s;


}
f3(double a[], double s[], double* n)
{
	int i = 0;
	do 
	{
		a[i] = s[i];
	} while (&s[i++] != n);
}*/
/*
f(int x, int y);
int x, y;
x = 5;
y = 10;
printf("x=%d\ny=%d", x, y);
f(x, y);
printf("x=%d\ny=%d", x, y);
f(int x, int y)
{
	int z;
	z = x;
	x = y;
	y = z;


}*/
/*
int fbqn()
{
	long long int a, b,c;
	a = b = c = 1;
	printf("1  1  ");
	for (int i=0;i<40;a=b,b=c,i++)
	{
		if (i % 10 == 0)
			printf("\n");
		c = a + b;
		printf("%lld  ", c);
	}

}
int main()
{
	fbqn();


	return 0;
}*/
/*
double power(double n, int p);

int main(void)
{
	double x, xpow;
	int exp;

	printf("Enter a number and the integer power");
	printf(" to which\nthe number will be raised. Enter q");
	printf(" to quit.\n");
	while (scanf("%lf %d", &x, &exp) == 2)
	{
		xpow = power(x, exp);
		printf("%.3g to the power %d is %.5g.\n", x, exp, xpow);
		printf("Enter next pair of numbers or q to quit.\n");
	}
	printf("Hope you enjoyed this power trip -- bye!\n");

	return 0;
}

double power(double n, int p)
{
	double pow = 1.0;

	if ((0 == p) && (0 == n))
	{
		printf("0 to the 0 undefined, using 1 as the value.\n");
		return pow;
	}
	if (0 == n)
	{
		pow = 0.0;
		return pow;
	}
	if (0 == p)
	{
		return pow;
	}
	if (p > 0)
	{
		return n * power(n, p - 1);
	}
	else
	{
		return power(n, p + 1) / n;
	}
}



*/
/*
double power(double a,int b);
int main()
{
	double a;
	int b;
	printf("输入底数:\t输入幂:\n");
	while (scanf("%lf%d", &a, &b) == 2)
	{
		if (a < 0)
		{
			printf("请输入正整数\n");
			continue;
		}
		else
		{
			printf("输出是%lf\n",power(a,b));
		}



	}

	return 0;
}
double power(double a, int b)
{
	double x = 1.0;
	if (a == 0 && b == 0)
	{
		printf("未定义，显示1\n");
		return 1;
	}
	else if (a == 0)
		return 0;
	else if (b == 0)
		return 1;
	else if (b > 0)
	{
		for (int i = 1, n = a;i <= b;i++)
			x *= n;
		return x;
	}
	else if (b < 0)
	{
		for (int i = 1, n = a;i <= -b;i++)
			x *= 1.0/n;
		return x;
	}
	




}*/
/*
int alpha(int m);
int main()
{
	int ch;
	while ((ch = getchar()) != EOF)
	{
		int  m=alpha(ch);
		printf("%c位置在%d\n",ch,m);
	}


	return 0;
}
int alpha(int m)
{
	int n=tolower(m);
	if (isalpha(n))
	{
		printf("%c是字母\n",n);
		return n - 'a' + 1;
	}
	else
		return -1;
}*/
/*int m(int* a, int* b, int* c);
int main(void)
{
	int a, b, c;
	printf("Enter your a:\tb:\tc:\n");
	scanf("%d%d%d",&a,&b,&c);
	m(&a, &b, &c);
	printf("%d < %d < %d\n",a,b,c);




	return 0;
}
int m(int *a, int *b, int *c)
{
	int d;
	do
	{
		if (*a > *b)
		{
			d = *a;
			*a = *b;
			*b = d;
		}
		if (*b > *c)
		{
			d = *b;
			*b = *c;
			*c = d;
		}

	} 
	while (!(*a<*b<*c));
	return;
}*/
/*int w = 0, l = 0;
	char ch;
	bool x = false;
	while ((ch = getchar()) != EOF)
	{
		if (ispunct(ch))
			continue;
		if (isalpha(ch))
		{
			l++;
			x = true;
		}
		if (isspace(ch) && x)
		{
			w++;
			x = false;
		}
		
			
		




	}
	printf("w=%d\tl=%d\n",w,l);*/
/*
int main(void)
{
	int ch;
	int i = 0;

	printf("Please enter some characters:\n");
	while ((ch = getchar()) != EOF)
	{
		if (i++ == 10)
		{
			putchar('\n');
			i = 1;
		}
		if (ch >= 32) //空格的十进制ASCII码;
		{
			printf(" \'%c\' - %3d ", ch, ch);
		}
		else if (ch == '\n')
		{
			printf(" \\n - \\n\n ");
			i = 0;
		}
		else if (ch == '\t')
		{
			printf(" \\t - \\t ");
		}
		else
		{
			printf(" \'%c\' - ^%c ", ch, ch + 64);
		}
	}
	puts("Done.");

	return 0;
}
*//**/
/*
int main(void)
{
	int ch;
	int i=0;
	while ((ch = getchar()) != EOF)
	{
		if (i++ == 10) 
		{
			printf("\n");
			i = 1;
		}
		if (ch >= 32)
			printf("   %c  %d", ch, ch);
		else if (ch == '\n')
			printf("   \\n  %d",ch);
		else if(ch=='\t')
			printf("   \\t  %d", ch);
		else
            printf("   %c  %d", ch,ch+64);
		
	
			
		

	}

	return 0;
}*/
/*int ch;
	int ct = 0;
	while ((ch=getchar()) != EOF)
	{
		ct++;
	}
	printf("%d",ct);*/
/*int susu(int n);
int main(void)
{
	int n;
	printf("Enter your num:");
	while (scanf("%d",&n)!=1)
	{
		printf("Enter your num again:");
		scanf("%d", &n);
	}
	while (n<=0)
		{
		printf("Enter your num again:");
		scanf("%d", &n);
		}
	for (int i = 1;i <= n;i++)
		susu(i);






	return 0;
}
int susu(int n)
{
	int i = 2;
	if (n == 2)
	{
		printf("2是素数\n");
		return 2;
	}
	else if (n == 1)
		printf("1算是素数\n");
	for (i = 2; i < n; i++)
	{
		int m = n % i;
		if (m == 0)
		{
			//printf("%d不是素数\n", n);
			break;
		}
	}
	if (i == n)
	{
		printf("%d是素数\n", n);
		return n;
	}

}*/
/*void menu(void);
int choice(void);
void show(double i,double j);
int main()
{
	int ch;
	double hour=0.0;
	menu();
	while ((ch=choice())!=5)
	{
		printf("Enter your hours:\n");
		while (scanf("%lf",&hour)!=1 || (hour<0))
		{
			printf("Enter your hours again:\n");
		}
		switch (ch)
		{
		case 1:show(8.75,hour);break;
		case 2:show(9.33, hour);break;
		case 3:show(10.00, hour);break;
		case 4:show(11.20, hour);break;
		case 5:break;
		default:
			break;
		}
	}
	return 0;
}
void menu(void)
{
for (int i = 0; i < 40; i++)
{
	printf("*");
}
printf("\nEnter the number\n");
printf("1)$8.75/hr\t\t");
printf("2)$9.33/hr\n");
printf("3)$10.00/hr\t\t");
printf("4)$11.20/hr\n");
printf("5)quit\n");
for (int i = 0; i < 40; i++)
{
	printf("*");
}
printf("\n");
}
int choice(void)
{
	int i;
	scanf("%d",&i);
	return i;
}
void show(double i, double j) 
{
	double s,s1;
	if (j<=40)
	{
		s = i * j;
	}
	else
	{
		s = i * (40 + (j - 40) * 1.5);
	}
	if (s <= 300)
		s1 = s * 0.15;
	else if (s <= 450)
		s1 = 300 * 0.15 + 0.2 * (s - 300);
	else
		s1 = 300 * 0.15 + 0.2 * 150 + (s - 450) * 0.25;

	printf("总工资：%lf\n",s);
	printf("税金：%lf\n",s1);
	printf("净收入：%lf\n",s-s1);
	return;
}*/
/*int ch;
	int i = 0;
	while ((ch=getchar())!='#')
	{
		switch (ch)
			
		{
		case '.':putchar('!');
			i++;break;
		case '!':printf("!!");
			i++;break;
		default:
			putchar(ch);
			break;
		}

	}
	printf("%d",i);*/
/*int ch;
	int i=0;
	while ((ch=getchar())!='#')
	{
		if (ch=='.')
		{
			putchar('!');
			i++;
		}
		else if(ch=='!')
		{
			printf("!!");
			i++;
		}
		else
			putchar(ch);

	}
	printf("\n%d",i);*/
/*int  n,o,d,so,sd;
	n = o = d = sd = so = 0;
	while (scanf("%d",&n)==1&&(n!=0))
	{
		if (n % 2 == 0)
		{
			d++;
			sd += n;
		}
		else
		{
			o++;
			so += n;
		}

	}
	if (o != 0 && d != 0)
		printf("奇数个数：%d\n偶数个数：%d\n奇数平均：%d\n偶数平均：%d\n", o, d, so / o, sd / d);
	else
		printf("done");*/
/*char ch;
	int i = 0;
	while ((ch=getchar())!='#')
	{
		
		if (i % 8 == 0)
			putchar('\n');
		i++;
		if (ch == '\t')
			printf("\\t%5d",ch);
		if(ch=='\n')
			printf("\\n%5d", ch);
		else 
			printf("   %5d", ch);
	}*/
/*char ch;
	int i = 0;
	while ((ch = getchar()) != '#')
	{
		
		i++;
	}
	printf("i=%d\nch=%c\ncc=%d\n",i,ch,ch);
	*/
/*	int main(void)
	{
		int ch;
		int i = 0;

		printf("Enter some characters('#' to quit):\n");
		while ((ch = getchar()) != STOP)
		{
			if (i++ % 8 == 0)
			{
				putchar('\n');
			}
			if (ch == '\n')
			{
				printf("'\\n'-%3d ", ch);
			}
			else if (ch == '\t')
			{
				printf("'\\t'-%3d ", ch);
			}
			else
			{
				printf("'%c'-%3d ", ch, ch);
			}
		}
		printf("Done.\n");

		return 0;
	}
*/
/*char in;
	int k = 0, h = 0, s = 0;
	in=getchar();
	while (in!='#')
	{
		if (in == ' ')
		{
			k++;
		}
		else if (in == '\n')
			h++;
		else
			s++;
		in=getchar();
	}
	printf("k=%d\nh=%d\ns=%d",k,h,s);
	*/
/*int s = 5, z = 0;
	do
	{
		s = (s - z-1) * 2;
		z++;
		printf("num=%d\nweeks=%d\n",s,z);
	} while (s<=150);*/
/*int s = 100,i=0;
	do 
	{
		s = s * 1.08-10;
		i++;

	} while (s>9);
	printf("%d\n%d",++i,s);
	*/
/*int s1=100, s2=100;
	int i = 1;
	do
	{
		s1 = 100 + 10 * i;
		s2 = s2 * 1.05;
		i++;
	} while (s1>=s2);
	printf("i=%d\ns1=%d\ns2=%d",i,s1,s2);
	*/
/*char n[9];
	int i = 0;
	do
	{
		scanf("%c",&n[i]);
		
	} while (n[i]!='\n' && ++i);
	for (i--;i >= 0;i--)
		printf("%c", n[i]);
	printf("\ndone");
	*/
/*	double n[8];
	double m[8];
	int i = 0;
	for (i=0;i < 8;i++)
		scanf("%lf",&n[i]);
	//嵌套
	i = 0;
	for (int s;i < 8;i++)
	{
		s = 0;
		for (int j = 0;j <= i;j++)
			s += n[j];
		m[i] = s;
     }
	
	//for (i = 0, m[i] = n[i];i < 7;i++)
		//m[i + 1] = m[i] + n[i + 1];
	for (i = 0;i < 8;i++)
		printf("%5.1lf",n[i]);
	printf("\n");
	for (i = 0;i < 8;i++)
		printf("%5.1lf", m[i]);
	*/
/*int n[8],i;
	for (i = 0, n[0] = 2;i < 7;i++)
		n[i + 1] = 2 * n[i];
	i = 0;
	do
	{
		printf("%5d",n[i]);
	i++;
	}
	while (i<8);*/
/*	int l;
	scanf("%d", &l);
	while (l>0)
	{
		double s1 = 0.0, s2 = 0.0, s;
      for (int i = 1;i <= l;i++)
			s1 += (1.0 / i);
	  printf("%lf\n",s1);
	  for (int i = 1;i <= l;i++)
	  {
		  if (i % 2 == 1)
			  s2 += (1.0 / i);
		  else
			  s2 -= (1.0 / i);
	  }
	  s = s1 + s2;
	  printf("%lf\n", s2);
	  printf("sun=%lf\n", s);
	  s = 0.0;
	for (int i = 0; i <= l; i++)
	{
			  if (i % 2 != 0)
				  s = s + 2 * 1.0 / i;
	}
	printf("sun=%lf\n", s);
	  
	  scanf("%d", &l);
		
	}	
		*/
/*	int n[8];
	for (int i = 0;i < 8;i++)
		scanf("%d",&n[i]);
	for (int i = 7;i >= 0;i--)
		printf("%5d",n[i]);
	printf("\ndone!");
*/
/*	int n, m;
	scanf("%d%d",&n,&m);
	while (n<m)
	{
		int s=0;
		for (int i = n;i <= m;i++)
			s += i * i;
		printf("%d",s);
		scanf("%d%d", &n, &m);
	}
	printf("done");
	*/
/*	float n, m;
	while (scanf("%f%f",&n,&m)== 2 )
	
		printf("%f",(n-m)/(n*m));
	
	printf("num error");
*/
/*	int n, m;
	scanf("%d",&n);
	scanf("%d",&m);
	printf("原始：   平方：   立方：   \n");
	for (int i = n;i <= m;i++)
		printf("%6d%10d%10d\n",i,i*i,i*i*i);
	*/
/*	char c, ch;
	int j;
	scanf("%c",&c);
	int n = c - 'A' + 1;
	for (int i = 1;i <= n;i++)
	{
		for (j = 1;j <= n - i;j++)
			printf(" ");
		for (ch = 'A';j <= n;j++)
			printf("%c",ch++);
		for (ch -= 2,j=1;j<i;j++,ch--)
			printf("%c",ch);
		printf("\n");
     }
*/
/*char c;
	scanf("%c", &c);
	int n = c - 'A' + 1;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= n - i;j++)
			printf(" ");
		for (int x = 1;x <= i;x++)
			printf("%c",'A'+x-1);
		for (int x = 1;x < i;x++)
			printf("%c", 'A' + i-1-x);
		
		

		printf("\n");
	}
*/
/*	int n = 6;
	char m = 'A';
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= i;j++, m++)
			printf("%c",m);
		printf("\n");
		}
*/
/*char c;
	int n = 6;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1, c = 'F';j <= i;j++,c--)
			printf("%c",c);
		printf("\n");
	}
*/
/*int n = 5;
	for (int row = 1;row <= n;row++,printf("\n"))
		for (int m = 1;m <= row ;m++)
			printf("$");
*/
/*#define SIZE 26

int main()
{
	char n[SIZE];
	for (int m = 0;m < SIZE;m++)
	{
		n[m] = 'a' + m;
		printf("%c\n",n[m]);
	}

	




	return 0;
}
*/
/*
double n3(double n);
int main()
{
	double n,m;
	scanf("%lf",&n);
	m = n3(n);
	
printf("%f", m);

	return 0;
}
double n3(double n)
{
	double m = n * n * n ;
	
	return m;
}*/
/*
int main()
{

	int n,m;
	scanf("%d",&n);
	m = n + 10;
	while (n <= m)
	{
		printf("%d ",n);
		n++;
	}
	printf("done!");


	return 0;
}

*/
/*#define MIN  60
int main()
{
	int min;
	int hour;
	int left;

	printf("输入分钟（小于等于0时退出）\n");
		scanf("%d",&min);
	while (min > 0)
	{
	
		hour = min / MIN;
		left = min % MIN;
		printf("时间是%d时%d分钟\n",hour,left);
		printf("输入分钟（小于等于0时退出）\n");
		scanf("%d", &min);
	}
	printf("完成！");


return 0;
}
*/
//char x[20],m[20];
	//int long1, long2;
	//printf("请输入您的姓\n");
	//scanf("%s",x);
	//printf("\n请输入您的名\n");
	//scanf("%s", m);
	//printf("\n%s%s\n",x,m);
	//long1 = strlen(x);
	//long2 = strlen(m);
	//printf("%-*d%-*d",long1,long1,long2,long2);
	//int age;
	//float sec = 3.156e7;
	//scanf("%d",&age);
	//printf("%.3e\n%.3f",age*sec,age*sec);
	//char ch[20];
	//int size, letters;
	//scanf("%s",ch);
	//printf("%s",ch);
	//size = sizeof(ch);
	//letters = strlen(ch);
	//printf("%d\n\n%d",size,letters);
	//float a = 9.0e2;
	//printf("%f",a);
	//int i = 2147483647;
	//unsigned int j = 4294967296;
	//printf("%d %d %d\n",i,i+1,i+2);
	//printf("%d %d %d\n", j, j + 1, j + 2);
	//printf("%d",sizeof(int));
/*













nt a[100001];
void qsort(int a[], int l,int r)
{
	int mid = a[(l + r) / 2];
	int i = l, j = r;
	do {
		while (a[i] < mid)i++;
		while (a[j] > mid)j--;
		if (i <= j) {
			swap(a[i], a[j]);
			i++;j--;
		}
	} while (i <= j);
	if (l < j)qsort(a, l, j);
	if (i < r)qsort(a, i, r);
}
int n;
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i];
	qsort(a,1, n);
	for (int i = 1;i <= n;i++) cout << a[i] << " ";
int n,m;
struct node {
	int v, l,r;
}t[50000000];
int a[20000010];
void pushup(int p) {
	t[p].v = min(t[2 * p].v, t[2 * p + 1].v);
}
void build(int l, int r, int p) {
	t[p].l = l;t[p].r = r;
	if (l == r) {
		t[p].v = a[l];return;
	}
	int mid = (l + r) / 2;
	build(l, mid, 2 * p);
	build(mid + 1, r, 2 * p + 1);
	pushup(p);
}
int query(int p, int l,int r){
	if (l <= t[p].l && t[p].r <= r)return t[p].v;
	int mid = (t[p].l + t[p].r) / 2;
	int a = 2147483647, b = 2147483647;
	if (l <= mid)a = query(p * 2, l, r);
	if (r >= mid + 1)b = query(p * 2 + 1, l, r);
	if (a > b)
		a = b;
	return a;
	//return a < b ? a : b;
}

cin >> n >> m;
	for (int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	build(1,  n,1);
	/*for (int i = 1;i <= 100;i++)
		cout << t[i].v << ' ';*/
cout << 0 << endl;
for (int i = 2;i <= n;i++)
{

	if (i - m > 1)
		cout << query(1, i - m, i - 1) << '\n';
	else
		cout << query(1, 1, i - 1) << '\n';
}

int a[1000002];
int b[1000002];
int t[1000002];
void pushup(int n) {
	t[n] = t[2 * n] + t[2 * n + 1];
}
void build(int n, int st, int end) {
	if (st == end){
		t[n] = a[st];return;
	}
	int mid = (st + end) / 2;
	build(2 * n, st, mid);
	build(2 * n + 1, mid + 1, end);
	pushup(n);
}
void pushdown(int n, int l) {
	if (b[n]) {
		b[2 * n] ^= 1;
		b[2 * n + 1] ^= 1;
		t[2 * n] = l - l / 2 - t[2 * n];
		t[2 * n + 1] = l / 2 - t[2 * n + 1];
		b[n] = 0;
	}
}
void update(int L, int R, int l, int r,int n) {
	if (r < L || R < l) {
		return;
	}
	if (L >= l && r >= R) {
		b[n] ^= 1;
		t[n] = R - L + 1 - t[n];
		return;
	}
	pushdown(n,R-L+1);
	int mid = (L + R) / 2;
	update(L, mid, l, r, 2 * n);
	update(mid+1,R, l, r, 2 * n+1);
	pushup(n);
}
int query(int L, int R, int l, int r, int n) {
	if (r < L || R < l) {
		return 0;
	}
	if (L >= l && r >= R)return t[n];
	pushdown(n, R - L + 1);
	int mid = (L + R) / 2;
	return query(L, mid, l, r, 2 * n) + query(mid + 1, R, l, r, 2 * n + 1);
}
void print(int n)
{

}
freopen("C:P2574_2.in", "r", stdin);
	int n, m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++) {
		char ch;
		cin >> ch;
		a[i] = ch - '0';
	}
	build(1, 1, n);
	while (m--) {
		int k, l, r;
		cin >> k >> l >> r;
		if (!k)
			update(1, n, l, r, 1);
		else
			cout << query(1, n, l, r, 1) << endl;
	}
build(1, 1, n);
	while (m--) {
		int k,l,r;
		cin >> k>>l>>r;
		if (!k)
			addf(1, 1, n, l, r, 1);
		else
			cout << query(1, 1, n, l, r) << endl;
	}
struct node {
	int  add, mul, val;
}tree[200000];
void build(int node, int st, int end) {
	tree[node].mul = 1;
	tree[node].add = 0;

	if (st == end) {
		tree[st].val = a[st];
		return;
	}

	int mid = (st + end) / 2;
	build(node*2, st, mid);
	build(node*2+1, mid + 1, end);

	tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
}
void push_down(int node, int l, int r) {
	int mid = (l + r) / 2;

	tree[node * 2].val = tree[node * 2].val * tree[node].mul + tree[node].add * (mid - l + 1);
	tree[node * 2 + 1].val = tree[node * 2 + 1].val * tree[node].mul + tree[node].add * (r - mid);

	tree[node * 2].mul = tree[node * 2].mul * tree[node].mul;
	tree[node * 2+1].mul = tree[node * 2+1].mul * tree[node].mul;

	tree[node * 2].add = tree[node * 2].add * tree[node].mul + tree[node].add;
	tree[node * 2+1].add = tree[node * 2+1].add * tree[node].mul + tree[node].add;

	tree[node].mul = 1;
	tree[node].add = 0;

}
void mulp(int node, int L, int R, int l, int r,int k) {
	if (r < L || R < l) return;
	if (l <= L && R <= r) {
		tree[node]. val = tree[node].val * k;
		tree[node].mul *= k;
		tree[node].add *= k;

		tree[node].add %= 2;

		return;
	}
	push_down(node, L, R);
	int mid = (L + R) / 2;
	mulp(node * 2, L, mid, l, r, k);
	mulp(node * 2 + 1, mid + 1, R, l, r, k);

	tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;

	//tree[node].val %= 2;

}
void addf(int node, int L, int R, int l, int r, int k) {
	if (r < L || R < l)return;
	if (l <= L && R <= r) {
		tree[node].add += k;
		tree[node].val += k * (R - L + 1);
		return;
	}
	push_down(node, L, R);
	int mid = (L + R) / 2;
	addf(node * 2, L, mid, l, r, k);
	addf(node * 2 + 1, mid+1, R  , l, r, k);

	tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
}
int query(int node, int L, int R, int l, int r) {
	if (r < L || R < l)return 0;
	if (l <= L && R <= r) {
		return tree[node].val;
	}
	push_down(node, L, R);
	int mid = (L + R) / 2;
	return query(node * 2, L, mid, l, r) + query(node * 2 + 1, mid + 1, R, l, r);
}
#define MAXN 1000001
#define ll long long
ll a1, b, c, d, e, f;
	scan();
	build(1, 1, n);
	while (m--)
	{
		scanf("%lld", &a1);
		switch (a1)
		{
		case 1: {
			scanf("%lld%lld%lld", &b, &c, &d);
			update(b, c, 1, n, 1, d);
			break;
		}
		case 2: {
			scanf("%lld%lld", &e, &f);
			printf("%lld\n", query(e, f, 1, n, 1));
			break;
		}
		}
	}
ll n, m, a[MAXN], ans[MAXN << 2], tag[MAXN << 2];
inline ll ls(ll x) { return x << 1; }
inline ll rs(ll x) { return x << 1 | 1; }
void scan()
{
	cin >> n >> m;
	for (ll i = 1;i <= n;i++)
		scanf("%lld", &a[i]);
}
inline void push_up(ll p)
{
	ans[p] = ans[ls(p)] + ans[rs(p)];
}
void build(ll p,ll l, ll r)
{
	tag[p] = 0;
	if (l == r) { ans[p] = a[l];return; }
	ll mid = (l + r) >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	push_up(p);
}
inline void f(ll p, ll l, ll r, ll k)
{
	tag[p] = tag[p] + k;
	ans[p] = ans[p] + k*(r - l + 1);
}
inline void push_down(ll p, ll l, ll r)
{
	ll mid = (l + r) >> 1;
	f(ls(p), l, mid, tag[p]);
	f(rs(p), mid + 1, r, tag[p]);
	tag[p] = 0;
}
inline void update(ll nl, ll nr, ll l, ll r, ll p, ll k)
{
	if (nl <= l && r <= nr)
	{
		ans[p] += k * (r - l + 1);
		tag[p] += k;
		return;
	}
	push_down(p, l, r);
	ll mid = (l + r) >> 1;
	if (nl <= mid)update(nl, nr, l, mid, ls(p), k);
	if (nr > mid)update(nl, nr, mid + 1, r, rs(p), k);
	push_up(p);
}
ll query(ll q_x, ll q_y, ll l, ll r, ll p)
{
	ll res = 0;
	if (q_x <= l && r <= q_y)return ans[p];
	ll mid = (l + r) >> 1;
	push_down(p, l, r);
	if (q_x <= mid)res += query(q_x, q_y, l, mid, ls(p));
	if (q_y > mid)res += query(q_x, q_y,mid+1,r, rs(p));
	return res;
}
ll a1, b, c, d, e, f;
	scan();
	build(1, 1, n);
	while (m--)
	{
		scanf("%lld", &a1);
		switch (a1)
		{
		case 1: {
			scanf("%lld%lld%lld", &b, &c, &d);
			update(b, c, 1, n, 1, d);
			break;
		}
		case 2: {
			scanf("%lld%lld", &e, &f);
			printf("%lld\n", query(e, f, 1, n, 1));
			break;
		}
		}
	}
#define PI acos(-1.0)
int n, f, c;
double a[10002];
scanf("%d%d", &n, &f);double max = -1;
	for (int i = 1;i <= n;i++)
	{
		scanf("%lf", &a[i]);
		a[i] = a[i] * a[i] * PI;
		if (a[i] > max)
			max = a[i];
	}f++;
	double l = 0.0, r = max;
	double m = 0;
	while (r - l > 0.000009)
	{
		m = (l + r) / 2;
		c = 0;
		for (int i = 1;i <= n;i++)
		{
			c += floor(a[i] / m);
		}
		if (c >= f)
			l = m;
		else
			r = m;
	}
	printf("%.3lf", m);
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<queue>
#include<algorithm>
#include<time.h>
#include<stack>
#define PI acos(-1.0)
using namespace std;
int n, f,c;
double a[10002];
int main()
{
	scanf("%d%d", &n, &f);double max = 0.0;
	for (int i = 1;i <= n;i++)
	{
		scanf("%lf", &a[i]);
		a[i] = a[i] * PI *a[i];
		if (a[i] > max)
			max = a[i];
	}f++;
	double l = 0.0, r = max * 1.0;
	double m = (l + r)/2;
	while (r-l>0.000009)
	{
		c = 0;
		for (int i = 1;i <= n;i++)
		{
			c += (int)a[i] / m;
		}
		if (c > f)
		{
			l = m;
		}
		else
		{
			r = m;
		}
		m = (l + r) / 2;
	}
	printf("%.4lf", m);
	return 0;
}
#define N 1200000
#define INF 0x3f3f3f3f

int dp[N];
int a[N];

 int n, m, T, i, j;

	scanf("%d", &T);

	while (T--)
	{
		scanf("%d %d", &n, &m);
		memset(dp, 0, sizeof(dp));

		for (i = 1;i <= n;i++)
		{
			scanf("%d", &a[i]);
			dp[i] = dp[i - 1] + a[i];
		}

		int minn = INF, i = 1,x=0;;
		for (j = 1;j <= n;j++)
		{
			if (dp[j] - dp[i - 1] < m)
				continue;
			while (dp[j] - dp[i] >= m)
				i++;
			//minn = min(minn, j - i + 1);
			if (minn > j - i + 1)
			{
				minn = j - i + 1;
				x = i;
			}
		}

		if (minn == INF)
			if(T)
			printf("0\n0\n");
			else
				printf("0\n0");

		else
		{
			printf("%d\n", minn);
			for(int i=x;i<minn+x-1;i++)
				printf("%d ", a[i]);printf("%d", a[minn + x - 1]);
			printf("\n");
		}
	}
#include<iostream>
#include<cstdio>
using namespace std;
int  m, n, s, a[1000001], b[1000011];
int read()
{
	char c = getchar();int x = 0, f = 1;
	while (c < '0' || c>'9')if (c == '-')f = -1, c = getchar();
	while (c >= '0' && c <= '9')x = x * 10 + c - '0', c = getchar();
	return x * f;
}
int main()
{
	m = read();
	while (m--)
	{
		n = read(), s = read();
		for (int i = 1;i <= n;i++)
		{
			a[i]=read();b[i] = b[i - 1] + a[i];
		}
		if (b[n] < s)
		{
			cout << 0 << '\n' << 0 << endl;continue;
		}
		int ans = 999999;int lo=0;
		for (int i = 1;i <=n;i++)
		{
			int l = i;
			if (b[n] - b[l - 1] < s)break;
			int r = n;
			while (l < r)
			{
				int mid = (l + r) >> 1;
				if (b[mid] - b[i - 1] < s)l = mid + 1;
				else r = mid;
			}
			if (ans > r - i + 1)
			{
				ans = r - i + 1;
				lo = i;
			}
		}
		cout << ans << '\n';
		for (int i = lo;i <= ans+lo-1;i++)
			cout << a[i] << ' ';
		cout << endl;
	}



	return 0;
}
int gcd(int n)
{
	int s = 0;
	for (int i = 1;i < n;i++)
		if (n % i == 0)s += i;
	return s;
}
int n;
int a[1001], dp[1001];
/**/
*/

/*


/*






int t, m;
int a[1000], v[1000], dp[1000][1000];
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;
int t, m;
int a[1000], v[1000], dp[1000][1000];
int main()
{
	cin >> t >> m;
	for (int i = 1;i <= m;i++)
		cin >> a[i] >> v[i];
	for (int i = 1;i <= m;i++)
		for (int j = t;j >= 0;j--)
		{
			if (j >= a[i])
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - a[i]] + v[i]);
			else
				dp[i][j] = dp[i - 1][j];
		}
	cout << dp[m][t];
	return 0;
}
int gcd(int n)
{
	int s = 0;
	for (int i = 1;i < n;i++)
		if (n % i == 0)s += i;
	return s;
}
int n;
int a[1001], dp[1001];
cin >> n;
for (int i = 2;i <= n;i++)
a[i] = gcd(i);
for (int i = 1;i <= n;i++)
for (int j = n;j >= i;j--)
{
	dp[j] = max(dp[j], dp[j - i] + a[i]);
}
cout << dp[n];
long long n, m, x, y;
long long a[40][40];long long  dp[40][40];
void ma(long long x, long long y)
{
	a[x + 1][y + 2] = a[x - 1][y + 2] = a[x + 2][y + 1] = a[x + 1][y - 2] = a[x - 1][y - 2] = a[x + 2][y - 1] = a[x - 2][y + 1] = a[x - 2][y - 1] = a[x][y] = 0;
}


for (long long i = 1;i < 33;i++)
	for (long long j = 1;j < 33;j++)
		a[i][j] = 1;
cin >> n >> m >> x >> y;n += 2;m += 2;x += 2;y += 2;
ma(x, y);
for (long long i = 2;i < 33;i++)
	for (long long j = 2;j < 33;j++)
	{
		if (!a[i][j])
			dp[i][j] = 0;
		else
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		dp[2][2] = 1;
	}
cout << dp[n][m];
int a[600], b[600];
void add(int a[], int b[])
{
	a[0] = a[0] > b[0] ? a[0] : b[0];
	for (int i = 1;i <= a[0];i++)
	{
		a[i] = a[i] + b[i];
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	if (a[a[0] + 1])a[0]++;
}
string n, m;
cin >> n >> m;
a[0] = n.length();b[0] = m.length();

for (int i = 1;i <= a[0];i++)
{
	a[i] = n[a[0] - i] - '0';
}
for (int i = 1;i <= b[0];i++)
{
	b[i] = m[b[0] - i] - '0';
}
add(a, b);
for (int i = a[0];i >= 1;i--)
cout << a[i];
int n, m;
char a[200][200];
int dx[3] = { -1,0,1 };
int dy[3] = { -1,0,1 };
cin >> n >> m;
char ch;int s = 0;
for (int i = 1;i <= n;i++)
{
	for (int j = 1;j <= m;j++)
	{
		cin >> a[i][j];
	}
}
for (int i = 1;i <= n;i++)
{
	for (int j = 1;j <= m;j++)
	{
		if (a[i][j] == '*')
			cout << '*';
		else if (a[i][j] == '?')
		{
			s = 0;
			for (int x = 0;x < 3;x++)
				for (int y = 0;y < 3;y++)
				{
					if (a[i + dx[x]][j + dy[y]] == '*')s++;
				}
			cout << s;
		}
	}
	cout << endl;
}
int n;
bool cmp(int x, int y)
{
	return x > y;
}
cin >> n;
int ans = -99999999, k = 0, he = 0;
while (n--)
{
	cin >> k;
	if (he < 0)
		he = 0;
	he += k;
	ans = max(he, ans);
}
cout << ans;
long long n, k;
long long a[2000000], b[2000000];
cin >> n >> k;
for (int i = 1;i < n;i++)
{
	cin >> a[i];
	b[i] = b[i - 1] + a[i];
}
long long ans = 0;
for (int i = 1;i <= n - k;i++)
{
	ans = max(ans, b[i + k - 1] - b[i - 1]);
}
cout << b[n - 1] - ans;
int a[200002], b[200002];
int n;
cin >> n;
for (int i = 1;i <= n;i++)
{
	cin >> a[i];
	b[i] = b[i - 1] + a[i];
}
int s = 0;
for (int i = 1;i <= n;i++)
{
	for (int j = i;j <= n;j++)
	{
		s = max(s, b[j] - b[j - i]);
	}
}
cout << s;

int n;
long long int a[1001];
cin >> n;
for (int i = 1;i <= n;i++)
{
	cin >> a[i];
	a[i] = a[i] * 1001 + i;
}
sort(a + 1, a + 1 + n);
double s = 0.0;
for (int i = 1;i <= n;i++)
{
	cout << a[i] % 1001 << ' ';
	s += a[i] / 1001 * (n - i);
}
cout << endl;
double ans = s / n;
printf("%.2f", ans);
int t, n, m;
int a[5000];
void mul(int a[], int b)
{
	for (int i = 1;i <= a[0];i++)
		a[i] = a[i] * b;
	for (int i = 1;i <= a[0];i++)
	{
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	while (a[a[0] + 1] > 0)
	{
		a[0]++;
		a[a[0] + 1] = a[a[0]] / 10;
		a[a[0]] %= 10;
	}
	return;
}
cin >> t;
a[0] = 1;a[1] = 1;
while (t--)
{
	for (int i = a[0];i >= 0;i--)
		a[i] = 0;
	a[0] = 1;a[1] = 1;
	long long s = 0;
	cin >> n >> m;
	for (int i = 2;i <= n;i++)
		mul(a, i);
	for (int i = a[0];i > 0;i--)
	{
		if (m == a[i])
			s++;
	}
	cout << s << endl;
}
cin >> n >> m;
mul(a, b, c, 2);
void add(int a[])
{
	for (int i = 1;i <= a[0];i++)
	{
		a[i] += 1;
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	if (a[a[0] + 1])a[0]++;
	return;
}
void mul(int a[], int b[], int c[], int k)
{
	for (int i = 1;i <= a[0];i++)
		for (int j = 1;j <= b[0];j++)
			c[i + j - 1] = a[i] * b[j];
	c[0] = a[0] + b[0];
	for (int i = 1;i <= c[0];i++)
	{
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	while (c[0] > 1 && c[c[0]] == 0)c[0]--;
	add(b);
	mul(b, c, a, k + 1);
	return;
}

int n, m, a[100001];
int s;
int b(int l, int r, int k)
{
	if (l == r)
	{
		if (k == a[l])
			return 0;
		else
			if (abs(k - a[l - 1]) > abs(k - a[l]))
				return abs(k - a[l]);
			else
				return abs(k - a[l - 1]);
	}
	int mid = (l + r) / 2;
	if (k <= a[mid])
		b(l, mid, k);
	else
		b(mid + 1, r, k);
}
a[0] = 999999;
cin >> m >> n;
int k;
for (int i = 1;i <= m;i++)
cin >> a[i];
sort(a + 1, a + m + 1);
while (n--)
{
	cin >> k;
	s += b(1, m, k);
}
cout << s;
int n, m;
int a[1000001];
int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c>'9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
n = read(), m = read();
for (int i = 1;i <= n;i++)
a[i] = read();
while (m--)
{
	int t, l = 1, r = n;
	t = read();int mid = (l + r) / 2;
	while (t != a[mid] && l != r)
	{

		if (t > a[mid])
			l = mid + 1;
		else
			r = mid;
		mid = (l + r) / 2;
	}
	if (l == r)
		cout << -1 << ' ';
	else
	{
		while (mid > 0)
		{
			mid--;
			if (t != a[mid])
				break;
		}
		cout << mid + 1 << ' ';
	}
}
using namespace std;
int a[2000], b[1000], c[2000];
int n, m, t;
int add(int a[], int b[], int k)
{
	if (k >= t)
		return 0;
	for (int i = 1;i <= b[0];i++)
	{
		a[i] += b[i];
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	if (a[a[0] + 1])a[0]++;
	add(b, a, k + 1);
	return 0;
}
void print(int a[])
{
	for (int i = a[0];i >= 1;i--)
		cout << a[i];
}
int main()
{
	a[0] = b[0] = 1;a[1] = 0, b[1] = 1;
	cin >> m >> n;n++;t = n - m;
	add(a, b, 1);
	if (t % 2)
		print(b);
	else
		print(a);

	int n, m, x, y;
	int a[40][40];int dp[40][40];
	void ma(int x, int y)
	{
		a[x + 1][y + 2] = a[x - 1][y + 2] = a[x + 2][y + 1] = a[x + 1][y - 2] = a[x - 1][y - 2] = a[x + 2][y - 1] = a[x - 2][y + 1] = a[x - 2][y - 1] = a[x][y] = 0;
	}
	for (int i = 1;i < 33;i++)
		for (int j = 1;j < 33;j++)
			a[i][j] = 1;
	cin >> n >> m >> x >> y;n += 2;m += 2;x += 2;y += 2;
	ma(x, y);
	for (int i = 2;i < 33;i++)
		for (int j = 2;j < 33;j++)
		{

			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			if (!a[i][j])
				dp[i][j] = 0;
			dp[2][2] = 1;
		}
	cout << dp[n][m];
	void print(int a[])
	{
		for (int i = a[0];i >= 1;i--)
			cout << a[i];
	}
	int a[2000], b[1000], c[2000];
	int n;
	int add(int a[], int b[], int k)
	{
		if (k >= n + 1)
			return 0;
		for (int i = 1;i <= b[0];i++)
		{
			a[i] += b[i];
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
		if (a[a[0] + 1])a[0]++;
		add(b, a, k + 1);
		return 0;
	}
	a[0] = b[0] = 1;a[1] = 0, b[1] = 1;
	cin >> n;n++;
	add(a, b, 1);
	if (n == 1) { cout << 0;return 0; }
	if (n % 2)
		print(b);
	else
		print(a);



	int f[3][260], g;
	int n;
	f[0][250] = 1;f[1][250] = 1;cin >> n;
	if (n == 0)
	{
		puts("0");
		return 0;
	}
	for (int i = 2;i <= n;i++)
		for (int j = 250;j > 0;j--)
		{
			f[i % 3][j]
		}
	int n, c = 0;
	int dfs(int k)
	{
		if (k > n)
			return 0;
		if (k == n)
		{
			c++;
			return 0;
		}
		for (int i = 1;i <= 2;i++)
			dfs(k + i);
	}
	cin >> n;
	dfs(0);
	cout << c;
	int n, m, ans = 99999, color[51][4], b[51][51];
	char ch;
	int dfs(int x, int y, int t)
	{
		if (x + y >= n)return 0;
		if (b[x][y]) return 0;
		b[x][y] = 1;
		dfs(x + 1, y, t + color[x + 1][1]);
		dfs(x, y + 1, t + color[n - y][3]);
		if (x > 0 && y > 0 && x + y < n)
		{
			int k = 0;
			for (int i = x + 1;i <= n - y;i++)
			{
				k += color[i][2];
			}
			ans = min(ans, t + k);
		}
	}
	cin >> n >> m;
	for (int i = 1;i <= n;i++)

		*/
		//
		//int ans=999999;
		//int w, b, r;
		//int n, m;
		//int aa[51][3];
		//char a[51][51];
		//void dfs(int  x, int y, int c)
		//{
		//	if (x==y)
		//		return;
		//	for (int i = 1;i <= x;i++)
		//		c += aa[i][1]+aa[i][2];
		//		/*for(int j=1;j<=m;j++)
		//			if (a[i][j] != 'W')c++;*/
		//for (int i = x + 1;i <= y - 1;i++)c += aa[i][0] + aa[i][2];
		///*for (int j = 1;j <= m;j++)
		//	if (a[i][j] != 'B')c++;*/
		//for (int i = y;i <= n;i++)c += aa[i][2] + aa[i][0];
		///*for (int j = 1;j <= m;j++)
		//	if (a[i][j] != 'R')c++;*/
		//ans = min(ans, c);
		//dfs(x + 1, y, 0);
		//dfs(x, y - 1, 0);
		//}
		//cin >> n >> m;
		//for (int i = 1;i <= n;i++)
		//for (int j = 1;j <= m;j++)
		//{
		//	a[i][j] = getchar();
		//	if (a[i][j] == 'W')aa[i][0]++;
		//	else if (a[i][j] == 'B')aa[i][1]++;
		//	else aa[i][2]++;
		//}
		//dfs(1, n, 0);
		//cout << ans;
		//fo(i, 0, m)
		//{
		//	if (a[0][i] != 'W')ans++;
		//	if (a[n - 1][i] != 'R')ans++;
		//}
		//fo()
		//int n, r;
		//int a[1001];
		//void dfs(int k)
		//{
		//	if (k - 1 == r)
		//	{
		//		for (int i = 1;i <= r;i++)
		//			cout << setw(3) << a[i];
		//		cout << endl;
		//		return;
		//	}
		//	for (int i = a[k - 1] + 1;i <= n;i++)
		//	{
		//		a[k] = i;
		//		dfs(k + 1);
		//	}
		//}
		//cin >> n >> r;
		//dfs(1);
		//int t, m;
		//int tc[101], mg[101];
		//void dfs(int tl, int)
		//cin >> t >> m;
		//for (int i = 1;i <= m;i++)
		//cin >> tc[i] >> mg[i];
		//
		//int a[1002][1002];
		//int n;
		//cin >> n;
		//int s = 0;
		//for (int i = 1;i <= n;i++)
		//for (int j = 1;j <= i;j++)
		//{
		//	int p;
		//	cin >> p;
		//	a[i][j] = max(a[i - 1][j - 1], a[i][j]) + p;
		//	s = max(s, a[i][j]);
		//}
		//cout << s;
		//int n, k, c;
		//int dfs(int s, int t)
		//{
		//	if (t > k || s > n)
		//		return 0;
		//	if (t == k)
		//		if (s == n)
		//		{
		//			c++;return 0;
		//		}
		//	for (int i = 1;i < n;i++)
		//	{
		//		if (s + i <= n)
		//			dfs(s + i, t + 1);
		//	}
		//	return 0;
		//}
		//cin >> n >> k;
		//dfs(0, 0);
		//cout << c;
		//int dx[4] = { 1,0,-1,0 };
		//int dy[4] = { 0,-1,0,1 };
		//int a[101][101], s[101][101];
		//int n, m, ans;
		//int dfs(int x, int y)
		//{
		//	if (s[x][y])return s[x][y];
		//	s[x][y] = 1;
		//	for (int i = 0;i < 4;i++)
		//	{
		//		int xx = x + dx[i];
		//		int yy = y + dy[i];
		//		if (xx >= 0 && yy >= 0 && xx < n && yy < m && a[x][y] < a[xx][yy])
		//		{
		//			dfs(xx, yy);
		//			s[x][y] = max(s[x][y], s[xx][yy] + 1);
		//		}
		//	}
		//	return s[x][y];
		//}
		//cin >> n >> m;
		//for (int i = 0;i < n;i++)
		//	for (int j = 0;j < m;j++)
		//		cin >> a[i][j];
		//for (int i = 0;i < n;i++)
		//	for (int j = 0;j < m;j++)
		//		ans = max(ans, dfs(i, j));
		//cout << ans;
		//int read()
		//{
		//	char c = getchar();int x = 0, f = 1;
		//	while (c < '0' || c>'9')if (c == '-')f = -1, c = getchar();
		//	while (c >= '0' && c <= '9')x = x * 10 + c - '0', c = getchar();
		//	return x * f;
		//}
		//int p[101];
		//int a = 0, b = 0, c = 0, d = 0, e = 0;
		//int n, k;
		//n = read();
		//for (int i = 0;i < n;i++)
		//{
		//	p[read()]++;
		//}
		//int i = 0;
		//for (;i < 60;i++)
		//	e += p[i];
		//for (;i < 70;i++)
		//	d += p[i];
		//for (;i < 80;i++)
		//	c += p[i];
		//for (;i < 90;i++)
		//	b += p[i];
		//for (;i <= 100;i++)
		//a += p[i];
		//printf("%d %d %d %d %d", a, b, c, d, e);
		//#include<iostream>
		//#include<cmath>
		//using namespace std;
		//bool prime(int n)
		//{
		//	int x = sqrt(n);
		//	for (int i = 2;i <= x;i++)
		//		if (n % i == 0)return 0;
		//	return  1;
		//}
		//int n;
		//int main()
		//{
		//	cin >> n;
		//	while (n != 0)
		//	{
		//		int c = 0;
		//		int m = n / 2;
		//		if (prime(n - 2))
		//			c++;
		//		for (int i = 3;i <= m;i++, i++)
		//		{
		//			if (prime(i))
		//				if (prime(n - i))
		//					c++;
		//		}
		//		cout << c << endl;
		//		cin >> n;
		//	}
		//
		//	return 0;
		//}
		//#include<iostream>
		//#include<cmath>
		//using namespace std;
		//bool prime(int n)
		//{
		//	int x = sqrt(n);
		//	for (int i = 2;i <= x;i++)
		//		if (n % i == 0)return 0;
		//	return  1;
		//}
		//
		//int main()
		//{
		//	int n;
		//	scanf("%d", &n);
		//	while (n != 0)
		//	{
		//		int c = 0;
		//		int m = n / 2;
		//		if (prime(n - 2))
		//			c++;
		//		for (int i = 3;i <= m;i++, i++)
		//		{
		//			if (prime(i))
		//				if (prime(n - i))
		//					c++;
		//		}
		//		printf("%d\n", c);
		//		scanf("%d", &n);
		//	}
		//	return 0;
		//}
		//
		//int c = 0, s = 1;
		//int x;
		//cin >> x;
		//while (s < x)
		//{
		//	c++;
		//	s = s * 10 + 1;
		//}
		//while (1)
		//{
		//	cout << s / x;
		//	s %= x;
		//	if (s == 0)
		//		break;
		//	c++;
		//	s = s * 10 + 1;
		//}
		//cout << ' ' << c;
		//int y, m, d = 0, w, i = 1;
		//cin >> y >> m;
		//if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		//d = 31;
		//if (m == 4 || m == 6 || m == 9 || m == 11)
		//d = 30;
		//if (m == 2) {
		//	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		//		d = 29;
		//	else
		//		d = 28;
		//}
		//if (m == 1 || m == 2)
		//m += 12;
		//w = (1 + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
		//cout << "     SUN     MON     TUE     WED     THU     FRI     SAT" << endl;
		//switch (w) {
		//case 0:
		//	for (i;i <= d;i++) {
		//		cout << setiosflags(ios::right) << setw(8) << i;
		//		if (i % 7 == 0)cout << endl;
		//	}break;
		//case 1:
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	for (i;i <= d;i++) {
		//		cout << setiosflags(ios::right) << setw(8) << i;
		//		if ((i + 1) % 7 == 0)cout << endl;
		//	}break;
		//case 2:
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	for (i;i <= d;i++) {
		//		cout << setiosflags(ios::right) << setw(8) << i;
		//		if ((i + 2) % 7 == 0)cout << endl;
		//	}break;
		//case 3:
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	for (i;i <= d;i++) {
		//		cout << setiosflags(ios::right) << setw(8) << i;
		//		if ((i + 3) % 7 == 0)cout << endl;
		//	}break;
		//case 4:
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	for (i;i <= d;i++) {
		//		cout << setiosflags(ios::right) << setw(8) << i;
		//		if ((i + 4) % 7 == 0)cout << endl;
		//	}break;
		//case 5:
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	for (i;i <= d;i++) {
		//		cout << setiosflags(ios::right) << setw(8) << i;
		//		if ((i + 5) % 7 == 0)cout << endl;
		//	}break;
		//default:
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	cout << setw(8) << setiosflags(ios::right) << " ";
		//	for (i;i <= d;i++) {
		//		cout << setiosflags(ios::right) << setw(8) << i;
		//		if ((i + 1) % 7 == 0)cout << endl;
		//	}break;
		//}
		//int a[401][401];
		//struct h {
		//	int x;int y;int t;
		//}s;
		//int dx[8] = { 2,2,1,1,-1,-1,-2,-2 };
		//int dy[8] = { 1,-1,2,-2,2,-2,1,-1 };
		//int n, m;
		//queue <h> q;
		//void bfs()
		//{
		//	q.push(s);
		//	a[s.x][s.y] = 0;
		//	while (!q.empty())
		//	{
		//		h k = q.front();q.pop();
		//		for (int i = 0;i < 8;i++)
		//		{
		//			int kx = k.x + dx[i], ky = k.y + dy[i];
		//			if (kx >= 0 && ky >= 0 && kx < n && ky < m)
		//			{
		//				if (a[kx][ky] == -1)
		//				{
		//					a[kx][ky] = k.t + 1;
		//					q.push({ kx,ky,k.t + 1 });
		//				}
		//			}
		//		}
		//	}
		//}
		//memset(a, -1, sizeof(a));
		//cin >> n >> m >> s.x >> s.y;s.t = 0;s.x -= 1;s.y -= 1;
		//bfs();
		//for (int i = 0;i < n;i++)
		//{
		//	for (int j = 0;j < m;j++)
		//		cout << std::left << setw(5) << a[i][j];
		//	cout << endl;
		//}
		//int fac(int n)
		//{
		//	if (n == 1)return 1;
		//	return n * fac(n - 1);
		//}
		//int a, b, c;
		//cin >> a >> b >> c;
		//cout << fac(a) + fac(b) + fac(c);
		//bool prime(int n);
		//int m;
		//cin >> m;
		//if (prime(m))
		//cout << "Yes";
		//else
		//cout << "N0";
		//int f(int a, int b)
		//{
		//	if (a % b == 0)return b;
		//	return f(b, a % b);
		//}
		//int g(int a, int b)
		//{
		//	int m = a * b;
		//	while (a % b != 0)
		//	{
		//		int r = a % b;
		//		a = b, b = r;
		//	}
		//	return m / b;
		//}
		//int a, b;
		//cin >> a >> b;
		//cout << "最大公约数：" << f(a, b) << endl << "最小公倍数：" << g(a, b);
		//int n;
		//int c[600000];
		//int d[600000];
		//int s[600000];
		//int lowbit(int i) { return i & (-i); }
		//void add(int i, int k)
		//{
		//	while (i <= n)
		//	{
		//		c[i] += k;
		//		i += lowbit(i);
		//	}
		//}
		//int getsum(int x)
		//{
		//	int r = 0;
		//	while (x > 0)
		//	{
		//		r += c[x];
		//		x -= lowbit(x);
		//	}
		//	return r;
		//}
		//int m;
		//cin >> n >> m;
		//for (int i = 1;i <= n;i++)
		//{
		//	cin >> d[i];
		//	s[i] = d[i] - d[i - 1];
		//	add(i, s[i]);
		//}
		//for (int i = 1;i <= m;i++)
		//{
		//	int x, k, y;
		//	cin >> k;
		//	if (k == 1)
		//	{
		//		cin >> x >> y >> k;
		//		add(x, k), add(y + 1, -k);
		//	}
		//	else
		//	{
		//		cin >> x;
		//		cout << getsum(x) << endl;
		//	}
		//}
		//int  n;
		//int  c[1000005];
		//int lowbit(int x)
		//{
		//	return x & (-x);
		//}
		//void updata(int i, int k)//i的位置加k
		//{
		//	while (i <= n)
		//	{
		//		c[i] += k;
		//		i += lowbit(i);
		//	}
		//}
		//int getsum(int i)//求1到i的和
		//{
		//	int res = 0;
		//	while (i > 0)
		//	{
		//		res += c[i];
		//		i -= lowbit(i);
		//	}
		//	return res;
		//}
		//int getsum(int x, int y)//求x到y的和
		//{
		//	return getsum(y) - getsum(x - 1);
		//}
		//int m;
		//cin >> n >> m;
		//for (int i = 1;i <= n;i++)
		//{
		//	int p;//n个p组成原数组
		//	cin >> p;
		//	updata(i, p);//更新为树状数组
		//}
		//for (int i = 0;i < m;i++)
		//{
		//	int k, x, y;
		//	cin >> k >> x >> y;
		//	if (k == 1)
		//		updata(x, y);
		//	else
		//		cout << getsum(x, y) << endl;
		//
		//}
		//priority_queue<int, vector<int>, greater<int> >q;
		//priority_queue<int, vector<int>, less<int> >p;
		//int read()
		//{
		//	char c = getchar();int x = 0, f = 1;
		//	while (c < '0' || c>'9')if (c == '-')f = -1, c = getchar();
		//	while (c >= '0' && c <= '9')x = x * 10 + c - '0', c = getchar();
		//	return x * f;
		//}
		//int Max[MAXN][21];
		//int Query(int l, int r)
		//{
		//	int k = log2(r - l + 1);
		//	return max(Max[l][k], Max[r - (1 << k) + 1][k]);
		//}
		//int mian()
		//{
		//	int N = read(), M = read();
		//	for (int i = 1;i <= N;i++)
		//		Max[i][0] = read();
		//	for (int j = 1;j < 21;j++)
		//		for (int i = 1;i + (1 << j) - 1 <= N;i++)
		//			Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
		//	for (int i = 1;i <= M;i++)
		//	{
		//		int l = read(), r = read();
		//		cout << Query(l, r);
		//	}
		//	return 0;
		//}
		//bool cmp1(char s1, char s2)
		//{
		//	return s1 < s2;
		//}
		//bool cmp2(char s1, char s2)
		//{
		//	return s1 > s2;
		//}
		//string s1 = "495";
		//string s2, s3;
		//cin >> s2;
		//s3 = s2;
		//sort(s2.begin(), s2.end());
		//sort(s3.begin(), s3.end());
		//cout << stoi(s2) << endl;
		//cout << stoi(s3);
		//string s1 = "495";
		//string s2, s3;
		//cin >> s2;
		//s3 = s2;
		//sort(s2.begin(), s2.end(), cmp1);
		//sort(s3.begin(), s3.end(), cmp2);
		//
		//void Add(int a[], int b[]) {
		//	if (a[0] < b[0]) a[0] = b[0];
		//	for (int i = 1;i <= a[0];i++) {
		//		a[i] += b[i];
		//		a[i + 1] += a[i] / 10;
		//		a[i] %= 10;
		//		//if (a[i] > 9) a[i + 1]++, a[i] -= 10;
		//	}
		//	if (a[a[0] + 1] > 0) a[0]++;
		//	return;
		//}
		//int a[1000], b[1000];
		//int main()
		//{
		//	a[0] = a[1] = 1, b[0] = b[1] = 1;
		//	int n;cin >> n;
		//	for (int i = 2;i <= n;i++)
		//	{
		//		if (i % 2 == 1)
		//			Add(a, b);
		//		else
		//			Add(b, a);
		//	}
		//	if (n % 2)
		//	{
		//		int m = a[0];
		//		for (int i = m;i > 0;i--)
		//			cout << a[i];
		//	}
		//	else
		//	{
		//		int m = b[0];
		//		for (int i = m;i > 0;i--)
		//			cout << b[i];
		//	}
		//	int a, b, c, d;
		//	cin >> a >> b >> c >> d;
		//	srand(b);
		//	for (int i = 0;i < a;i++)
		//		b = rand() % (d - c + 1) + c;
		//	cout << b;


		/*
		long long int a, b, n,c=0;
			cin >> a >> b >> n;
			a = a % b;
			for (int i = 0;i < n;i++)
			{
				a *= 10;
				c= a / b;
				a = a % b;
			}
			cout << c;

		int n;
			cin >> n;
			while (n != 0)
			{
				int c = 0;
				int m = n / 2;
				if (prime(n - 2))
					c++;
				for (int i = 3;i <= m;i++,i++)
				{
					if (prime(i))
						if (prime(n-i))
							c++;
				}
				cout << c << endl;
				cin >> n;
			}*/
			//bool prime(int n)
			//{
			//	int x = sqrt(n);
			//	for (int i = 2;i <=x;i++)
			//		if (n % i == 0)return 0;
			//	return  1;
			//}
			/*int n, x = 1,c=0;
				cin >> n;
				int a[n][n];
				for (int i = 0;i < n;i++)
					for (int j = 0;j < n;j++)
						cin >> a[i][j];
				for (int i = 0;i < n;i++)
				{
					x = 1;
					int m = a[i][0];int  y;
					for (int j = 0;j < n;j++)
					{
						if (a[i][j] >= m)
						{
							m = a[i][j];
							 y = j;
						}
					}
					for (int k = 0;k < n;k++)
					{
						if (a[k][y] < m)
							x = 0;
					}
					if (x)
					{
						c++;
						cout << i << ' ' << y;break;
					}
				}
				if (!c)
					cout << "NONE";*/
					//long x[1001], y[1001], z[1001];
					//long fa[1003];
					//long n, h, r,T;
					//long d(long x1, long y1, long z1, long x2, long y2, long z2)
					//{
					//	return sqrt( pow(x1-x2,2)+ pow(y1 - y2, 2)+ pow(z1 - z2, 2));
					//}
					//long find(long s)
					//{
					//	while (s != fa[s])
					//	{
					//		fa[s] = fa[fa[s]];
					//		s = fa[s];
					//	}
					//	return s;
					//}
					//
					//
					//int main()
					//{
					//	cin >> T;
					//	while (T--)
					//	{
					//		fa[1001] = -1, fa[1002] = -2;
					//		cin >> n >> h >> r;
					//		for (int i = 0;i < n;i++)
					//		{
					//			cin >> x[i] >> y[i] >> z[i];
					//			fa[i] = i;
					//		}
					//		for (int i = 0;i < n;i++)
					//		{
					//			if (z[i] - r <= 0)
					//			{
					//				if (find(i) != find(1001))
					//					fa[find(i)] = find(1001);
					//			}
					//			if (z[i] + r >= h)
					//				if (find(i) != find(1002))
					//					fa[find(i)] = find(1002);
					//			for (int j = 0;j < i;j++)
					//			{
					//				if (d(x[i], y[i], z[i], x[j], y[j], z[j]) <= 2 * r)
					//					if (find(i) != find(j))
					//						fa[find(i)] = find(j);
					//			}
					//		}
					//		if (find(1001) == find(1002))
					//			cout << "Yes" << endl;
					//		else
					//			cout << "No" << endl;
					//	}
					//long find(long x)
					//{
					//	return fa[x] == x ? x : (find(fa[x]));
					//}
					//void merge(long a, long b)
					//{
					//	long da = find(a);
					//	long db = find(b);
					//	fa[da] = db;
					//}
					//int main()
					//{
					//	cin >> T;
					//	while (T--)
					//	{
					//		fa[1002] = -1;
					//		cin >> n >> h >> r;
					//		for (long i = 0;i < n;i++)
					//		{
					//			cin >> x[i] >> y[i] >> z[i];
					//			fa[i] = i;
					//		}
					//		for (long i = 0;i < n;i++)
					//		{
					//			if (z[i] - r <= 0)
					//			{
					//				merge(i, 1001);
					//			}
					//			if (z[i] + r >= h)
					//				merge(i, 1002);
					//			for (int j = 0;j < i;j++)
					//			{
					//				if (d(x[i], y[i], z[i], x[j], y[j], z[j]) <= 2 * r)
					//					merge(j, i);
					//			}
					//			if (fa[1001] == fa[1002])
					//				break;
					//		}
					//		if (fa[1001] == fa[1002])
					//			cout << "Yes" << endl;
					//		else
					//			cout << "No" << endl;
					//	}
					//#define  MAXN 100010
					//int read()
					//{
					//	char c = getchar();int x = 0, f = 1;
					//	while (c < '0' || c>'9') { if (c == '-')f = -1;c = getchar(); }
					//	while (c >= '0' && c <= '9') { x = x * 10 + c - '0';c = getchar(); }
					//	return x * f;
					//}
					//int Max[MAXN][21];
					//int Query(int l, int r)
					//{
					//	int k = log2(r - l + 1);
					//	return max(Max[l][k], Max[r - (1 << k )+ 1][k]);
					//}
					//int main()
					//{
					//#ifdef WIN32
					//	feropen("a.in", "r", stdin);
					//#endif
					//	int N = read(), M = read();
					//	for (int i = 1;i <= N;i++) Max[i][0] = read();
					//	for (int j = 1;j <= 21;j++)
					//		for (int i = 1;i + (1 << j) - 1 <= N;i++)
					//			Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
					//	for (int i = 1;i <= M;i++)
					//	{
					//		int l = read(), r = read();
					//		printf("%d\n", Query(l, r));
					//	}
					//#ifdef WIN32
					//	feropen("a.in", "r", stdin);
					//#endif
					/*int n,m;
						long long s = 0;
						cin >> n;
						for (int i = 0;i < n;i++)
						{
							cin >> m;
							q.push(m);
						}
						while(q.size()>1)
						{
							m = 0;
							m += q.top();q.pop();
							m += q.top();q.pop();
							s += m;
							q.push(m);
						}
						cout << s;*/
						/*int n, m=-1,c;
							cin >> n;
							cin >> c;
							cout << c << endl;
							m = c;
							p.push(m);
							for (int i = 2;i <= n;i++)
							{
								cin >> c;
								if (c >= m)
								{
									q.push(c);
								}
								else
									p.push(c);
								if (i % 2 == 1)
								{

								}


							}*/
							/*for (int i = 1;i <= n;i++)
								{
									cin >> c;
									if (c >= m)
										q.push(c);
									else
										p.push(c);
									if (q.size() > p.size() + 1)
									{
										m = q.top();
										p.push(m);q.pop();
									}
									if (p.size() > q.size() + 1)
									{
										m = p.top();
										q.push(m);p.pop();
									}
									if (i % 2 == 1)
									{
										if (p.size() > q.size())
										{
											m = p.top();
											cout << m << endl;
										}
										else
										{
											m = q.top();
											cout << m << endl;
										}
									}
								}*/
								/*int n, m = -1, c;
									cin >> n;
									for (int i = 0;i < n;i++)
									{
										cin >> c;
										if (c >= m)
										{
											q.push(c);m = q.top();
										}
										else
										{
											p.push(c);m = p.top();
										}
										if (q.size() > p.size() + 1)
										{
											p.push(m);m = q.top();q.pop();
										}
										else if (q.size() < p.size() + 1)
										{
											q.push(m);m = p.top();p.pop();
										}
										if ((i+1) % 2==1&&i<n-1)
										{
											cout << m << endl;
										}

									}
									if ((n - 1) / 2 % 2 == 0)
										cout << m;*/
										/*
											int n, a, b;
											cin >> n;
											while (n--)
											{
												cin >> a;
												switch (a) {
												case 1:cin >> b;q.push(b);break;
												case 2:cout << q.top() << endl;break;
												case 3:q.pop();break;
												}
											}*/
											//int T;
												//cin >> T;
												//while (T--)
												//{
												//	long long int n, h, r;
												//	cin >> n >> h >> r;
												//	/*Dot* dot = new Dot[n];*/
												//	for (int i = 0;i < n;i++)
												//	{
												//		cin >> dot[i].x >> dot[i].y >> dot[i].z;
												//		dot[i].num = i;fa[i] = i;
												//	}
												//	int c = 0;
												//	for (int i = 0;i < n;i++)
												//	{
												//		if (dot[i].z <= r)
												//		{
												//			for (int k = 0;k < n;k++)
												//			{
												//				if (d(dot[fa[i]].x, dot[k].x, dot[fa[i]].y, dot[k].y, dot[fa[i]].z, dot[k].z) <= 2 * r)
												//				{
												//					merge(dot[fa[i]].num, dot[k].num);
												//				}
												//			}
												//			if (dot[find(fa[dot[i].num])].z + r >= h)
												//			{
												//				c = 1;
												//				cout << "Yes" << endl;break;
												//			}
												//		}
												//	}
												//	if (!c)
												//		cout << "No" << endl;
												//}
											//long long int fa[1001];/*
											//long long int x[1001], y[1001], z[1001];*/
											//long long int d(long long int x1, long long int  x2, long long int y1, long long  int y2, long long int  z1, long long int  z2)
											//{
											//	return sqrt( (x1-x2)* (x1 - x2)+ (y1 - y2) * (y1 - y2)+ (z1 - z2) * (z1 - z2));
											//}
											//struct Dot {
											//	long long int x, y, z, num;
											//}dot[1001];
											//long long int find(long long int x)
											//{
											//	return x == fa[x] ? x : (fa[x]=find(fa[x]));
											//}
											//void merge(long long int a, long long  int b)
											//{
											//	int da = find(a);int db = find(b);
											//	if (dot[da].z <= dot[db].z) {
											//		fa[da] = db;
											//	}
											//	else fa[db] = da;
											//}
											/*cin >> n >> m;
												for (int i = 1;i <= n;i++)
													fa[i] = i;
												for (int i = 1;i <= m;i++)
													cin >> a[i].x >> a[i].y >> a[i].t;
												sort(a + 1, a + m + 1, cmp);
												for (int i = 1;i <= m;i++)
												{
													merge(a[i].x, a[i].y);
													if (check())
													{
														cout << a[i].t;return 0;
													}
												}
												if (!check())
													cout << -1;*/
													//int fa[100010], n, m;
													//struct node
													//{
													//	int x, y, t;
													//}a[100010];
													//bool cmp(node a, node b)
													//{
													//	return a.t < b.t;
													//}
													//int find(int x)
													//{
													//	return fa[x] == x ? x : (find(fa[x]));
													//}
													//void merge(int x, int y)
													//{
													//	int dx = find(x);
													//	int dy = find(y);
													//	fa[dx] = dy;
													//}
													//bool check()
													//{
													//	int s = 0;
													//	for (int i = 1;i <= m;i++)
													//	{
													//		if (fa[i] == i) s++;
													//		if (s > 1)return 0;
													//	}
													//	return 1;
													//}
													/*cin >> n >> m;
														for (int i = 1;i <= n;i++)
															fa[i] = i;
														for (int i = 1;i <= m;i++)
															cin >> a[i].x >> a[i].y >> a[i].t;
														sort(a + 1, a + m + 1, cmp);
														for (int i = 1;i <= m;i++)
														{
															hb(a[i].x, a[i].y);
															if (check())
															{
																cout << a[i].t;return 0;
															}
														}
														cout << -1;*/
														//int fa[1010], n, m;
														//struct node
														//{
														//	int x, y, t;
														//}a[100010];
														//bool cmp(node fir, node sec)
														//{
														//	return fir.t < sec.t;
														//}
														//int gf(int x)
														//{
														//	if (fa[x] == x)return x;
														//	return fa[x] = gf(fa[x]);
														//}
														//void hb(int x, int y)
														//{
														//	int fx = gf(x);
														//	int fy = gf(y);
														//	fa[fx] = fy;
														//}
														//bool check()
														//{
														//	int s = 0;
														//	for (int i = 1;i <= n;i++)
														//	{
														//		if (fa[i] == i)s++;
														//		if (s == 2)return 0;
														//	}
														//	return 1;
														//}
														/*char ch;
															while (cin >> ch, ch != '@')
															{
																switch (ch)
																{
																case'(':n.push(ch);break;
																case')':
																{
																	if (n.size() == 0)
																	{
																		cout << "NO";return 0;
																	}
																	n.pop();
																	break;
																}
																default:break;
																}
															}
															if (n.size())
																cout << "NO";
															else
																cout << "YES";*/

																/*int n, m;
																	n=m =0;
																	char ch;
																	while (cin >> ch, ch != '@')
																	{
																		switch (ch)
																		{
																		case '(':n++;break;
																		case')':m++;break;
																		default:break;
																		}


																	}
																	if (n != m)
																		cout << "NO";
																	else
																		cout << "YES";*/
																		/*int s=0;char ch;
																			int a, b;
																			while (cin >> ch,ch != '@')
																			{
																				switch (ch)
																				{
																				case '+': b = n.top();n.pop(); a = n.top();n.pop();n.push(a+b);break;
																				case '-': b = n.top();n.pop(); a = n.top();n.pop();n.push(a - b);break;
																				case '*': b = n.top();n.pop(); a = n.top();n.pop();n.push(a * b);break;
																				case '/': b = n.top();n.pop(); a = n.top();n.pop();n.push(a / b);break;
																				case '.':n.push(s);s = 0;break;
																				default:s = s * 10 + ch - '0';break;

																				}

																			}
																			cout << n.top();*/
																			/*int n, m, p, k, i, nu;
																				cin >> n;
																				Ndlk** arr = (Ndlk**)calloc(n + 1, sizeof(Ndlk*));
																				Ndlk* tmp;
																				int first = 1;
																				for (int i = 1;i <= n;i++)
																				{
																					arr[i] = (Ndlk*)calloc(1, sizeof(Ndlk));
																					arr[i]->num = i;
																					arr[i]->last = NULL;arr[i]->next = NULL;
																				}
																				for (int i = 2;i <= n;i++)
																				{
																					cin >> k >> p;
																					if (k == first && p == 0)
																					{
																						first = i;
																					}
																					if (!p)
																					{
																						arr[i]->next
																					}
																				}*/
																				//struct Ndlk
																				//{
																				//	Ndlk* last;
																				//	int num;
																				//	Ndlk* next;
																				//};
																				//int a[100001][3];
																					// int n;
																					//cin >> n;
																					//int k, p,head=1;
																					//a[1][0] = 1;
																					//for (int i = 2;i <= n;i++)
																					//{
																					//	cin >> k >> p;
																					//	if (p)//right
																					//	{
																					//		a[i][2] = a[k][2];a[i][1] = k;
																					//		a[a[k][2]][1] = i;a[k][2] = i;
																					//		a[i][0] = 1;
																					//	}
																					//	else//left
																					//	{
																					//		if (a[k][1] == 0)
																					//		{
																					//			head = i;
																					//			a[k][1] = i;a[i][2] = k;
																					//			a[i][0] = 1;
																					//		}
																					//		else
																					//		{
																					//			a[i][1] = a[k][1];a[i][2] = k;
																					//			a[a[k][1]][2] = i;
																					//			a[k][1] = i;a[i][0] = 1;
																					//		}
																					//	}
																					//}
																					//int m;
																					//cin >> m;
																					//for (int i = 0,M=m;i < M;i++)
																					//{
																					//	cin >> m;
																					//	if (a[m][0] == -1)
																					//		continue;
																					//	if (a[m][0])
																					//	{
																					//		a[m][0] = -1;
																					//	}
																					//}
																					//while (a[head][0] != 0)
																					//{
																					//	if (a[head][0] != -1)
																					//	{
																					//		cout << head << ' ';
																					//	}
																					//	
																					//		head = a[head][2];
																					//	
																					//}
																				/*queue<int>q;
																					int n, m;
																					cin >> n >> m;
																					if (n == 0)
																						return 0;
																					for (int i = 1;i <= n;i++)
																						q.push(i);
																					int a;
																					while (q.size() > 1)
																					{
																						for (int i = 1;i <= m - 1;i++)
																						{
																							a = q.front();
																							q.pop();
																							q.push(a);
																						}
																						cout << q.front() << ' ';
																						q.pop();
																					}
																					cout << q.front() << ' ';

																				*/

																				//int n, m;
																				//struct Stree
																				//{
																				//	int l, r;
																				//	int dat;
																				//}t[N];
																				//void build(int p, int l, int r)
																				//{
																				//	t[p].l = l;t[p].r = r;
																				//	if (l == r)
																				//	{
																				//		t[p].dat = 1;
																				//		return;
																				//	}
																				//	int mid = (l + r) >> 1;
																				//	build(p << 1, l, mid);
																				//	build(p<<1|1)
																				//
																				//
																				//}

																				/*int n, m;
																					cin >> n >> m;
																					bool* b = new bool[n];
																					for (int i = 0;i < n;i++)
																						b[i] = 0;
																					int c = 0;
																					for (int i = 0;i < n;i++)
																					{
																						for (int j = 0;j < m;j++)
																						{
																							if (c >= n)
																								c = 0;
																							if (b[c])
																								j--;
																							c++;
																						}
																						b[c-1] = 1;
																						cout << c  << ' ';
																					}
																					*/
																					//int c = 0;
																						//for (int i = 2;i < 20000;i++)
																						//{
																						//	for (int j = 2;j < i;j++)
																						//	{
																						//		if (i % j == 0)
																						//		{
																						//			for (int k = i;k < 20000;k += k)
																						//				p[k] = 1;
																						//		}
																						//	}
																						//	if (p[i] == 0)
																						//		prime[c++] = i;///*for (int i = 0;i < c;i++)//}
																						//int n;//	cout << prime[i] << ' ';*/
																						//scanf("%d", &n);
																						//while (n != 0)
																						//{
																						//	int t = 0;
																						//	for (int i = 0;i < c;i++)
																						//	{
																						//		if (prime[i] > n)
																						//			break;
																						//		for (int j = i;j < c;j++)
																						//		{
																						//			if (n == prime[i] + prime[j])
																						//			{
																						//				t++;break;
																						//			}
																						//		}
																						//	}
																						//	cout << t << endl;
																						//	scanf("%d", &n);
																						//}int prime[30000];
																					//bool p[30001];
																					/*int m, n,t=0;
																						cin >> m >> n;
																						int p[100];
																						for (int i = m;i <= n;i++)
																						{
																							int s = 0,c=0;
																							for (int j = 1;j < i;j++)
																							{
																								if (i % j == 0)
																								{
																									p[c++] = j;
																									s += j;
																								}
																							}
																							c--;
																							if (s == i)
																							{
																								t = 1;
																								cout << s << ' ' << '=' << ' ';
																								for (int i = 0;i < c;i++)
																								{
																									cout << p[i] << ' ' << '+'<<' ';
																								}
																								cout  << p[c] << endl;
																							}
																						}
																						if (t == 0)
																						{
																							cout << "None";
																						}
																					*/
																					/*int n;
																						cin >> n;
																						int c = 1, a = 0, b = n-1;
																						int p[n][n];
																						for (int i = 0;i < n;i++)
																							for (int j = 0;j < n;j++)
																								p[i][j] = 0;
																						while (a <= b)
																						{
																							for (int i = a;i <= b;i++) p[a][i] = c++;
																							for (int i = a+1;i <= b;i++) p[i][b] = c++;
																							for (int i = b-1;i >= a;i--) p[b][i] = c++;
																							for (int i = b-1;i > a;i--) p[i][a] = c++;
																							a++, b--;
																						}
																						for (int i = 0;i < n;i++)
																						{
																							for (int j = 0;j < n;j++)
																								cout <<setw(3)<< p[i][j];
																							cout << endl;
																						}*/
																						//struct s {
																						//	int m;
																						//	s* r;
																						//};
																						//int main()
																						//{
																						//	s* head = NULL;
																						//	s* p, * c;
																						//	head->m = 1;
																						//	c = p = head;
																						//	int n;cin >> n;int k, d;
																						//	for (int i = 2;i <= n;i++)
																						//	{
																						//		cin >> k >> d;
																						//		if (d)
																						//		{
																						//			while (c->m != k)
																						//			{
																						//				p = c;
																						//				c = c->r;
																						//			}
																						//			c = new s;
																						//			p->r = c;c->m = k;
																						//			p = head;
																						//		}
																						//		else
																						//		{
																						//			while (c->m != k)
																						//			{
																						//				p = c;
																						//				c = c->r;
																						//			}
																						//			c = new s;
																						//			c->m = k;c->r = p->r;
																						//
																						//
																						//		}
																						//
																						//
																						//	}
																						//#define TSIZE 45
																						//struct film {
																						//	char title[TSIZE];
																						//	int rating;
																						//	film* next;
																						//};
																						//int main()
																						//{
																						//	film* head = NULL;
																						//	film* prev, * current;
																						//	char input[TSIZE];
																						//	int* p = NULL;
																						//	while (p != NULL && input[0] != '\0')
																						//	{
																						//		current = new film;
																						//		if (head == NULL)
																						//			head = current;
																						//		else
																						//			prev->next = current;
																						//		current->next = NULL;
																						//
																						//	}
																						//struct s
																						//{
																						//	int m;
																						//	s* l;
																						//	s* r;
																						//};
																						//int main()
																						//{
																						//	int n;
																						//	cin >> n;
																						//	s a;
																						//	s* head;
																						//	head->r = a;
																						//	a.m = 1, a.l = NULL;
																						//	int  k,p;
																						//	for (int i = 2;i <= n;i++)
																						//	{
																						//		cin >> k >> p;
																						//		if (p)
																						//		{
																						//			s* c = new s;
																						//			c->m = i;
																						//			a.r = c;
																						//		}
																						//
																						//
																						//	}
																						//
																						//
																						/*cin >> p;
																							while (p--)
																							{
																								cin >> n;
																								int a[n + 1], b[n + 1], sum = 1;
																								for (int i = 1;i <= n;i++)
																									cin >> a[i];
																								for (int i = 1;i <= n;i++)
																									cin >> b[i];
																								for (int i = 1;i <= n;i++)
																								{
																									q.push(a[i]);
																									while ((q.top()) == b[sum])
																									{
																										q.pop(), sum++;
																										if (q.empty())break;
																									}
																								}
																								if (q.empty()) cout << "Yes" << endl;
																								else cout << "No" << endl;
																								while(!q.empty())q.pop();
																							}*/
																							//#define MAX 100005
																							//struct node
																							//{
																							//	vector<int> num, w;
																							//	int s;
																							//}desk[MAX];
																							/*int n, q;
																								cin >> n >> q;
																								while (q--)
																								{
																									int x, a, b, c;
																									cin >> x;
																									if (x == 1)
																									{
																										cin >> a >> b >> c;
																										desk[a].s++;
																										desk[a].num.push_back(b);
																										desk[a].w.push_back(c);
																									}
																									else
																									{
																										cin >> a >> b;
																										for (int i = desk[a].s - 1;i >= 0;i--)
																										{
																											if (desk[a].num[i] == b)
																											{
																												cout << desk[a].w[i] << endl;
																												break;
																											}
																										}
																									}
																								}*/
																								//int m, n;
																								//struct Node
																								//{
																								//	int data;
																								//	Node* next;
																								//}*head, * p, * tail, * temp;
																								/*cin >> m >> n;
																									head = new Node;
																									head->next = NULL;
																									tail = head;
																									for (int i = 1;i <= m;i++)
																									{
																										p = new Node;
																										p->data = i;
																										p->next = NULL;
																										tail->next = p;
																										tail = p;
																									}
																									p = head->next;
																									tail->next = head->next;
																									for (int i = 1;i <= m;i++)
																									{
																										for (int j = 1;j < n - 1;i++)
																										{
																											p = p->next;
																										}
																										cout << p->next->data;
																										temp = p->next;
																										p->next = temp->next;
																										p = p->next;
																										free(temp);
																									}*/
																									//int a[32][32] = { 0 }, b[32][32] = { 0 };
																									//int dx[4] = { 1,0,-1,0 };
																									//int dy[4] = { 0,-1,0,1 };
																									//void f(int x, int y)
																									//{
																									//	if (x < 0 || y < 0 || x>32 || y>32)
																									//		return;
																									//	if (b[x][y] == true || a[x][y] == 1)
																									//		return;
																									//	if (a[x][y] == 0)
																									//	{
																									//		b[x][y] = true;
																									//		for (int i = 0;i < 4;i++)
																									//			f(x + dx[i], y + dy[i]);
																									//	}
																									//	return;
																									//}
																									//
																									//int main()
																									//{
																									//	int n;
																									//	cin >> n;
																									//	for (int i = 1;i <= n;i++)
																									//	{
																									//		for (int j = 1;j <= n;j++)
																									//		{
																									//			cin >> a[i][j];
																									//		}
																									//	}
																									//	/*for (int i = 1;i <= n;i++)
																									//	{
																									//		for (int j = 1;j <= n;j++)
																									//			cout << a[i][j] << ' ';
																									//		cout << endl;
																									//	}*/
																									//	f(31, 31);
																									//	for (int i=1;i<=n;i++)
																									//	{
																									//		for (int j = 1;j <= n;j++)
																									//		{
																									//			if (a[i][j] == 0 && b[i][j] == 0)
																									//				cout << 2 << ' ';
																									//			else
																									//				cout << a[i][j] << ' ';
																									//		}
																									//		cout << endl;
																									//	}
																									//int a[40][40] = { 0 }, n;
																									//bool b[40][40] = { 0 };
																									//int dx[4] = { 1,0,-1,0 };
																									//int dy[4] = { 0,-1,0,1 };
																									//void f(int x,int y,int n)
																									//{
																									//	if (x > 32 || y > 32 || x < 0 || y < 0)
																									//		return;
																									//	if (n == 1)
																									//		return;
																									//	if (n == 0)
																									//		b[x][y] = 1;
																									//	for (int i = 0;i < 4;i++)
																									//		if (x - 1 < 0 || y - 1 < 0)
																									//			return;
																									//		else
																									//			f(x + dx[i], y + dy[i], a[x + dx[i]][y + dy[i]]);
																									//	return;
																									//}
																									//int main()
																									//{
																									//	cin >> n;
																									//	for (int i = 0;i < n;i++)
																									//		for (int j = 0;j < n;j++)
																									//			cin >> a[i][j];
																									//	f(31, 31, 0);
																									//	for (int i = 0;i < n;i++)
																									//		for (int j = 0;j < n;j++)
																									//			if (!a[i][j] && !b[i][j])
																									//				a[i][j] = 2;
																									//	for (int i = 0;i < n;i++)
																									//	{
																									//		for (int j = 0;j < n;j++)
																									//			cout << a[i][j];
																									//		cout << endl;
																									//	}
																									//cin >> n;
																									//dfs(0);
																									//int n, a[200];
																									//bool p[200];
																									//void print()
																									//{
																									//	for (int i = 0;i < n;i++)
																									//		cout << setw(5) << a[i];
																									//	cout << endl;
																									//}
																									//void dfs(int k)
																									//{
																									//	if (k == n)
																									//	{
																									//		print();
																									//		return;
																									//	}
																									//	for(int i=1;i<=n;i++)
																									//		if (!p[i])
																									//		{
																									//			a[k] = i;
																									//			p[i] = 1;
																									//			dfs(k + 1);
																									//			p[i] = 0;
																									//		}
																									//}
																									/*int n;
																										cin >> n;
																										char* a = new char[n];
																										for (int i = 0;i < n;i++)
																										{
																											 a[i]=i+1+48;
																										}
																										for (int i = 0;i < n;i++)
																										{
																											cout << setw(5) << a[i];
																										}
																										cout << endl;
																										while (next_permutation(a, a + n))
																										{
																											for (int i = 0;i < n;i++)
																											{
																												cout << setw(5) << a[i];
																											}
																											cout << endl;
																										}*/
																										//void inline swap(char* s1, char* s2)
																										//{
																										//	char t = *s1;
																										//	*s1 = *s2;
																										//	*s2 = t;
																										//}
																										//void reverse(char* s, char* e)// s, e分别开始和结尾，不能反转中文
																										//{
																										//	for (e--;s < e;s++, e--)
																										//		swap(s, e);
																										//}
																										//bool next_permutation(char* start, char* end)//排列下一次
																										//{
																										//	char* cur = end - 1, * pre = cur - 1;
																										//	while (cur > start && *pre >= *cur)cur--, pre--;
																										//	if (cur <= start)return false;
																										//	for (cur = end - 1;*cur <= *pre;cur--)
																										//		;
																										//	//找到逆序中大于*pre的元素的最小元素
																										//	swap(cur, pre);
																										//	reverse(pre + 1, end);//将尾部的逆序变成正序
																										//	return true;
																										//}
																										/*cin >> n;
																											for (int i = 1;i <= n;i++)
																											{
																												cin >> tr[i];
																											}
																											cin >> ch;
																											for (int i = 1;i <= n;i++)
																												for (int j = 1;j <= n;j++)
																													yc[i][j] = mt(i, j);
																											for (int i = 1;i <= n;i++)
																											{
																												if (tr[i][0] == ch)
																												{
																													vis[i]++;
																													an = tr[i].size();
																													dfs(i);
																													vis[i] = 0;
																												}
																											}
																											cout << ans;*/
																											//int n;
																											//string tr[30];
																											//int  yc[30][30];
																											//int vis[30];
																											//int mt(int x, int y) {
																											//	bool pp = true;
																											//	int ky = 0;
																											//	for (int k = tr[x].size() - 1;k >= 0;k--)
																											//	{
																											//		for (int kx = k;kx < tr[x].size();kx++)
																											//		{
																											//			if (tr[x][kx] != tr[y][ky++])
																											//			{
																											//				pp = false;
																											//				break;
																											//			}
																											//		}
																											//		if (pp == true)
																											//		{
																											//			return tr[x].size() - k;
																											//		}
																											//			ky = 0;
																											//			pp = true;
																											//	}
																											//	return 0;
																											//
																											//}
																											//char ch;
																											//int ans = -1;
																											//int an = 0;
																											//void dfs(int p)
																											//{
																											//	bool jx = false;
																											//	for (int j = 1;j <= n;j++)
																											//	{
																											//		if (vis[j] >= 2)continue;
																											//		if (yc[p][j] == 0)continue;
																											//		if (yc[p][j] == tr[p].size() || yc[p][j] == tr[j].size())continue;
																											//		an += tr[j].size() - yc[p][j];
																											//		vis[j]++;
																											//		jx = true;
																											//		dfs(j);
																											//		an -= tr[j].size() - yc[p][j];
																											//		vis[j]--;
																											//	}
																											//	if (jx == false)
																											//	{
																											//		ans = max(ans, an);
																											//	}
																											//	return;
																											//}
																											//
																											/*bool prime(long long int n)
																											{
																												for (int i = 2;i * i <= n;i++)
																													if (n % i == 0)return 0;
																												return n != 1;
																											}
																												int n;
																												cin >> n;
																												long long int k;
																												for (int i = 0;i < n;i++)
																												{
																													cin >> k;
																													if (prime(k))
																														cout << "Yes" << endl;
																													else
																														cout << "No" << endl;
																												}*/

																												//int n;
																													//cin >> n;
																													//sd* a = new sd[n];
																													//for (int i = 0;i < n;i++)
																													//{
																													//	cin >> a[i].n >>a[i].a>> a[i].b >> a[i].c;
																													//	a[i].s = (a[i].a + a[i].b + a[i].c)/3;
																													//	double t = a[i].s *100;
																													//	a[i].s = round(t) /100;
																													//}
																													//sort(a, a + n, cmp);
																													////cout << setiosflags(ios::fixed) << setprecision(2);
																													//for (int i = 0;i < n;i++)
																													//	cout << a[i].n <<' ' << a[i].s << endl;
																												//struct sd
																												//{
																												//	string n;
																												//	double a, b, c;
																												//	double s=0.0;
																												//};
																												//bool cmp(sd a, sd b)
																												//{
																												//	if (a.s != b.s)
																												//		return a.s > b.s;
																												//	else
																												//		return a.n < b.n;
																												//}
																												/*double x;
																													cin >> x;
																													double k = 0,s=0;
																													double m = pow(x, k) / f(k);
																													s += m;
																													do
																													{
																														k++;
																														m = pow(x, k) / f(k);
																														s += m;

																													} while (m >= 0.00001);

																													cout << setiosflags(ios::fixed) << setprecision(4) << s;*/
																													/*int n;
																														cin >> n;
																														int a[n][n], p[n],pp[n],c=0,w=0;
																														for (int i = 0;i < n;i++)
																														{
																															for (int j = 0;j < n;j++)
																															{
																																cin >> a[i][j];
																															}
																														}

																														for (int i = 0;i < n;i++)
																														{
																															int t = 0;
																															for (int j = 0;j < n;j++)
																															{
																																if (a[i][j] >= t)
																																{
																																	pp[c] = i;
																																	p[c++] = j;
																																	t = a[i][j];
																																}
																															}
																															int k;
																															for ( k = 0;k < c;k++)
																															{
																																for (int l = 0;l < n;l++)
																																{
																																	if (a[l][p[k]] < t)
																																		break;
																																	w = 1;
																																}
																															}
																															if (w)
																																cout << i << ' ' << p[k];
																														}
																														if (w == 0)
																															cout << "NONE";*/
#include<iostream>
																															//#include<cmath>
																															//#include<iomanip>
																															//#include<stdlib.h>
																															//#include<algorithm>
																															//#include <cstring>
																															//#include<vector>
																															//using namespace std;
																															////bool prime(long long  n)
																															////{
																															////	for (int i = 2;i * i <= n;i++)
																															////		if (n % i == 0)return 0;
																															////	return n != 1;
																															////}
																															///*int n;
																															//cin >> n;
																															//long long k;
																															//for (int i = 0;i < n;i++)
																															//{
																															//	cin >> k;
																															//	if (prime(k))
																															//		cout << "Yes" << endl;
																															//	else
																															//		cout << "No" << endl;
																															//}*/
																															//int main()
																															//{
																															//	int n;
																															//	cin >> n;
																															//	int a[n][n];int s[n],m=1;
																															//	for (int i = 0;i < n;i++)
																															//		for (int j = 0;j < n;j++)
																															//			cin >>a[i][j];
																															//	int t = 0,x=0,y,c=0;
																															//	for (int i = 0;i < n;i++)
																															//	{
																															//		m = 1;
																															//		t = a[i][0];
																															//		for (int j = 0;j < n;j++)
																															//		{
																															//			if (a[i][j] > t)
																															//			{
																															//				t = a[i][j];
																															//				s[0] = j;
																															//				x = i;
																															//			}
																															//			else if (a[i][j] == t)
																															//			{
																															//				s[m++] = j;
																															//			}
																															//		}
																															//		for (int p = 0;p < m;p++)
																															//		{
																															//			c = 1;
																															//			for (int k = 0;k < n;k++)
																															//			{
																															//				if (a[k][s[p]] < t)
																															//				{
																															//					c = 0;break;
																															//				}
																															//			}
																															//			if (c)
																															//			{
																															//				cout << x << ' ' << y;
																															//				break;
																															//			}
																															//		}
																															//	}
																															//	if (c == 0)
																															//		cout << "NONE";
																															//
																															//
																															//
																															//	return 0;
																															//}
																															//
																															//
																															//
																															//  
																															/*for (int i = 0;i <= 121;i++)
																																	for (int j = 0;j <= 121;j++)
																																		ar[i][j] = '0';
																																cin >> n >> m;
																																for(int i=1;i<=n;i++)
																																	for (int j = 1;j <= m;j++)
																																	{
																																		cin >> ar[i][j];
																																	}
																																for (int i = 1;i <= n;i++)
																																	for (int j = 1;j <= m;j++)
																																	{
																																		if (ar[i][j] != '0')
																																		{
																																			s++;
																																			dfs(i, j);
																																		}
																																	}
																																cout << s;*/
																																//int n, m, s;
																																//char ar[122][122] ;
																																//int p[4] = { 1,0,-1,0 };
																																//int q[4] = { 0,1,0,-1 };
																																//void dfs(int x, int y)
																																//{
																																//	if (ar[x][y] != '0')
																																//	{
																																//		ar[x][y] = '0';
																																//		for (int i = 0;i < 4;i++)
																																//			dfs(x + q[i], y + p[i]);
																																//	}
																																//	return;
																																//}
																																/*cin >> n >> m;
																																	for (int i = 1;i <= m;i++)
																																	{
																																		int x, v, y;
																																		cin >> x >> y >> v;
																																		a[x][y] = v;
																																		a[y][x] = v;
																																	}
																																	for(int i = 1;i <= n;i++)
																																	{
																																		b[i] = 1;
																																		dfs(i);
																																		memset(b, 0, sizeof(b));
																																	}
																																	cout << s;*/
																																	//int n, m, a[300][300],s=-1000,d;
																																	//bool b[300];
																																	//void dfs(int k)
																																	//{
																																	//	for (int i = 1;i <= n;i++)
																																	//	{
																																	//		if (!b[i] && a[k][i])
																																	//		{
																																	//			b[i] = 1;
																																	//			d += a[k][i];
																																	//			dfs(i);
																																	//			d -= a[k][i];
																																	//		}
																																	//	}
																																	//	s = max(s, d);
																																	//	b[k] = 0;
																																	//	return;
																																	//}
																																	/*cin >> n >> k;
																																		for (int i = 0;i < n;i++)
																																			cin >> ar[i];
																																		f(0, 0, 0);
																																		cout << c;*/
																																		//#include "head.cpp"
																																		//using namespace std;
																																		//int ar[20], k,c,t,n;
																																		////bool prime(int n)
																																		////{
																																		////	for (int i = 2;i * i <= n;i++)
																																		////		if (n % i == 0)return 0;
																																		////	return n != 1;
																																		////}
																																		//void f(int a, int s, int m)
																																		//{
																																		//	if (a == k)
																																		//		if (prime(s))
																																		//		{
																																		//			c++;
																																		//			return;
																																		//		} 
																																		//	for (int i = m;i < n;i++)
																																		//	{
																																		//		f(a + 1, s + ar[i], i + 1);
																																		//	}
																																		//	return;
																																		//}
																																		//int a[20], k,c,t;
																																		//bool prime(int n)
																																		//{
																																		//	for (int i = 2;i * i <= n;i++)
																																		//		if (n % i == 0)return 0;
																																		//	return n != 1;
																																		//}
																																		//void f(int n)
																																		//{
																																		//	if (n == k)
																																		//		if (prime(t))c++;
																																		//	for(int i=0;i<)
																																		//
																																		//
																																		//
																																		//}
																																		/*cin >> n;
																																			queue(1);
																																			cout << t;*/
																																			//int a[100], b[100], c[100], d[100];
																																			//int t;
																																			//int n;
																																			//void print()
																																			//{
																																			//	if (t <= 2)
																																			//	{
																																			//		for (int k = 1;k <= n;k++)
																																			//			cout << a[k] << ' ' ;
																																			//		cout<< endl;
																																			//	}
																																			//	t++;
																																			//}
																																			//void queue(int i)
																																			//{
																																			//	if (i > n)
																																			//	{
																																			//		print();
																																			//		return;
																																			//	}
																																			//	else
																																			//	{
																																			//		for (int j = 1;j <= n;j++)
																																			//		{
																																			//			if ((!b[j]) && (!c[i + j]) && (!d[i - j + n]))
																																			//			{
																																			//				a[i] = j;
																																			//
																																			//				b[j] = 1;
																																			//				c[i + j] = 1;
																																			//				d[i - j + n] = 1;
																																			//
																																			//				queue(i + 1);
																																			//				b[j] = 0;
																																			//				c[i + j] = 0;
																																			//				d[i - j + n] = 0;
																																			//			}
																																			//		}
																																			//	}
																																			//}
																																			/*//int  b[5001][5001];
																																			//int n, m;
																																			cin >> n >> m;
																																				int x, y, ans = 0,t;
																																				for (int i = 0;i < n;i++)
																																				{
																																					cin >> x >> y;
																																					cin >> b[x][y];
																																				}
																																				for (int i = 1;i < 5001;i++)
																																				{
																																					b[0][i] += b[0][i - 1];
																																					b[i][0] += b[i - 1][0];
																																				}
																																				for(int i=1;i<=5000;i++)
																																					for (int j = 1;j <= 5000;j++)
																																					{
																																						b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + b[i][j];
																																					}
																																				ans = b[m - 1][m - 1];
																																				for (int i = m;i <= 5000;i++)
																																				{
																																					t = b[m - 1][i] - b[m - 1][i - m];
																																					if (t > ans)ans = t;
																																				}
																																				for (int i = m;i <= 5000;i++)
																																				{
																																					t = b[i][m-1] - b[i-m][m-1];
																																					if (t > ans)ans = t;
																																				}
																																				for (int i = m;i <= 5000;i++)
																																					for (int j = m;j <= 5000 ;j++)
																																					{
																																						t = b[i][j] - b[i - m][j] - b[i][j -m] + b[i -m][j -m];
																																						if (t > ans)ans = t;
																																					}
																																				cout << ans;*/
																																				//#define MAX_N 10000
																																				//int prime[MAX_N];//存储素数
																																				//bool is_prime[MAX_N + 1];
																																				//int sieve(int n) {
																																				//	int p = 0;
																																				//	for (int i = 0;i <= n;i++) 
																																				//		is_prime[i] = true;//初始化
																																				//	is_prime[0] = is_prime[1] = false;//初始化
																																				//	for (int i = 2;i <= n;i++) {
																																				//		if (is_prime[i]) {
																																				//			prime[p++] = i;
																																				//			//j+=i提升倍数
																																				//			for (int j = 2 * i;j <= n;j += i) 
																																				//				is_prime[j] = false;//划去素数i的倍数
																																				//		}
																																				//	}
																																				//	return p;
																																				//}
																																				/*for (int i = 0;i < sieve(100);i++)
																																						cout << prime[i] << ' ';*/
																																						//void prime_table(int n)
																																						//{
																																						//	int p[n];
																																						//	int i, j;
																																						//	p[0] = p[1] = 0;
																																						//	for (i = 2;i <= n;i++)
																																						//		p[i] = 1;
																																						//	i = 2;
																																						//	while (i <= 1000)
																																						//	{
																																						//		for (j = i + i;j <= n;j += i)
																																						//			p[j] = 0;
																																						//		for (i++;!p[i];i++);
																																						//		for(i)	}
																																						//}
																																						/*
																																						 (+c)--------(-c)
																																							|          |
																																							|          |
																																							|          |
																																							------------
																																						   (-c)         +c*/
																																						   /*int cf[2000][2000];
																																							   int n, m;
																																							   int x1, x2, y1, y2;
																																							   cin >> n >> m;
																																							   while (m--)
																																							   {
																																								   cin >> x1 >> y1 >> x2 >> y2;
																																								   for (int i = x1;i <= x2;i++)
																																								   {
																																									   cf[i][y1]++;
																																									   cf[i][y2 + 1]--;
																																								   }
																																							   }
																																							   for (int i = 1;i <= n;i++)
																																							   {
																																								   for (int j = 1;j <= n;j++)
																																								   {
																																									   cf[i][j] += cf[i][j - 1];
																																									   cout << cf[i][j] << ' ';
																																								   }
																																								   cout << endl;
																																							   }*/
																																							   /*cin >> n >> m;
																																								   for (int i = 1;i <= m;i++)
																																								   {
																																									   for (int j = 1;j <= 4;j++)
																																										   cin >> p[j];
																																									   for (int i = p[1];i <= p[3];i++)
																																										   for (int j = p[2];j <= p[4];j++)
																																											   a[i][j]++;
																																								   }
																																								   for (int i = 1;i <= n;i++)
																																								   {
																																									   for (int j = 1;j <= n;j++)
																																										   cout << a[i][j] << ' ';
																																									   cout << endl;
																																								   }*/
																																								   //int a[1001][1001],s[1001][1001],p[5];
																																								   //int n, m;
																																								   //int s[101][101], a[101][101];
																																								   //int n, m, ans = 0;
																																								   //bool f(int a1, int b, int len)
																																								   //{
																																								   //	int x = a1 + len - 1, y = b + len - 1;
																																								   //	if (len*len == s[x][y]+s[a1-1][b-1]-s[x][b-1]-s[a1-1][y])return 1;
																																								   //	return 0;
																																								   //}
																																								   /*cin >> n >> m;
																																									   for(int i=1;i<=n;i++)
																																										   for (int j = 1;j <= m;j++)
																																										   {
																																											   cin >> a[i][j];
																																											   s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
																																										   }
																																									   int l, r, d, mid;
																																									   for (int i = 1;i <= n;i++)
																																										   for (int j = 1;j <= m;j++)
																																										   {
																																											   if (a[i][j] == 0)continue;
																																											   d = min(n - i + 1, m - j + 1);
																																											   l = 1, r = d;
																																											   while (l < r)
																																											   {
																																												   mid = (l + r) / 2;
																																												   if (f(i, j, mid))l = mid+1;
																																												   else r = mid;
																																											   }
																																											   ans = max(ans, l-1);
																																										   }
																																									   cout << ans;*/
																																									   //int a[2000][2000];
																																									   //int cmp(int a, int b)
																																									   //{
																																									   //	return a > b;
																																									   //}
																																									   /*int n;
																																										   cin >> n;
																																										   int t;
																																										   for(int i=1;i<n;i++)
																																											   for (int j = i + 1;j <= n;j++)
																																											   {
																																												   cin >> t;
																																												   a[i][j] = a[j][i] = t;
																																											   }
																																										   for (int i = 0;i <= n;i++)
																																										   {
																																											   sort(a[i], a[i] + n + 1, cmp);
																																										   }
																																										   t = a[0][1];
																																										   for (int i = 1;i <= n;i++)
																																										   {
																																											   if (a[i][1] > t)
																																												   t = a[i][1];
																																										   }
																																										   cout << 1 << endl << t;*/
																																										   /*long long int a, b, p,s=1;
																																											   cin >> a >> b >> p;
																																											   s = f(a, b, p);
																																											   cout << a << '^' << b << ' ' << "mod" << ' ' << p << '=' << s;*/
																																											   //int qpow(int a, int n)
																																											   //{
																																											   //	int ans = 1;
																																											   //	while (n)
																																											   //	{
																																											   //		if (n & 1) //如果n的当前末位为1
																																											   //			ans *= a;
																																											   //		a *= a;
																																											   //		n >>= 1;//n往右移一位
																																											   //	}
																																											   //	return ans;
																																											   //}
																																											   //long long int f(long long int a, long long int b, long long  int p)
																																											   //{
																																											   //	if (b == 0)return 1;
																																											   //	if (b == 1)return a;
																																											   //	if (b % 2 == 1)
																																											   //	{
																																											   //		return (a * f(a * a % p, b / 2, p)) % p;
																																											   //	}
																																											   //	else
																																											   //		return f(a * a % p, b / 2, p) % p;
																																											   //}
																																											   /*int cmp(int a, int b)
																																											   //{
																																											   //	return a > b;
																																											   //}int n, m;
																																												   cin >> n >> m;
																																												   int* a = new int[m];
																																												   for (int i = 0;i < m;i++)
																																												   {
																																													   cin >> a[i];
																																												   }
																																												   sort(a, a + m,cmp);
																																												   int  s = 0;
																																												   int l = 0,r = m - 1;
																																												   while (l <= r)
																																												   {
																																													   if (a[l] + a[r] <= n)
																																														   s++, l++, r--;
																																													   else
																																														   l++, s++;
																																												   }
																																												   cout << s;*/
																																												   /*for (int i = 0;i < m;i++)
																																												   *
																																														   b[i] = true;
																																													   {
																																														   while (b[i])
																																														   {
																																															   for (int j = m-1;j>i;j--)
																																															   {
																																																   if ((a[i] + a[j]) <= n && b[j])
																																																   {
																																																	   b[j] = false;
																																																	   b[i] = false;
																																																	   s++;
																																																	   break;
																																																   }
																																																   if (i == j)
																																																   {
																																																	   s++;
																																																	   b[i] = false;
																																																	   break;
																																																   }
																																															   }
																																														   }
																																													   }*/
																																													   //struct milk
																																													   //{
																																													   //	int p, k;
																																													   //};
																																													   //int cmp(milk a,milk b)
																																													   //{
																																													   //	return a.p < b.p;
																																													   //}
																																													   /*int n, m;
																																														   cin >> n >> m;
																																														   milk* a = new milk[m];
																																														   for (int i = 0;i < m;i++)
																																															   cin >> a[i].p>>a[i].k;
																																														   sort(a, a + m,cmp);
																																														   int c = 0;
																																														   for (int i = 0;i < m;i++)
																																														   {
																																															   while (a[i].k != 0&&n!=0)
																																															   {
																																																   c += a[i].p;a[i].k--;n--;
																																															   }
																																															   if (n == 0)
																																																   break;

																																														   }
																																														   cout << c;*/
																																														   //struct home
																																														   //{
																																														   //	int s, v;
																																														   //}a[100010];
																																														   //int q[100010];
																																														   //int h[100010], qm[100010];
																																														   //int n;
																																														   //bool cmp(home a, home b)
																																														   //{
																																														   //	return a.v > b.v;
																																														   //}
																																														   //
																																														   //int main()
																																														   //{
																																														   //		cin >> n;
																																														   //	for (int i = 1;i <= n;i++)
																																														   //		cin >> a[i].s;
																																														   //	for (int i = 1;i <= n;i++)
																																														   //		cin >> a[i].v;
																																														   //		sort(a + 1, a + 1 + n, cmp);
																																														   //	for (int i = n;i >= 1;i--)
																																														   //		h[i] = max(h[i + 1], 2 * a[i].s + a[i].v);
																																														   //	for (int i = 1;i <= n;i++)
																																														   //		qm[i] = max(qm[i - 1], a[i].s);
																																														   //	for (int i = 1;i <= n;i++) 
																																														   //		q[i] = q[i - 1] + a[i].v;
																																														   //	for (int i = 1;i <= n;i++)
																																														   //		cout << max(q[i - 1] + h[i], q[i] + 2 * qm[i]) << endl;
																																														   //	
																																														   //	return 0;
																																														   //}
																																														   /*
																																														   #include<iostream>
																																														   #include<cmath>
																																														   #include<iomanip>
																																														   #include<stdlib.h>
																																														   #include<algorithm>
																																														   #include <cstring>
																																														   #include<vector>
																																														   using namespace std;
																																														   int main()
																																														   {
																																															   long long int l, k;
																																															   cin >> l >> k;
																																															   long long int min = 1, max = 999999999999, ans = -1;
																																															   long long  a[100001];
																																															   for (int i = 1;i <= l;i++)
																																															   {
																																																   cin >> a[i];
																																															   }

																																															   while (min <= max)
																																															   {
																																																   long long int s = 0, t = 0;
																																																   long long int m = (min + max) / 2;
																																																   for (int i = 1;i <= l;i++)
																																																   {
																																																	   s += a[i];
																																																	   if (s >= m)
																																																	   {
																																																		   s = 0;t++;
																																																	   }
																																																	   if (s < 0)
																																																	   {
																																																		   s = 0;
																																																	   }
																																																   }
																																																   if (t <= k)
																																																   {
																																																	   max = m - 1;
																																																	   if (t == k)
																																																	   {
																																																		   ans = m;
																																																	   }
																																																   }
																																																   else
																																																	   min = m + 1;
																																															   }
																																															   if (ans != -1)
																																															   {
																																																   cout << ans << ' ';
																																																   long long as = -1;long long int min = 1, max = 9999999999;
																																																   while (min <= max)
																																																   {
																																																	   long long s = 0,
																																																		t = 0;

																																																	   int m = (min + max) / 2;
																																																	   for (int i = 1;i <= l;i++)
																																																	   {
																																																		   s += a[i];
																																																		   if (s >= m)
																																																		   {
																																																			   s = 0;t++;
																																																		   }
																																																		   if (s < 0)
																																																		   {
																																																			   s = 0;
																																																		   }
																																																	   }
																																																	   if (t <= k-1)
																																																	   {
																																																		   max = m - 1;

																																																	   }
																																																	   else
																																																	   {
																																																		   min = m + 1;
																																																		   if (t == k)
																																																		   {
																																																			   as = m;
																																																		   }
																																																	   }
																																																   }
																																																   cout << as;
																																															   }
																																															   else
																																																   cout << -1;


																																															   return 0;
																																														   }
																																														   //int n;
																																															   //cin >> n;
																																															   //long long int* a = new long long int[n];
																																															   //for (int i = 0;i < n;i++)
																																															   //	cin >> a[i];
																																															   //sort(a, a + n);
																																															   //long long int s = 0, c = 1;
																																															   //long long int l = 0,r = n - 1;
																																															   //s += p(a[n - 1]);
																																															   //while (l <= r)
																																															   //{
																																															   //	if (c % 2 == 1)
																																															   //	{
																																															   //		s += p(a[r--] - a[l]);c++;
																																															   //	}
																																															   //	else
																																															   //	{
																																															   //		s += p(a[r] - a[l++]);c++;
																																															   //	}
																																															   //}//long long int p(long long int n)
																																														   //{
																																														   //	return n * n;
																																														   //}
																																															   //*s += p(a[n / 2 - 1] - a[n / 2]);*/
																																															   //cout << s;
																																														   /*for (int i = 0;i < n / 2;i++)
																																															   {
																																																   s += p(a[i] - a[n - 1 - i]);
																																															   }
																																															   if (n % 2 == 0)
																																															   {
																																																   cout << s;
																																															   }
																																															   else
																																															   {
																																																   s += p(a[n / 2 - 1] - a[n / 2]);
																																																   cout << s;
																																															   }*/

																																															   /*
																																															   #include<cstdio>
																																															   long long a[1000001];
																																															   int main()
																																															   {
																																																   long long inf = 9999999999999, ans = -1, n = 0, m = 0;
																																																   scanf("%lld %lld", &n, &m);
																																																   for (long long i = 1;i <= n;i++)
																																																   {
																																																	   scanf("%lld", &a[i]);
																																																   }
																																																   long long l = 1, r = inf;
																																																   while (l <= r)
																																																   {
																																																	   long long mid = (l + r) / 2;
																																																	   long long su = 0, t = 0;
																																																	   for (long long i = 1;i <= n;i++)
																																																	   {
																																																		   su += a[i];
																																																		   if (su >= mid)
																																																		   {
																																																			   t++;su = 0;
																																																		   }
																																																		   if (su < 0)
																																																			   su = 0;
																																																	   }
																																																	   if (t <= m)
																																																	   {
																																																		   r = mid - 1;
																																																		   if (t == m)
																																																			   ans = mid;
																																																	   }
																																																	   else l = mid + 1;
																																																   }
																																																   if (ans != -1)
																																																   {
																																																	   printf("%lld", ans);
																																																   }
																																																   return 0;
																																															   }


																																															   */


																																															   //double a, b, c, d;
																																															   //int s = 0;
																																															   //double f(double x)
																																															   //{
																																															   //	return a * x * x * x + b * x * x + c * x + d;
																																															   //}
																																															   //int main()
																																															   //{
																																															   //	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
																																															   //	double n, m;
																																															   //	for (int i = -100;i < 100;i++)
																																															   //	{
																																															   //		double l = i,r=i+1,md;
																																															   //		n = f(l);
																																															   //		m = f(r);
																																															   //		cout << setiosflags(ios::fixed) << setprecision(2);
																																															   //		if (!n )
																																															   //		{
																																															   //			cout << l << ' ';s++;
																																															   //		}
																																															   //		if (n * m < 0)
																																															   //		{
																																															   //			while (r - l >= 0.00001)
																																															   //			{
																																															   //				md = (l + r) / 2;
																																															   //				if (f(md) * f(r) <= 0)
																																															   //					l = md;
																																															   //				else r = md;
																																															   //			}
																																															   //			cout << r << ' ';s++;
																																															   //		}
																																															   //		if (s == 3)break;
																																															   //	}
																																															   //char s[10], t[10];
																																															   //bool vis[10];
																																															   //int n;
																																															   //void dfs(int step) {
																																															   //	if (step == n)
																																															   //	{
																																															   //		t[step] = '\0';
																																															   //		cout << t << endl;
																																															   //	}
																																															   //	else 
																																															   //		for (int i = 0;i < n;i++)
																																															   //		{
																																															   //			if (vis[i] == 0)
																																															   //			{
																																															   //				vis[i] = 1;
																																															   //				t[step] = s[i];
																																															   //				dfs(step + 1);
																																															   //				vis[i] = 0;
																																															   //			}
																																															   //		}
																																															   //}
																																															   /*cin >> n;
																																															   search(1);*/
																																															   //int n;int num[10001];
																																															   //bool mark[10001];
																																															   //bool check(int x, int y)
																																															   //{
																																															   //	int k = 2, i = x + y;
																																															   //	while (k <= sqrt(i) && i % k != 0)k++;
																																															   //	if (k > sqrt(i))return true;
																																															   //	return false;
																																															   //}
																																															   //void print()
																																															   //{
																																															   //	for (int i = 1;i <= n;i++)
																																															   //		cout << num[i]<<' ';
																																															   //}
																																															   //void search(int x)
																																															   //{
																																															   //	if (x == n + 1 && check(num[1], num[n]))print();//加条件num[1]==1可以规范初始值为1
																																															   //	else
																																															   //	{
																																															   //		for(int i=1;i<=n;i++)
																																															   //			if (!mark[i] && check(num[x - 1], i))
																																															   //			{
																																															   //				num[x] = i;mark[i] = true;
																																															   //				search(x + 1);mark[i]=false;
																																															   //			}
																																															   //	}
																																															   //}
																																															   //int r, a[100], n;
																																															   //void dfs(int k)
																																															   //{
																																															   //	int i;
																																															   //	if (k > r)
																																															   //	{
																																															   //		for (i = 1;i <= r;i++)
																																															   //			cout << setw(3) << a[i];
																																															   //		cout << endl;
																																															   //		return;
																																															   //	}
																																															   //	for (i = a[k - 1] + 1;i <= n;i++)
																																															   //	{
																																															   //		a[k] = i;
																																															   //		dfs(k + 1);
																																															   //	}
																																															   //}cin >> n >> r;
																																															   //	dfs(1);*/
																																															   /*int n, m, a[10002], tmp;
																																																   cin >> n >> m;
																																																   for (int i = 1;i <= n;i++)
																																																	   cin >> a[i];
																																																   int k, j;
																																																   for (int i = 1;i <= m;i++)
																																																   {
																																																	   for (j = n;j > 1 && a[j] < a[j - 1];j--);
																																																	   for (k = j;k <= n && a[j - 1] < a[k];k++);
																																																   }*/
																																																   //int n, m;
																																																	   //cin >> n >> m;
																																																	   //int* a = new int[n];
																																																	   //for (int i = 0;i < n;i++)
																																																	   //{
																																																	   //	cin >> a[i];a[i] += '0';
																																																	   //}
																																																	   ///*for (int i = 0;i < n;i++)
																																																	   //{
																																																	   //	cout << a[i]-'0' << ' ';
																																																	   //}
																																																	   //cout << endl;*/
																																																	   //for (int i = 0;i < m;i++)
																																																	   //{
																																																	   //	next_permutation(a, a + n);
																																																	   //}
																																																	   //for (int i = 0;i < n-1;i++)
																																																	   //{
																																																	   //	cout << a[i]-'0' << ' ';
																																																	   //}
																																																	   //cout << a[n - 1]-'0';
																																																   //char a[] = "12345";//12453..12435
																																																	   //char* s=a;
																																																	   //int n = strlen(a);
																																																	   //while (next_permutation(a, a + n))
																																																	   //{
																																																	   //	puts(a);
																																																	   //}
																																																   //char s1[] = "1234", s2[] = "876543";
																																																	   ////reverse(s1, s1 + strlen(s1));
																																																	   ////printf("%s\n", s1);
																																																	   //int n = strlen(s1);
																																																	   //int c = 0;
																																																	   //do
																																																	   //{
																																																	   //	puts(s1);
																																																	   //	c++;
																																																	   //} while (next_permutation(s1, s1 + n));
																																																	   //cout << c << endl<<endl;
																																																	   //cout << strlen(s2);
																																																   /*char* aa;
																																																	   aa = s2;
																																																	   cout << *(aa+4);*/
																																																	   //bool prime(int n)
																																																	   //{
																																																	   //    for (int i = 2;i * i <= n;i++)
																																																	   //        if (n % i == 0)return 0;
																																																	   //    return n != 1;
																																																	   //}
																																																	   //int c = 0;
																																																	   //int n,k;
																																																	   //int a[21];
																																																	   //void dfs(int m, int t, int s);
																																																	   //int main()
																																																	   //{
																																																	   //    cin >> n >> k;
																																																	   //    for (int i = 0;i < n;i++)
																																																	   //        cin >> a[i];
																																																	   //    dfs(0, 0, 0);
																																																	   //    cout << c;
																																																	   //
																																																	   //    return 0;
																																																	   //}
																																																	   //void dfs(int m, int t, int s)
																																																	   //{
																																																	   //    if (k == t)
																																																	   //        if (prime(s))
																																																	   //            c++;
																																																	   //    for (int i = m;i < n;i++)
																																																	   //    {
																																																	   //        dfs(i + 1, t + 1, s + a[i]);
																																																	   //    }
																																																	   //}
																																																	   /*student1 aa;
																																																		   aa.display1();
																																																		   */
																																																		   //class student
																																																		   //{
																																																		   //public:
																																																		   //    student()
																																																		   //    {
																																																		   //        num = 3;
																																																		   //        name = "hh";
																																																		   //        sex = 'm';
																																																		   //    }
																																																		   //    void display()
																																																		   //    {
																																																		   //        cout << 1 << endl;
																																																		   //        cout << num << endl;
																																																		   //    }
																																																		   //private:
																																																		   //    int num;
																																																		   //    string name;
																																																		   //    char sex;
																																																		   //};
																																																		   //class student1 :public student
																																																		   //{
																																																		   //public:
																																																		   //    void display1()
																																																		   //    {
																																																		   //        display();
																																																		   //        cout << 2;
																																																		   //    }
																																																		   //private:
																																																		   //    int age;
																																																		   //    string addr;
																																																		   //};
																																																		   /* compare<int>cmp(3, 7);
																																																			   cout << cmp.max();*/
																																																			   //template<class numtype>
																																																			   //class compare
																																																			   //{
																																																			   //public:
																																																			   //    compare(numtype a, numtype b) { x = a, y = b; }
																																																			   //    numtype max()
																																																			   //    {
																																																			   //        return (x > y) ? x : y;
																																																			   //    }
																																																			   //    numtype min()
																																																			   //    {
																																																			   //        return (x < y) ? x : y;
																																																			   //    }
																																																			   //private:
																																																			   //    numtype x, y;
																																																			   //};
																																																			   ////class Time
																																																			   //{
																																																			   //    int h, m, s;
																																																			   //};
																																																			   //class time 
																																																			   //{
																																																			   //public:
																																																			   //    time(int, int, int);
																																																			   //    const int h, m, s;
																																																			   //    friend void gettime();
																																																			   //
																																																			   //};
																																																			   //time::time(int a, int b, int c) :h(a), m(b), s(c) {};
																																																			   // void gettime()
																																																			   //{
																																																			   //    cout << ' ';
																																																			   //}
																																																			   /*class time* p;
																																																				   p = new class time;*/
																																																				   /*Time* p;
																																																					   p = new Time;*/
																																																					   /*class time t1(2, 3, 4);
																																																						   void(time:: * p)();
																																																						   p = &time::gettime;
																																																						   (t1.*p)();*/
																																																						   /*int n, k,s;
																																																							   cin >> n >> k;
																																																							   int* a = new int[n];
																																																							   for (int i = 0;i < n;i++)
																																																								   cin >> a[i];
																																																							   sort(a, a + n);
																																																						   */
																																																						   /*long long int sqr = 0, rec = 0;
																																																							   int m, n;
																																																							   cin >> m >> n;
																																																							   for(int i=1;i<=m;i++)
																																																								   for (int j = 1;j <= n;j++)
																																																								   {
																																																									   if(i == j)
																																																										   sqr += (m - i + 1) * (n - j + 1);
																																																									   else
																																																										   rec += (m - i + 1) * (n - j + 1);
																																																								   }
																																																							   cout << sqr << ' '<< rec;*/
																																																							   /*int m, n;
																																																								   scanf("%d %d", &m, & n);
																																																								   if (m < n)
																																																								   {
																																																									   int t = m;m = n;n = t;
																																																								   }
																																																								   printf("%d", gys(m, n));*/
																																																								   //int gys(int m, int n)
																																																								   //{#include<stdio.h>
																																																								   //    if (!n)return m;
																																																								   //    int r = m % n;
																																																								   //    return gys(n, r);
																																																								   //}
																																																								   //class box
																																																								   //{public:
																																																								   //    box();
																																																								   //    box(int, int, int);
																																																								   //    int v();
																																																								   //private:
																																																								   //    int h1, w1, l1;
																																																								   //
																																																								   //};
																																																								   //box::box()
																																																								   //{
																																																								   //    h1 = 1;w1 = 2;l1 = 4;
																																																								   //}
																																																								   //box::box(int h, int w, int l)
																																																								   //{
																																																								   //    h1 = h;w1 = w;l1 = l;
																																																								   //}
																																																								   //box boxl(12, 23, 25);
																																																								   //class student
																																																								   //{
																																																								   //public:
																																																								   //    void display();
																																																								   //    void in();
																																																								   //private:
																																																								   //    int n;
																																																								   //    string name;
																																																								   //    char sex;
																																																								   //};
																																																								   //void set(student&a)
																																																								   //{
																																																								   //     ;
																																																								   //}
																																																								   //void student::in()
																																																								   //{
																																																								   //    cin >> n >> name >> sex;
																																																								   //}
																																																								   //inline void student::display()
																																																								   //{
																																																								   //    cout << n;
																																																								   //    cout << name;
																																																								   //    cout << sex;
																																																								   //}
																																																								   //
																																																								   //
																																																								   //int main()
																																																								   //{
																																																								   //    student std;
																																																								   //    cin>>std
																																																								   //    std.display();
																																																								   /*int n;
																																																									   cin >> n;
																																																									   student* a = new student[n];
																																																									   for (int i = 0;i < n;i++)
																																																									   {
																																																										   cin >> a[i].name >> a[i].m1 >> a[i].m2 >> a[i].m3;
																																																										   a[i].s = a[i].m1 + a[i].m2 + a[i].m3;
																																																									   }
																																																									   for(int i=0;i<n-1;i++)
																																																										   for (int j = i + 1;j < n;j++)
																																																										   {
																																																											   if (abs(a[i].m1 - a[j].m1) <= 5 && abs(a[i].m2 - a[j].m2) <= 5 && abs(a[i].m3 - a[j].m3) <= 5 && abs(a[i].s - a[j].s) <= 10)
																																																											   {
																																																												   cout << a[i].name << ' ' << a[j].name << endl;
																																																											   }
																																																										   }*/
																																																										   //struct student {
																																																										   //    string name;
																																																										   //    int m1, m2, m3, s;
																																																										   //};
																																																										   /*int b[10000];
																																																											   int x, y;
																																																											   cin >> x >> y;
																																																											   if (y >= 10000000)y = 10000000;
																																																											   for (int i = x;i <= y;i+=2)
																																																											   {
																																																												   if (i % 2 == 0)
																																																												   {
																																																													   i++;continue;
																																																												   }
																																																													   if (h(i))
																																																													   {
																																																														   if (p(i))
																																																															   cout << i << endl;
																																																													   }

																																																											   }*/
																																																											   //int a[10], k = 0;
																																																											   //bool p(int n)
																																																											   //{
																																																											   //    for (int i = 2;i * i <= n;i++)
																																																											   //        if (n % i == 0)return 0;
																																																											   //    return n != 1;
																																																											   //}
																																																											   //bool h(int n)
																																																											   //{
																																																											   //    k = 0;
																																																											   //    while (n > 0) 
																																																											   //    {
																																																											   //        a[k++] = n % 10;
																																																											   //        n /= 10;
																																																											   //    }
																																																											   //    for (int i = 0;i < k / 2;i++)
																																																											   //    {
																																																											   //        if (a[i] != a[k - i - 1])return false;
																																																											   //    }
																																																											   //    return true;
																																																											   //}
																																																											   /*int a,s=0,i=0;
																																																												   while (cin >> a)
																																																												   {
																																																													   s += a;i++;
																																																												   }
																																																												   int n = s * pow(2, i - 1);
																																																												   cout << n;*/
																																																												   //struct student {
																																																												   //    string name;
																																																												   //    int age;
																																																												   //    int score;
																																																												   //};
																																																												   //student f(student a)
																																																												   //{
																																																												   //    a.score *= 1.2;
																																																												   //    a.age++;
																																																												   //    if (a.score > 600)a.score = 600;
																																																												   //    return a;
																																																												   //}
																																																												   /*int n;
																																																													   cin >> n;
																																																													   student* s = new student[n];
																																																													   for (int i = 0;i < n;i++)
																																																													   {
																																																														   cin >> s[i].name >> s[i].age >> s[i].score;
																																																														   s[i]=f(s[i]);
																																																													   }
																																																													   for (int i = 0;i < n;i++)
																																																													   {
																																																														   cout << s[i].name << ' ' << s[i].age << ' ' << s[i].score << endl;
																																																													   }*/
																																																													   /* int n;
																																																														   cin >> n;
																																																														   stu* student = new struct stu[n];
																																																														   for (int i = 0;i < n;i++)
																																																														   {
																																																															   cin >> student[i].name >> student[i].m1 >> student[i].m2 >> student[i].m3;
																																																															   student[i].s = student[i].m1 + student[i].m2 + student[i].m3;
																																																														   }
																																																														   stable_sort(student, student+n,cmp);
																																																														   cout<< student[0].name <<' '<<student[0].m1 << ' '<<student[0].m2 <<' '<< student[0].m3;*/
																																																														   //struct stu{
																																																														   //    string name;
																																																														   //    int m1, m2, m3;
																																																														   //    int s=0;
																																																														   //};
																																																														   //int cmp(stu a, stu b)
																																																														   //{
																																																														   //    return a.s > b.s;
																																																														   //}
																																																														   //int a[1024][1024];
																																																														   //int f(int a[][1024], int n,int x,int y)
																																																														   //{
																																																														   //    if (n == 1)return 0;
																																																														   //    for (int i = 0;i < n / 2;i++)
																																																														   //    {
																																																														   //        for (int j = 0;j < n / 2;j++)
																																																														   //            a[x + i][y + j] = 0;
																																																														   //    }
																																																														   //    f(a, n / 2, x + n / 2, y);
																																																														   //    f(a, n / 2, x , y+n/2);
																																																														   //    f(a, n / 2, x + n / 2, y+n/2);
																																																														   //
																																																														   //
																																																														   //}
																																																														   /*int n;
																																																															   cin >> n;
																																																															   int c = pow(2, n);
																																																															   for (int i = 0;i < c;i++)
																																																															   {
																																																																   for (int j = 0;j < c;j++)
																																																																	   a[i][j] = 1;
																																																															   }
																																																															   f(a, c, 0, 0);
																																																															   for (int i = 0;i < c;i++)
																																																															   {
																																																																   for (int j = 0;j < c;j++)
																																																																	   cout << a[i][j]<<' ';
																																																																   cout << endl;
																																																															   }*/
																																																															   //int prime(int n)
																																																															   //{
																																																															   //    for (int i = 2;i * i <= n;i++)
																																																															   //    {
																																																															   //        if (n % i == 0)return 0;
																																																															   //    }
																																																															   //    return n != 1;
																																																															   //}
																																																															   /*int a[10001] = { 0 };
																																																																   for (int i = 1;i < 10001;i++)
																																																																   {
																																																																	   if (prime(i)==1)
																																																																		   a[i] = 1;
																																																																   }
																																																																   int n;
																																																																   cin >> n;
																																																																   for (int i = 4;i <= n;i++,i++)
																																																																   {
																																																																	   for (int j = 1;j <= i/2;j++)
																																																																	   {
																																																																		   if (a[j] == 1 && a[i - j] == 1)
																																																																		   {
																																																																			   cout << i << '=' << j << '+' << i - j << endl;break;
																																																																		   }
																																																																	   }
																																																																   }*/
																																																																   //void adjust(vector<int>& arr, int len, int index)
																																																																   //{
																																																																   //    int left = 2 * index + 1;
																																																																   //    int right = 2 * index + 2;
																																																																   //    int maxIdx = index;
																																																																   //    if (left<len && arr[left]>arr[maxIdx])maxIdx = left;
																																																																   //    if (right<len && arr[right]>arr[maxIdx])maxIdx = right;
																																																																   //    if (maxIdx != index)
																																																																   //    {
																																																																   //        swap(arr[maxIdx], arr[index]);
																																																																   //        adjust(arr, len, maxIdx);
																																																																   //    }
																																																																   //}
																																																																   //void buildheap(vector<int>& arr, int size)
																																																																   //{
																																																																   //    for (int i = size / 2 - 1;i >= 0;i--)
																																																																   //    {
																																																																   //        adjust(arr, size, i);
																																																																   //    }
																																																																   //}
																																																																   //void heapsort(vector<int>& arr, int size)
																																																																   //{
																																																																   //    buildheap(arr, size);
																																																																   //    for (int i = size - 1;i >= 1;i--)
																																																																   //    {
																																																																   //        swap(arr[0], arr[i]);
																																																																   //        adjust(arr, i, 0);
																																																																   //    }
																																																																   //}
																																																																   /*vector<int> arr = { 8, 1, 14, 3, 21, 5, 7, 10 };
																																																																	   heapsort(arr, arr.size());
																																																																	   for (int i = 0;i < arr.size();i++)
																																																																	   {
																																																																		   cout << arr[i] << endl;
																																																																	   }*/
																																																																	   /*int n, k;
																																																																		   cin >> n >> k;
																																																																		   int a = k + 1;
																																																																		   for (int i = 0;i < n;i++)
																																																																			   a *= 2;
																																																																		   cout << a;*/
																																																																		   ////64
																																																																			   //string a, b;
																																																																			   //cin >> a >> b;
																																																																			   //int n=1, m=1,t;
																																																																			   //for (int i = 0;i < a.size();i++)
																																																																			   //{
																																																																			   //    t = a[i] - 64;
																																																																			   //    n *= t;
																																																																			   //}
																																																																			   //for (int i = 0;i < b.size();i++)
																																																																			   //{
																																																																			   //    t = b[i] - 64;
																																																																			   //    m *= t;
																																																																			   //}
																																																																			   //if (n % 47 == m % 47)
																																																																			   //    cout << "GO";
																																																																			   //else
																																																																			   //    cout << "STAY";
																																																																		   //using namespace std;
																																																																		   //char dic[30][20] = { "zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty","a","both","another","first","second","third" };//对应
																																																																		   //int di[30] = { 0,1,4,9,16,25,36,49,64,81,00,21,44,69,96,25,56,89,24,61,0,1,4,1,1,4,9 };
																																																																		   //int a[10], top=0, flag=0;
																																																																		   //int i, j;
																																																																		   //char s[100];
																																																																		   //int main()
																																																																		   //{
																																																																		   //    for (i = 1;i <= 6;i++)
																																																																		   //    {
																																																																		   //        scanf("%s", s);
																																																																		   //        for (j = 1;j <= 26;j++)
																																																																		   //        {
																																																																		   //            if (!strcmp(s, dic[j])) 
																																																																		   //            {
																																																																		   //                a[++top] = di[j]; 
																																																																		   //                break; 
																																																																		   //            }
																																																																		   //        }
																																																																		   //    }
																																																																		   //    sort(a + 1, a + top + 1); 
																																																																		   //    for (i = 1;i <= top;i++)
																																																																		   //    {
																																																																		   //        if (flag) 
																																																																		   //        {
																																																																		   //            printf("%.2d", a[i]); 
																																																																		   //        }
																																																																		   //        else
																																																																		   //        {
																																																																		   //            if (a[i])
																																																																		   //            {
																																																																		   //                printf("%d", a[i]);
																																																																		   //                flag = 1;
																																																																		   //            }
																																																																		   //        }
																																																																		   //    }
																																																																		   //    if (!flag)printf("0"); 
																																																																		   /*string p[27] = { "","one","two","three","four","five","six","seven",
																																																																		   "eight","nine","ten","elven","twelve","thirteen","fourteen","fifteen",
																																																																		   "sixteen","seventeen","eighteen","nineteen","twenty","a","both",
																																																																		   "another","first","second","third" };
																																																																			   string sz[27] = { "00","01","04","09","16","25","36","49","64","81","00","21","44","69","96","25","56","89","24","61","00","01","04","01","01","04","09" };
																																																																			   string s;
																																																																			   string m[6];
																																																																			   int n=0;
																																																																			   for (int i = 0;i < 7;i++) {
																																																																				   cin >> s;
																																																																				   for (int j = 0;j < 27;j++) {
																																																																					   if (s == p[j])
																																																																						   m[n++] = sz[j];
																																																																				   }
																																																																			   }*/

																																																																			   /*string s;
																																																																				   cin >> s;
																																																																				   int c=0,l=s.size();
																																																																				   char p='0';
																																																																				   for (int i = 0;i < l;i++) {
																																																																					   if ('0' <= s[i] && s[i] <= '9')c++;
																																																																					   else {
																																																																						   p = s[i];
																																																																						   break;
																																																																					   }
																																																																				   }
																																																																				   int m = c - 1;
																																																																				   while (s[m] == '0' && m != 0)m--;
																																																																				   for (int i = m;i >= 0;i--)
																																																																					   cout << s[i];
																																																																				   if (p == '0')
																																																																					   return 0;
																																																																				   else if (p == '%') {
																																																																					   cout << p;return 0;
																																																																				   }
																																																																				   else
																																																																					   cout << p;
																																																																				   while (s[c + 1] == '0' && c < l - 2)c++;
																																																																				   while (s[l - 1] == '0' && l - 2 > c)l--;
																																																																				   for (int i = l - 1;i > c;i--)
																																																																					   cout << s[i];*/
																																																																					   /*string s;
																																																																						   cin >> s;
																																																																						   int a, b,c=1;
																																																																						   for (int i = 0;i < s.size();i++) {
																																																																							   if (s[i] == '.') {
																																																																								   a = i;
																																																																								   c = 2;
																																																																								   break;
																																																																							   }
																																																																							   else if(s[i]=='/') {
																																																																								   a = i;
																																																																								   c = 3;
																																																																								   break;
																																																																							   }
																																																																							   else if (s[i] == '%') {
																																																																								   a = i;
																																																																								   c = 4;
																																																																								   break;
																																																																							   }
																																																																						   }
																																																																						   b = s.size()-1;
																																																																						   switch (c) {
																																																																						   case 1:
																																																																							   while (s[b] == '0'&&b!=0)b--;
																																																																							   for (int i = b;i >= 0;i--)
																																																																								   cout << s[i];
																																																																							   break;
																																																																						   case 2:
																																																																							   while (s[a - 1] == '0' && a != 1)a--;
																																																																							   for (int i = a;i >= 0;i--)
																																																																								   cout << s[i];
																																																																							   cout << '.';

																																																																							   break;
																																																																						   case 3:
																																																																							   break;
																																																																						   case 4:
																																																																							   break;
																																																																						   }*/
																																																																						   /*string s;
																																																																							   cin >> s;
																																																																							   for(int i=0;i<s.size()-)*/
																																																																							   /*int n;
																																																																								   string s;
																																																																								   cin >>n>> s;
																																																																								   int t = s.size();
																																																																								   int c = 0,p=0;
																																																																								   for (int i = 0;i < t-1;i++) {
																																																																									   if (s[i] == 'V' && s[i + 1] == 'K')
																																																																										   s[i] = s[i + 1] = ' ',c++;
																																																																								   }
																																																																								   for (int i = 0;i < t - 1;i++) {
																																																																									   if ((s[i] == 'V' && s[i + 1] == 'V') || (s[i] == 'K' && s[i + 1] == 'K'))
																																																																										   p = 1;
																																																																								   }
																																																																								   if (p == 0)
																																																																									   cout << c;
																																																																								   else
																																																																									   cout << c + 1;*/
																																																																									   /*int ans=0;
																																																																										   string a;
																																																																										   int num[26] = { 1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4 };
																																																																										   getline(cin, a);
																																																																										   for (int i = 0;i < a.size();i++)
																																																																										   {
																																																																											   if (a[i] >= 'a' && a[i] <= 'z') ans += num[a[i] - 'a'];
																																																																											   if (a[i] == ' ') ans++;
																																																																										   }
																																																																										   printf("%d", ans);*/
																																																																										   /*string s1, s2;
																																																																											   getline(cin, s1);
																																																																											   getline(cin, s2);
																																																																											   int t1 = s1.size();
																																																																											   int t2 = s2.size();
																																																																											   int c = 0, a, w = 0;
																																																																											   for (int i = 0;i < t1;i++)
																																																																												   if (isupper(s1[i]))s1[i]=tolower(s1[i]);
																																																																											   for (int i = 0;i < t2;i++)
																																																																												   if (isupper(s2[i]))s2[i]=tolower(s2[i]);
																																																																											   for (int i = 0;i < t2;i++) {
																																																																												   a = 0;
																																																																												   if ((i==0||s2[i-1]==' ') && s2[i] == s1[0]&&(i+t1<t2&&s2[i+t1]==' ')) {
																																																																													   for (int j = 0;j < t1;j++) {
																																																																														   if (s2[i + j] == s1[j]) {
																																																																															   a++;
																																																																														   }
																																																																													   }
																																																																													   if (a == t1) {
																																																																														   c++;
																																																																														   if (c == 1)
																																																																															   w = i;
																																																																													   }
																																																																												   }
																																																																											   }
																																																																											   if (c == 0)
																																																																												   cout << -1;
																																																																											   else
																																																																												   cout << c << ' ' << w;*/
																																																																												   /*string str, l, r;
																																																																													   int t;
																																																																													   scanf("%d", &t);
																																																																													   cin >> str;
																																																																													   while (t--)
																																																																													   {
																																																																														   l = "";
																																																																														   r = "";
																																																																														   int lei, x, y;string in;
																																																																														   scanf("%d", &lei);
																																																																														   if (lei == 1)
																																																																														   {
																																																																															   cin >> in;
																																																																															   str += in;
																																																																															   cout << str;
																																																																														   }
																																																																														   if (lei == 2)
																																																																														   {
																																																																															   scanf("%d%d", &x, &y);
																																																																															   for (int i = x;i <= x + y - 1;i++)
																																																																																   in += str[i];
																																																																															   str = in;
																																																																															   cout << str;
																																																																														   }
																																																																														   if (lei == 3)
																																																																														   {
																																																																															   cin >> x >> in;
																																																																															   for (int i = 0;i < x;i++)
																																																																																   l += str[i];
																																																																															   for (int i = x;i <= str.size();i++)
																																																																																   r += str[i];
																																																																															   str = l + in + r;
																																																																															   cout << str;
																																																																														   }
																																																																														   if (lei == 4)
																																																																														   {
																																																																															   cin >> in;
																																																																															   if (str.find(in) == -1)
																																																																																   printf("-1");
																																																																															   else printf("%d", str.find(in));
																																																																														   }
																																																																														   cout << endl;
																																																																													   }*/
																																																																													   /*string s;//97-122
																																																																														   cin >> s;
																																																																														   int l = s.size();
																																																																														   int a[123] = { 0 };
																																																																														   int t;
																																																																														   for (int i = 0;i < l;i++) {
																																																																															   t = s[i];
																																																																															   a[t]++;
																																																																														   }
																																																																														   int max=a[97], min=a[t];
																																																																														   for (int i = 97;i < 123;i++) {
																																																																															   if (a[i] > max)
																																																																																   max = a[i];
																																																																															   if (a[i] < min&&a[i]!=0)
																																																																																   min = a[i];
																																																																														   }
																																																																														   t = max - min;
																																																																														   for (int i = 2;i * i < t;i++)
																																																																															   if (t % i == 0)
																																																																															   {
																																																																																   cout << "No Answer" << endl << 0;
																																																																																   return 0;
																																																																															   }
																																																																														   if (t == 0||t==1) {
																																																																															   cout << "No Answer" << endl << 0;
																																																																															   return 0;
																																																																														   }
																																																																														   else
																																																																															   cout << "Lucky Word" << endl << t;*/
																																																																															   /*string s;
																																																																																   cin >> s;
																																																																																   int p = s.size();
																																																																																   for (int i = 0;i < p;i++)
																																																																																	   if (s[i] >= 'a' && s[i] <= 'z')
																																																																																		   s[i] += 32;
																																																																																   for (int i = 0;i < p;i++)
																																																																																	   cout << s[i];*/
																																																																																	   /*char a, b = '0';
																																																																																		   int n=0, ans[1000001], t = 1;
																																																																																		   while (cin >> a) {
																																																																																			   n++;
																																																																																			   if (a == b) {
																																																																																				   ans[t]++;
																																																																																			   }
																																																																																			   else
																																																																																				   ans[++t]++, b = a;
																																																																																		   }
																																																																																		   cout << sqrt(n);
																																																																																		   for (int i = 1;i <= t;i++)
																																																																																			   cout <<" " << ans[i];*/
																																																																																			   /*int m,n,c=2;
																																																																																				   cin >> n;
																																																																																				   int ar[n][n];
																																																																																				   ar[n - 1][n - 1] = 2;
																																																																																				   int i = 0, j = 0;
																																																																																				   while (ar[n - 1][n - 1] == 2) {
																																																																																					   cin >> m;
																																																																																					   if (c % 2==0) {
																																																																																						   for (int a = 0;a < m;a++){
																																																																																							   ar[i][j++] = 0;
																																																																																							   if (j == n ) {
																																																																																								   i++;j = 0;
																																																																																							   }
																																																																																						   }
																																																																																					   }
																																																																																					   else
																																																																																						   for (int a = 0;a < m;a++) {
																																																																																							   ar[i][j++] = 1;
																																																																																							   if (j == n ) {
																																																																																								   i++;j = 0;
																																																																																							   }
																																																																																						   }
																																																																																					   c++;
																																																																																				   }
																																																																																				   for (int i = 0;i < n;i++)
																																																																																				   {
																																																																																					   for (int j = 0;j < n;j++)
																																																																																						   cout << ar[i][j];
																																																																																					   cout << endl;
																																																																																				   }*/
																																																																																				   //int n, m, k, a, b, ans;
																																																																																				   //int s[5005][5005];
																																																																																				   //bool pd(int x, int y) { 
																																																																																				   //    if (x < 1 || y < 1 || x > n || y > n) return 0;
																																																																																				   //    return 1;
																																																																																				   //}
																																																																																				   /*scanf("%d%d%d", &n, &m, &k);
																																																																																					   for (int i = 1; i <= m + k; i++) {
																																																																																						   scanf("%d%d", &a, &b);
																																																																																						   for (int x = -2; x <= 2; x++)
																																																																																							   for (int y = -2; y <= 2; y++)
																																																																																								   if ((i > m || abs(x) + abs(y) <= 2) && pd(x + a, b + y))
																																																																																									   s[x + a][b + y]++;
																																																																																					   }
																																																																																					   for (int i = 1; i <= n; i++)
																																																																																						   for (int j = 1; j <= n; j++)
																																																																																							   ans += s[i][j] == 0;
																																																																																					   printf("%d\n", ans); */
																																																																																					   //int a[21][21] = {0};
																																																																																						   //int n;
																																																																																						   //scanf("%d", &n);
																																																																																						   //for (int i = 1;i <= n;i++)
																																																																																						   //	a[i][1] = a[i][i] = 1;
																																																																																						   //for (int i = 1;i <= n;i++)
																																																																																						   //	for (int j = 2;j < i;j++)
																																																																																						   //		a[i][j] = a[i - 1][j - 1] + a[i - 1][j];////for (int i = 1;i <= n;i++)
																																																																																						   ////	a[i][1] = a[i][i] = 1;//赋初值
																																																																																						   ////for (int i = 1;i <= n;i++)
																																																																																						   ////	for (int j = 2;j < i;j++)//因为a[i][1]、a[i][i]已经赋值过了，所以循环是2~n-1
																																																																																						   ////		a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
																																																																																						   ////
																																																																																						   //
																																																																																						   //
																																																																																						   //
																																																																																						   //for (int i = 1;i <= n;i++)
																																																																																						   //{
																																																																																						   //	for (int j = 1;j <= i;j++)
																																																																																						   //		printf("%d ", a[i][j]);
																																																																																						   //	printf("\n");
																																																																																						   //}
																																																																																					   /*int n;
																																																																																						   cin >> n;
																																																																																						   int a[n][n] = {0};
																																																																																						   */
																																																																																						   /*bool b[2000001] = { 0 };
																																																																																							   int n, t;
																																																																																							   double a;
																																																																																							   int c;
																																																																																							   cin >> n;
																																																																																							   for (int i = 0;i < n;i++) {
																																																																																								   cin >> a >> t;
																																																																																								   for (int j = 1;j <= t;j++) {
																																																																																									   c = a * j;
																																																																																									   if (c > 2000000)return 0;
																																																																																									   if (b[c])b[c] = false;
																																																																																									   else b[c] = true;
																																																																																								   }
																																																																																							   }
																																																																																							   for (int i = 0;i < 2000001;i++) {
																																																																																								   if (b[i])
																																																																																									   t = i;
																																																																																							   }
																																																																																							   cout << t;*/
																																																																																							   //double a = 1.11111;
																																																																																							   //int t = a * 2;
																																																																																							   //cout << t;
																																																																																							   /*int a, b, c;
																																																																																								   cin >> a >> b >> c;
																																																																																								   int s[81] = { 0 },t=0,p=3;
																																																																																								   for (int i = 1;i <= a;i++)
																																																																																									   for (int j = 1;j <= b;j++)
																																																																																										   for (int k = 1;k <= c;k++)
																																																																																											   s[i + j + k]++;
																																																																																								   t = s[3];
																																																																																								   for (int i = 3;i <= 80;i++) {
																																																																																									   if (s[i] > t && s[i] != 0) {
																																																																																										   p = i;
																																																																																										   t = s[i];
																																																																																									   }
																																																																																								   }
																																																																																								   cout << p;*/
																																																																																								   /*int n = 1;
																																																																																									   for (int i = 9;i > 0;i--) n=(n + 1) * 2;
																																																																																									   cout << n;*/
																																																																																									   /*char ch;
																																																																																										   int l, s, n, o;
																																																																																										   l = s = n = o = 0;
																																																																																										   while ((ch = getchar()) != '\n') {
																																																																																											   if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')l++;
																																																																																											   else if (ch >= '0' && ch <= '9')n++;
																																																																																											   else if (ch == ' ')s++;
																																																																																											   else o++;
																																																																																										   }
																																																																																										   cout << "字母："<<l<<"  空格："<<s<<"  数字："<<n <<"  其他："<<o;*/
																																																																																										   /*int i, w = 0;
																																																																																											   cout << "当月利润：";
																																																																																											   cin >> i;
																																																																																											   int c = i / 100000;
																																																																																											   switch (c) {
																																																																																											   case 0: w = i * 0.1;    break;
																																																																																											   case 1: w = 10000 + (i - 100000) * 0.075; break;
																																																																																											   case 2:
																																																																																											   case 3:w = 17500 + (i - 200000) * 0.05;   break;
																																																																																											   case 4:
																																																																																											   case 5:w = 17500 + 200000 * 0.05 + (i - 400000) * 0.03;   break;
																																																																																											   case 6:
																																																																																											   case 7:
																																																																																											   case 8:
																																																																																											   case 9:w = 17500 + 2000 * 5 + 2000 * 3 + (i - 600000) * 0.015;   break;
																																																																																											   default:w = 17500 + 2000 * 5 + 2000 * 3 + 400 * 15 + (i - 1000000) * 0.01; break;
																																																																																											   }
																																																																																											   cout << "应发奖金：" << w;*/
																																																																																											   /*int i, w=0;
																																																																																												   cout << "当月利润：";
																																																																																												   cin >> i;
																																																																																												   if (i <= 100000)w = i *0.1;
																																																																																												   if (100000 < i&&i <= 200000)w = 10000 + (i - 100000) * 0.075;
																																																																																												   if (200000 < i &&i<= 400000)w = 17500 + (i - 200000) * 0.05;
																																																																																												   if(400000 < i&&i <= 600000)w = 17500 + 200000 * 0.05 + (i - 400000) * 0.03;
																																																																																												   if(600000 < i&&i <= 1000000)w = 17500 + 2000 * 5 + 2000 * 3 + (i - 600000) * 0.015;
																																																																																												   if (i>1000000)w = 17500 + 2000 * 5 + 2000 * 3 + 400 * 15 + (i - 1000000) * 0.01;
																																																																																												   cout<< "应发奖金：" << w;*/
																																																																																												   /*int n, m, s = 0;
																																																																																													   cin >> n>>m;
																																																																																													   int* a = new int[n];
																																																																																													   for (int i = 0;i < n;i++)
																																																																																														   cin >> a[i];
																																																																																													   for (int i = 0;i < m;i++)
																																																																																														   s += a[i];
																																																																																													   for (int i = 1;i < n - m;i++)
																																																																																													   {
																																																																																														   int k = 0;
																																																																																														   for (int j = i;j < m + i;j++)
																																																																																															   k += a[j];
																																																																																														   if (s > k)s = k;


																																																																																													   }
																																																																																													   cout << s;
																																																																																													   */
																																																																																													   /*int m[100], c = 0,  n;
																																																																																														   bool b[20001] = { 0 };
																																																																																														   cin >> n;
																																																																																														   for (int i = 0;i < n;i++) {
																																																																																															   cin >> m[i];
																																																																																															   b[m[i]] = true;
																																																																																														   }
																																																																																														   for(int i=0;i<n-1;i++)
																																																																																															   for (int j = i + 1;j < n;j++) {
																																																																																																   if (b[m[i] + m[j]]==true) {
																																																																																																	   c++;b[m[i] + m[j]] = false;
																																																																																																   }
																																																																																															   }
																																																																																														   cout << c;*/
																																																																																														   /*int n;
																																																																																															   cin >> n;
																																																																																															   int* m = new int[n];
																																																																																															   int* k = new int[n];
																																																																																															   for (int i = 0;i < n;i++)
																																																																																																   cin >> m[i];
																																																																																															   for (int i = 0;i < n;i++)
																																																																																															   {
																																																																																																   for (int j = i + 1;j < n;j++) {
																																																																																																	   if(m[])


																																																																																																   }
																																																																																															   }*/
																																																																																															   /*int f[39] = { 0 }, s = 0, m, n, p[10] = {0};
																																																																																																   cin >> n;
																																																																																																   for (int i = 0;i < 7;i++) {
																																																																																																	   cin >> m;
																																																																																																	   f[m] = 1;
																																																																																																   }

																																																																																																   for (int i = 0;i < n;i++) {
																																																																																																	   s = 0;
																																																																																																	   for (int j = 0;j < 7;j++) {
																																																																																																		   cin >> m;
																																																																																																		   if (f[m] == 1)s++;
																																																																																																	   }
																																																																																																	   p[s]++;

																																																																																																   }
																																																																																																   for (int i = 7;i >= 1;i--)
																																																																																																	   cout << p[i] << ' ';
																																																																																																   */
																																																																																																   //int f[33], p[10], n, m;
																																																																																																	   //cin >> n;
																																																																																																	   //for (int i = 0;i < 7;i++)
																																																																																																	   //{
																																																																																																	   //    cin >> m;
																																																																																																	   //    f[m] = 1;
																																																																																																	   //}
																																																																																																	   //for (int i = 1;i <= n;i++)
																																																																																																	   //{
																																																																																																	   //    int sum = 0;//中奖号码数量
																																																																																																	   //    for (int j = 1;j <= 7;j++)
																																																																																																	   //    {
																																																																																																	   //        cin >> m;
																																																																																																	   //        if (f[m] == 1)sum++;
																																																																																																	   //    }
																																																																																																	   //    p[sum]++;
																																																																																																	   //}
																																																																																																	   //for (int i = 7;i >= 1;i--)cout << p[i] << ' ';
																																																																																																   /*int n, k = 1;
																																																																																																	   cin >> n;
																																																																																																	   int a[n][n];
																																																																																																	   for (int i = 0;i < n;i++)
																																																																																																		   for (int j = 0;j < n;j++)
																																																																																																			   a[i][j] = 0;
																																																																																																	   a[0][n / 2] = k++;
																																																																																																	   while (k <= n * n) {
																																																																																																		   int r =0,c=0;
																																																																																																		   for (int i = 0;i < n;i++)
																																																																																																			   for (int j = 0;j < n;j++) {
																																																																																																				   if (a[i][j] == k - 1) {
																																																																																																					   r = i;c = j;
																																																																																																				   }
																																																																																																			   }
																																																																																																		   if (r == 0 && c != n - 1)
																																																																																																			   a[n - 1][c + 1] = k++;
																																																																																																		   else if (c == n - 1 && r != 0)
																																																																																																			   a[r - 1][0] = k++;
																																																																																																		   else if (r == 0 && c == n - 1)
																																																																																																			   a[r + 1][c] = k++;
																																																																																																		   else if (c != n - 1 && r != 0) {
																																																																																																			   if (a[r - 1][c + 1] == 0)
																																																																																																				   a[r - 1][c + 1] = k++;
																																																																																																			   else
																																																																																																				   a[r + 1][c] = k++;
																																																																																																		   }



																																																																																																	   }
																																																																																																	   for (int i = 0;i < n;i++) {
																																																																																																		   for (int j = 0;j < n;j++) {
																																																																																																			   cout << a[i][j] << ' ';
																																																																																																		   }
																																																																																																		   cout << endl;
																																																																																																	   }*/
																																																																																																	   //int l, w, h, q;///*int q;cin >> q;*///#define l 4
																																																																																																	   //#define w 4
																																																																																																	   //#define h 4
																																																																																																		   //cin >> l >> w >> h >> q;
																																																																																																		   //int a[l][w][h];
																																																																																																		   //for (int i = 0;i < l;i++)
																																																																																																		   //	for (int j = 0;j < w;j++)
																																																																																																		   //		for (int k = 0;k < h;k++)
																																																																																																		   //			a[i][j][k] = 1;
																																																																																																		   //int x1, y1, z1, x2, y2, z2;
																																																																																																		   //while (q--) {
																																																																																																		   //	cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
																																																																																																		   //	for (int i = min(x1,x2)-1;i < max(x1,x2);i++)
																																																																																																		   //		for (int j = min(y1, y2) - 1;j < max(y1, y2);j++)
																																																																																																		   //			for (int k = min(z1, z2) - 1;k < max(z1, z2) ;k++)
																																																																																																		   //				a[i][j][k] = 0;
																																																																																																		   //}
																																																																																																		   //int s = 0;
																																																																																																		   //for (int i = 0;i < l;i++)
																																																																																																		   //	for (int j = 0;j < w;j++)
																																																																																																		   //		for (int k = 0;k < h;k++)
																																																																																																		   //			s += a[i][j][k];
																																																																																																		   //cout << s;
																																																																																																	   /*struct Student {
																																																																																																		   int s1;
																																																																																																		   int s2;
																																																																																																		   int s3;
																																																																																																	   };
																																																																																																		   int n;
																																																																																																		   cin >> n;
																																																																																																		   int c = 0;
																																																																																																		   struct Student* a = new struct Student[n];
																																																																																																		   for (int i = 0;i < n;i++) {
																																																																																																			   cin >> a[i].s1 >> a[i].s2 >> a[i].s3;
																																																																																																		   }
																																																																																																		   int d1, d2, d3,d=0;
																																																																																																		   for (int i = 0;i < n;i++) {
																																																																																																			   for (int j = i+1;j < n;j++) {
																																																																																																				   d1 = a[i].s1 - a[j].s1;
																																																																																																				   d2 = a[i].s2 - a[j].s2;
																																																																																																				   d3 = a[i].s3 - a[j].s3;
																																																																																																				   d = abs(d1 + d2 + d3);
																																																																																																				   d1 = abs((a[i].s1 - a[j].s1));
																																																																																																				   d2 = abs((a[i].s2 - a[j].s2));
																																																																																																				   d3 = abs((a[i].s3 - a[j].s3));
																																																																																																				   if (d1 <= 5 && d2 <= 5 && d3 <= 5 && d <= 10)
																																																																																																					   c++;
																																																																																																			   }
																																																																																																		   }
																																																																																																		   cout << c;*/
																																																																																																		   //#include<iostream>
																																																																																																		   //#include<cstdlib>
																																																																																																		   //#include<cstring>
																																																																																																		   //using namespace std;
																																																																																																		   //int main()
																																																																																																		   //{return 0;
																																																																																																		   //}
																																																																																																		   /*int l, n;
																																																																																																			   cin >> l >> n;
																																																																																																			   l++;
																																																																																																			   int x, y,s=0;
																																																																																																			   int* a = new int[l];
																																																																																																			   for (int i = 0;i < l;i++)
																																																																																																				   a[i] = 1;
																																																																																																			   for (int i = 0;i < n;i++) {
																																																																																																				   cin >> x >> y;
																																																																																																				   for (int j = x;j <= y;j++)
																																																																																																					   a[j] = 0;
																																																																																																			   }
																																																																																																			   for (int i = 0;i < l;i++)
																																																																																																				   s += a[i];
																																																																																																			   cout << s;*/
																																																																																																			   /*int a[1000];
																																																																																																				   int n;
																																																																																																				   cin >> n;
																																																																																																				   int i = 0;
																																																																																																				   while (n != 1) {
																																																																																																					   a[i] = n;
																																																																																																					   if (n % 2 == 0)
																																																																																																						   n /= 2;
																																																																																																					   else
																																																																																																						   n = n * 3 + 1;
																																																																																																					   i++;
																																																																																																				   }
																																																																																																				   a[i] = 1;
																																																																																																				   for (int j = i;j >= 0;j--)
																																																																																																					   cout << a[j] << ' ';*/
																																																																																																					   /*int a[200];
																																																																																																						   int c = 0;
																																																																																																						   for (int i = 0;;i++) {
																																																																																																							   cin >> a[i];
																																																																																																							   if (a[i] == 0) break;
																																																																																																							   c = i;
																																																																																																						   }
																																																																																																						   for (int j = c;j >=0;j--)
																																																																																																						   {
																																																																																																							   cout << a[j] << ' ';
																																																																																																						   }*/
																																																																																																						   /*string s;
																																																																																																							   cin >> s;
																																																																																																							   int l = s.size();

																																																																																																							   int i = 0;
																																																																																																							   while (--l >= 0) {
																																																																																																								   while (s[l] != ' ' || l != 0) {
																																																																																																									   i++;
																																																																																																									   l--;
																																																																																																								   }
																																																																																																								   while (s[l] == ' ' || l == 0) {
																																																																																																									   if (s[l + 1] == '0') {
																																																																																																										   i = 0;
																																																																																																										   break;
																																																																																																									   }
																																																																																																									   for (int j = 0;j <= i;j++) {
																																																																																																										   cout << s[l + j];
																																																																																																									   }
																																																																																																									   break;
																																																																																																								   }

																																																																																																							   }*/
																																																																																																							   //string s;
																																																																																																								   //cin >> s;
																																																																																																								   //int l = s.size();
																																																																																																								   //if (s[0] == 0)
																																																																																																								   //	cout << 0;
																																																																																																								   //else {
																																																																																																								   //	while (s[l - 1] == '0')l--;
																																																																																																								   //	//char a[l];
																																																																																																								   //	char* a = new char[l];
																																																																																																								   //	if (s[0] == '-') {
																																																																																																								   //		a[0] = '-';
																																																																																																								   //		for (int i = 1;i < l;i++) {
																																																																																																								   //			a[i] = s[l - i];
																																																																																																								   //		}
																																																																																																								   //	}
																																																																																																								   //	else
																																																																																																								   //		for (int i = 0;i < l;i++) {
																																																																																																								   //			a[i] = s[l - i - 1];
																																																																																																								   //		}
																																																																																																								   //	for (int i = 0;i < l;i++)
																																																																																																								   //		cout << a[i];
																																																																																																								   //}
																																																																																																							   /*double s;
																																																																																																								   cin >> s;
																																																																																																								   double d = 2;
																																																																																																								   double x = 0;
																																																																																																								   int i;
																																																																																																								   for (i = 1;x < s;i++) {
																																																																																																									   x += d;
																																																																																																									   d *= 0.98;
																																																																																																								   }
																																																																																																								   cout << i - 1;*/
																																																																																																								   /*int n;
																																																																																																									   cin >> n;
																																																																																																									   int prime[1001];
																																																																																																									   memset(prime, 0, sizeof(prime));
																																																																																																									   int i = 2;
																																																																																																									   int c = 0;
																																																																																																									   while (prime[1000] == 0) {
																																																																																																										   for (int j = 2;j < i;j++) {
																																																																																																											   if (i % j == 0) {
																																																																																																												   i++;j = 2;
																																																																																																											   }
																																																																																																										   }
																																																																																																										   prime[c++] = i++;
																																																																																																									   }
																																																																																																									   int s = 0;
																																																																																																									   int t = 0;
																																																																																																									   while (s <= n) {
																																																																																																										   s += prime[t++];
																																																																																																									   }
																																																																																																									   t--;
																																																																																																									   for (int i = 0;i < t;i++)
																																																																																																										   cout << prime[i] << endl;
																																																																																																									   cout << t;*/
																																																																																																									   /*int n;
																																																																																																										   int s = 0;
																																																																																																										   cin >> n;
																																																																																																										   for (int i = 1;i <= n;i++)
																																																																																																											   s += i;
																																																																																																										   cout << s;*/
																																																																																																										   /*int k;
																																																																																																											   int s = 0;
																																																																																																											   cin >> k;
																																																																																																											   int n;
																																																																																																											   for (n= 1;n * (n + 1) / 2 <= k;n++) {
																																																																																																												   for (int j = 1;j <= n;j++)
																																																																																																													   s += n;
																																																																																																											   }
																																																																																																											   n--;
																																																																																																											   int i = k - (n * (n + 1) / 2);
																																																																																																											   if (i > 0) {
																																																																																																												   for (int j = 1;j <= i;j++)
																																																																																																													   s += n + 1;
																																																																																																											   }
																																																																																																											   cout << s;*/
																																																																																																											   //#define N 1000
																																																																																																											   //void Read(int a[]) {
																																																																																																											   //	string s;
																																																																																																											   //	cin >> s;
																																																																																																											   //	a[0] = s.size();
																																																																																																											   //	for (int i = 1;i <= a[0];i++)
																																																																																																											   //		a[i] = s[a[0] - i] - '0';
																																																																																																											   //	return;
																																																																																																											   //}
																																																																																																											   ////高精度+高精度
																																																																																																											   //void Add(int a[], int b[]) {
																																																																																																											   //	if (a[0] < b[0]) a[0] = b[0];
																																																																																																											   //	for (int i = 1;i <= a[0];i++) {
																																																																																																											   //		a[i] += b[i];
																																																																																																											   //		a[i + 1] += a[i] / 10;
																																																																																																											   //		a[i] %= 10;
																																																																																																											   //		//if (a[i] > 9) a[i + 1]++, a[i] -= 10;
																																																																																																											   //	}
																																																																																																											   //	if (a[a[0] + 1] > 0) a[0]++;
																																																																																																											   //	return;
																																																																																																											   //}
																																																																																																											   //void Out(int a[]) {
																																																																																																											   //	while (a[0] > 1 && a[a[0]] == 0) a[0]--;//去掉数据多余的0
																																																																																																											   //	for (int i = a[0];i > 0;i--) cout << a[i];
																																																																																																											   //	return;
																																																																																																											   //}
																																																																																																											   ////高精度+单精度
																																																																																																											   //void Add(int a[], int b) {
																																																																																																											   //	a[1] += b;
																																																																																																											   //	int i = 1;
																																																																																																											   //	while (a[i] > 9) {
																																																																																																											   //		a[i + 1] += a[i] / 10;
																																																																																																											   //		a[i] %= 10;
																																																																																																											   //		i++;
																																																																																																											   //	}
																																																																																																											   //	if (i > a[0]) a[0]++;
																																																																																																											   //}
																																																																																																											   ////高精度*单精度
																																																																																																											   //void Mul(int a[], int b) {
																																																																																																											   //	for (int i = 1;i <= a[0];i++)
																																																																																																											   //		a[i]=a[i] * b;
																																																																																																											   //	for (int i = 1;i <= a[0];i++) {
																																																																																																											   //		a[i + 1] += a[i] / 10;
																																																																																																											   //		a[i] %= 10;
																																																																																																											   //	}
																																																																																																											   //	while (a[a[0] + 1] > 0) {
																																																																																																											   //		a[0]++;
																																																																																																											   //		a[a[0] + 1] = a[a[0]] / 10;
																																																																																																											   //		a[a[0]] %= 10;
																																																																																																											   //	}
																																																																																																											   //	return;
																																																																																																											   //}
																																																																																																											   ////高精度*高精度
																																																																																																											   //void Mul(int a[],int b[],int c[]) {
																																																																																																											   //	int i, j;
																																																																																																											   //	for (i = 1;i <= a[0];i++)
																																																																																																											   //		for (j = 1;j <= b[0];j++)
																																																																																																											   //			c[i + j - 1] += a[i] * b[j];
																																																																																																											   //	c[0] = a[0] + b[0];
																																																																																																											   //	for (i = 1;i <= c[0];i++) {
																																																																																																											   //		c[i + 1] += c[i] / 10;
																																																																																																											   //		c[i] %= 10;
																																																																																																											   //	}
																																																																																																											   //	while (c[0] > 1 && c[c[0]] == 0)  c[0]--;//c[0]>1考虑了和0相乘的情况
																																																																																																											   //	return;
																																																																																																											   //}
																																																																																																											   ////高精度减法a>b
																																																																																																											   //void Minus(int a[], int b[]) {
																																																																																																											   //	for (int i = 1;i <= a[0];i++) {
																																																																																																											   //		if (a[i] < b[i]) {
																																																																																																											   //			a[i + 1]--;a[i] += 10;
																																																																																																											   //		}
																																																																																																											   //		a[i] -= b[i];
																																																																																																											   //	}
																																																																																																											   //	while (a[0] > 0 && a[a[0]] == 0)a[0]--;
																																																																																																											   //	return;
																																																																																																											   //}
																																																																																																											   ////高精度/单精度
																																																																																																											   //void Div(int a[], int b, int c[]) {
																																																																																																											   //	c[0] = a[0];
																																																																																																											   //	int y=0;//存储余数;
																																																																																																											   //	for (int i = a[0];i > 0;i--) {
																																																																																																											   //		y = y * 10 + a[i];
																																																																																																											   //		c[i] = y / b;
																																																																																																											   //		y %= b;
																																																																																																											   //	}
																																																																																																											   //	while (c[0] > 1 && c[c[0]] == 0) c[0]--;
																																																																																																											   //	return;
																																																																																																											   //}
																																																																																																											   ////高精度/高精度
																																																																																																											   //int Comp(int a[],int b[]) {
																																																																																																											   //	int i;
																																																																																																											   //	if (a[0] > b[0])return 1;
																																																																																																											   //	if (a[0] < b[0])return -1;
																																																																																																											   //	for (i = a[0];i > 0;i--) {
																																																																																																											   //		if (a[i] > b[i])return 1;
																																																																																																											   //		if (a[i] < b[i])return -1;
																																																																																																											   //	}
																																																																																																											   //	return 0;
																																																																																																											   //}
																																																																																																											   //void numcopy(int b[], int t[], int i) {
																																																																																																											   //	t[0] = b[0] + i - 1;//t的位数
																																																																																																											   //	for (int j = b[0];j > 0;j--)
																																																																																																											   //		t[i + j - 1] = b[j];
																																																																																																											   //}
																																																																																																											   //void Div(int a[], int b[], int c[]) {
																																																																																																											   //	int i, j, t[N];
																																																																																																											   //	c[0] = a[0] - b[0] + 1;
																																																																																																											   //	for (i = c[0];i > 0;i--) {
																																																																																																											   //		memset(t, 0, sizeof(t));
																																																																																																											   //		numcopy(b, t, i);//在b后面添加0，为方便处理用t替代b，每次循环的时候0的个数会减少1
																																																																																																											   //		while (Comp(a, t) >= 0) {//a比t大的时候就统计a中包含了多少个t(个数<10)
																																																																																																											   //			c[i]++;
																																																																																																											   //			Minus(a, t);
																																																																																																											   //		}
																																																																																																											   //	}
																																																																																																											   //	while (c[0] > 0 && c[c[0]] == 0)c[0]--;
																																																																																																											   //}
																																																																																																											   //int change(int n,int b[]) {
																																																																																																											   //	int i = 1;
																																																																																																											   //	for (b[0] = 1;n > 0;i++) {
																																																																																																											   //		b[i] = n % 10;
																																																																																																											   //		n /= 10;
																																																																																																											   //	}
																																																																																																											   //	while (b[0] > 0 && b[b[0]] == 0)b[0]--;
																																																																																																											   //	return 0;
																																																																																																											   //}
																																																																																																											   //memset(a, 0, sizeof(a));
																																																																																																												   //memset(b, 0, sizeof(b));
																																																																																																												   //b[0] = 1;
																																																																																																												   // 	   int a[10000], b[10000];
																																																																																																												   //int n;
																																																																																																												   //cin >> n;
																																																																																																												   //a[0] = 1;a[1] = 1;
																																																																																																												   ////Mul(a, n);
																																																																																																												   ////Add(a, n);
																																																																																																												   ////Out(a);
																																																																																																												   //for (int i = 1;i <= n;i++) {
																																																																																																												   //	memset(a, 0, sizeof(a));
																																																																																																												   //	a[0] = 1;a[1] = 1;
																																																																																																												   //	for (int j = 1;j <= i;j++) {
																																																																																																												   //		Mul(a, j);
																																																																																																												   //	}
																																																																																																												   //	Add(b, a);
																																																																																																												   //}
																																																																																																												   //Out(b);
																																																																																																											   /*int a[5] = { 2,4,1,3,5 };
																																																																																																												   radixsort(a, 5);
																																																																																																												   for (int i = 0;i < 5;i++)
																																																																																																													   cout << a[i] << ' ';*/
																																																																																																													   //void countingsort(int arr[], int n)
																																																																																																													   //{
																																																																																																													   //	int* sorted = new int[n];
																																																																																																													   //	int max = arr[0];
																																																																																																													   //	for (int i = 1;i < n;i++)
																																																																																																													   //	{
																																																																																																													   //		if (arr[i] > max)
																																																																																																													   //			max = arr[i];
																																																																																																													   //	}
																																																																																																													   //	int* count = new int[max + 1];//max+1为最大数组下标，为arr[](max)
																																																																																																													   //	for (int i = 0;i < max + 1;i++)
																																																																																																													   //	{
																																																																																																													   //		count[i] = 0;
																																																																																																													   //	}
																																																																																																													   //	//记录频次
																																																																																																													   //	for (int i = 0;i < n;i++)
																																																																																																													   //		count[arr[i]]++;
																																																																																																													   //	//累加计数
																																																																																																													   //	for (int i = 1;i <= max;i++)
																																																																																																													   //	{
																																																																																																													   //		count[i] += count[i - 1];
																																																																																																													   //	}
																																																																																																													   //	//确认最终位置
																																																																																																													   //	for (int i = n - 1;i >= 0;i--)
																																																																																																													   //	{
																																																																																																													   //		sorted[count[arr[i]] - 1] = arr[i];//数值-->数组下标-1
																																																																																																													   //		count[arr[i]]--;
																																																																																																													   //	}
																																																																																																													   //	for (int i = 0;i < n;i++)
																																																																																																													   //		arr[i] = sorted[i];
																																																																																																													   //	delete[]sorted;
																																																																																																													   //	delete[]count;
																																																																																																													   //}
																																																																																																													   //int maxbit(int arr[], int n)//找最大位数
																																																																																																													   //{
																																																																																																													   //	int max = arr[0];
																																																																																																													   //	for (int i = 1;i < n;i++)
																																																																																																													   //	{
																																																																																																													   //		if (max < arr[i])
																																																																																																													   //			max = arr[i];
																																																																																																													   //	}
																																																																																																													   //	int d = 1;
																																																																																																													   //	int p = 10;
																																																																																																													   //	while (max >= p)
																																																																																																													   //	{
																																																																																																													   //		max /= 10;
																																																																																																													   //		d++;
																																																																																																													   //	}
																																																																																																													   //	return d;
																																																																																																													   //}
																																																																																																													   //void radixsort(int arr[], int n)
																																																																																																													   //{
																																																																																																													   //	int d = maxbit(arr, n);
																																																																																																													   //	int* temp = new int[n];
																																																																																																													   //	int* count = new int[10];
																																																																																																													   //	int i, j, k;
																																																																																																													   //	int radix = 1;
																																																																																																													   //	for (i = 1;i <= d;i++)
																																																																																																													   //	{//每次对位数的值进行计数排序
																																																																																																													   //		for (j = 0;j < 10;j++)
																																																																																																													   //			count[j] = 0;//每次都清空计数器
																																																																																																													   //		for (j = 0;j < n;j++)
																																																																																																													   //		{
																																																																																																													   //			k = (arr[j] / radix) % 10;
																																																																																																													   //			count[k]++;
																																																																																																													   //		}
																																																																																																													   //		for (j = 1;j < 10;j++)
																																																																																																													   //			count[j] += count[j - 1];
																																																																																																													   //		for (j = n - 1;j >= 0;j--)
																																																																																																													   //		{
																																																																																																													   //			k = (arr[j] / radix) % 10;
																																																																																																													   //			temp[count[k] - 1] = arr[j];
																																																																																																													   //			count[k]--;
																																																																																																													   //		}
																																																																																																													   //		for (j = 0;j < n;j++)
																																																																																																													   //			arr[j] = temp[j];
																																																																																																													   //		radix *= 10;
																																																																																																													   //	}
																																																																																																													   //	delete[]temp;
																																																																																																													   //	delete[]count;
																																																																																																													   //}









																																																																																																													   /*int a, b;
																																																																																																														   scanf("%d+%d", &a, &b);
																																																																																																														   cout << a << b;*/
																																																																																																														   //int a[1003],b[1004];
																																																																																																														   //void quicksort(int a[], int l, int r)//从大到小排序
																																																																																																														   //{
																																																																																																														   //	if (l >= r)
																																																																																																														   //		return;
																																																																																																														   //	int i, j,base, temp;
																																																																																																														   //	i = l, j = r;base = a[l];
																																																																																																														   //	while (i < j)
																																																																																																														   //	{
																																																																																																														   //		while (a[j] <= base && i < j)//从小到大只需将<=改为>=
																																																																																																														   //			j--;
																																																																																																														   //		while (a[i] >= base && i < j)//从小到大只需将>=改为<=
																																																																																																														   //			i++;
																																																																																																														   //		if (i < j)
																																																																																																														   //		{
																																																																																																														   //			temp = a[i];
																																																																																																														   //			a[i] = a[j];
																																																																																																														   //			a[j] = temp;
																																																																																																														   //		}
																																																																																																														   //	}
																																																																																																														   //	a[l] = a[i];//交换基准数和俩子数组交接处的数
																																																																																																														   //	a[i] = base;//此时a[i]是中间值
																																																																																																														   //	quicksort(a, l, i - 1);
																																																																																																														   //	quicksort(a, i + 1, r);
																																																																																																														   //}
																																																																																																														   /*int n;
																																																																																																															   cin >> n;
																																																																																																															   for (int i = 0;i < n;i++)
																																																																																																																   cin >> a[i];
																																																																																																															   for (int i = 0;i < n - 1;i++)
																																																																																																																   b[i] = a[i + 1] - a[i];
																																																																																																															   for (int i = 0;i < n - 1;i++)
																																																																																																																   if (b[i] < 0)
																																																																																																																	   b[i] = 0 - b[i];
																																																																																																															   quicksort(b, 0, n - 2);
																																																																																																															   if (b[0] > n)
																																																																																																																   cout << "Not jolly";
																																																																																																															   else
																																																																																																																   cout << "Jolly";*/
																																																																																																																   //#include<iostream>
																																																																																																																   //using namespace std;
																																																																																																																   //int a[100001], b[100001], c[100001];
																																																																																																																   //void msort(int l, int r)
																																																																																																																   //{
																																																																																																																   //	int mid = (l + r) / 2;
																																																																																																																   //	return;
																																																																																																																   //	msort(l, mid);msort(mid + 1, r);
																																																																																																																   //	int left = l, right = mid + 1, c = 0;
																																																																																																																   //	while (left <= mid && right < r)
																																																																																																																   //	{
																																																																																																																   //		if (a[left] <= a[right])
																																																																																																																   //			b[c++] = a[left++];
																																																																																																																   //		else
																																																																																																																   //			b[c++] = a[right++];
																																																																																																																   //	}
																																																																																																																   //	while(left<=mid)
																																																																																																																   //		b[c++] = a[left++];
																																																																																																																   //	while(right<r)
																																																																																																																   //		b[c++] = a[right++];
																																																																																																																   //	for (int i = 0;i < r;i++)
																																																																																																																   //		a[i] = b[i];
																																																																																																																   //	return;
																																																																																																																   //}
																																																																																																																   //
																																																																																																																   //int main()
																																																																																																																   //{
																																																																																																																   //	int n,k;
																																																																																																																   //	cin >> n>>k;
																																																																																																																   //	for (int i = 0;i < n;i++)
																																																																																																																   //		cin >> a[i];
																																																																																																																   //	for (int i = 0;i < n ;i++)
																																																																																																																   //		cout << a[i] << ' ';
																																																																																																																   //	cout << endl;
																																																																																																																   //	msort(0, n);
																																																																																																																   //	for (int i = 0;i < n ;i++)
																																																																																																																   //		cout << a[i] << ' ';
																																																																																																																   //	cout << endl;
																																																																																																																   //	for (int i = 0;i < n - 1;i++)
																																																																																																																   //		c[i] = a[i + 1] - a[i];
																																																																																																																   //	for (int i = 0;i < n - 1;i++)
																																																																																																																   //		a[i] = c[i];
																																																																																																																   //	msort(0, n - 1);
																																																																																																																   //	int ans = 0;
																																																																																																																   //	for (int i = 0;i < k;i++)
																																																																																																																   //		ans += a[i];
																																																																																																																   //	cout << ans;
																																																																																																																   //	return 0;
																																																																																																																   //}
																																																																																																																   /*int a[5] = { 2,4,3,1,5 };
																																																																																																																	   shellsort(a, 5);
																																																																																																																	   for (int i = 0;i < 5;i++)
																																																																																																																		   cout << a[i] << ' ';
																																																																																																																   */
																																																																																																																   //void shellsort(int arr[], int n)
																																																																																																																   //{
																																																																																																																   //	int i, j, gap;
																																																																																																																   //	for (gap = n / 2;gap > 0;gap /= 2)//步长gap
																																																																																																																   //	{
																																																																																																																   //		for (i = 0;i < gap;i++)//步长内
																																																																																																																   //		{
																																																																																																																   //			for (j = i + gap;j < n;j += gap)
																																																																																																																   //			{
																																																																																																																   //				if (arr[j] < arr[j - gap])
																																																																																																																   //				{
																																																																																																																   //					int temp = arr[j];
																																																																																																																   //					int k = j - gap;
																																																																																																																   //					while (k >= 0 && arr[k] > temp)//往前移
																																																																																																																   //					{
																																																																																																																   //						arr[k + gap] = arr[k];
																																																																																																																   //						k -= gap;
																																																																																																																   //					}
																																																																																																																   //					arr[k + gap] = temp;
																																																																																																																   //				}
																																																																																																																   //			}
																																																																																																																   //
																																																																																																																   //		}
																																																																																																																   //	}
																																																																																																																   //}
																																																																																																																   //#include<iostream>
																																																																																																																   //using namespace std;
																																																																																																																   //int a[100001], b[100001], c[100001];
																																																																																																																   //void msort(int l, int r)
																																																																																																																   //{
																																																																																																																   //	if (l = r) return;
																																																																																																																   //	int mid = (l + r) / 2;
																																																																																																																   //	msort(l, mid);msort(mid + 1, r);
																																																																																																																   //	int left = l, right = mid + 1, c = 0;
																																																																																																																   //	while (left <= mid && right < r)
																																																																																																																   //	{
																																																																																																																   //		if (a[left] <= a[right])
																																																																																																																   //			b[c++] = a[left++];
																																																																																																																   //		else
																																																																																																																   //			b[c++] = a[right++];
																																																																																																																   //	}
																																																																																																																   //	while(left<=mid)
																																																																																																																   //		b[c++] = a[left++];
																																																																																																																   //	while(right<r)
																																																																																																																   //		b[c++] = a[right++];
																																																																																																																   //	for (int i = 0;i < r;i++)
																																																																																																																   //		a[i] = b[i];
																																																																																																																   //	return;
																																																																																																																   //}
																																																																																																																   //
																																																																																																																   //int main()
																																																																																																																   //{
																																																																																																																   //	int n,k;
																																																																																																																   //	cin >> n>>k;
																																																																																																																   //	for (int i = 1;i <= n;i++)
																																																																																																																   //		cin >> a[i];
																																																																																																																   //	for (int i = 1;i <= n ;i++)
																																																																																																																   //		cout << a[i] << ' ';
																																																																																																																   //	cout << endl;
																																																																																																																   //	msort(0, n);
																																																																																																																   //	for (int i = 0;i < n ;i++)
																																																																																																																   //		cout << a[i] << ' ';
																																																																																																																   //	cout << endl;
																																																																																																																   //	for (int i = 0;i < n - 1;i++)
																																																																																																																   //		c[i] = a[i + 1] - a[i];
																																																																																																																   //	for (int i = 0;i < n - 1;i++)
																																																																																																																   //		a[i] = c[i];
																																																																																																																   //	msort(0, n - 1);
																																																																																																																   //	int ans = 0;
																																																																																																																   //	for (int i = 0;i < k;i++)
																																																																																																																   //		ans += a[i];
																																																																																																																   //	cout << ans;
																																																																																																																   //	return 0;
																																																																																																																   //}
																																																																																																																   //void merge_sort(int arr[], int len)
																																																																																																																   //{
																																																																																																																   //    int ans[10];
																																																																																																																   //    for (int seg = 1; seg < len; seg += seg)
																																																																																																																   //    {
																																																																																																																   //        for (int beg = 0; beg < len; beg += seg + seg)
																																																																																																																   //        {
																																																																																																																   //            int low = beg, mid = std::min(beg + seg, len), high = std::min(beg + seg + seg, len);
																																																																																																																   //            int i = low, j = mid, k = low;
																																																																																																																   //            while (i < mid && j < high)
																																																																																																																   //                ans[k++] = arr[i] > arr[j] ? arr[j++] : arr[i++];
																																																																																																																   //            while (i < mid)
																																																																																																																   //                ans[k++] = arr[i++];
																																																																																																																   //            while (j < high)
																																																																																																																   //                ans[k++] = arr[j++];
																																																																																																																   //            for (k = beg; k < high; k++)
																																																																																																																   //                arr[k] = ans[k];
																																																																																																																   //        }
																																																																																																																   //    }
																																																																																																																   //}
																																																																																																																   /*int arr[10] = { 2,5,4,8,9,7,1,6,0,3 };
																																																																																																																	   merge_sort(arr, 10);
																																																																																																																	   for (int i = 0;i < 10;i++)
																																																																																																																		   cout << arr[i]<<' ';*/

																																																																																																																		   /*int n, k;
																																																																																																																			   cin >> n;
																																																																																																																			   int m[n];
																																																																																																																			   for (int i = 0;i < n;i++)
																																																																																																																				   cin >> m[i];
																																																																																																																			   merge_sort(m, n);
																																																																																																																			   int d[n - 1];
																																																																																																																			   for (int i = 0;i < n - 1;i++)
																																																																																																																				   d[i] = m[i + 1] - m[i];
																																																																																																																			   merge_sort(d, n - 1);
																																																																																																																			   int s = 0;
																																																																																																																			   for (int i = 0;i < k;i++)
																																																																																																																				   s += d[i];
																																																																																																																			   cout << s;
																																																																																																																			  */


																																																																																																																			  /*int arr[4] = { 20,3,6,10 };
																																																																																																																				  merge_sort_it(arr, 4);
																																																																																																																				  for (int i = 0;i < 4;i++)
																																																																																																																					  cout << arr[i] << ' ';*/
																																																																																																																					  //void merge_sort_it(int arr[], int len)
																																																																																																																					  //{
																																																																																																																					  //    int ans[4];
																																																																																																																					  //    for (int seg = 1; seg < len; seg += seg) 
																																																																																																																					  //    {
																																																																																																																					  //        for (int beg = 0; beg < len; beg += seg + seg)
																																																																																																																					  //        {
																																																																																																																					  //            int low = beg, mid = std::min(beg + seg, len), high = std::min(beg + seg + seg, len);
																																																																																																																					  //            int i = low, j = mid, k = low;
																																																																																																																					  //            while (i < mid && j < high) 
																																																																																																																					  //                ans[k++] = arr[i] > arr[j] ? arr[j++] : arr[i++];
																																																																																																																					  //            while (i < mid)
																																																																																																																					  //                ans[k++] = arr[i++];
																																																																																																																					  //            while (j < high)
																																																																																																																					  //                ans[k++] = arr[j++];
																																																																																																																					  //            for (k = beg; k < high; k++) 
																																																																																																																					  //                arr[k] = ans[k];
																																																																																																																					  //        }
																																																																																																																					  //    }
																																																																																																																					  //}
																																																																																																																					  //void merge_sort(int arr[], int len)
																																																																																																																					  //{
																																																																																																																					  //    int* a = arr;
																																																																																																																					  //    int* b = new int[len];
																																																																																																																					  //    for (int s = 1;s < len;s *=2)
																																																																																																																					  //    {
																																																																																																																					  //        for (int start = 0;start < len;start += s *2)
																																																																																																																					  //        {
																																																																																																																					  //            int low = start, mid = min(start + s, len), high = min(start + s + s, len);
																																																																																																																					  //            int k = low;//偏移位置
																																																																																																																					  //            int start1 = low, end1 = mid;//左边部分
																																																																																																																					  //            int start2 = mid, end2 = high;//右边部分
																																																																																																																					  //            while (start < end1 && start2 < end2)
																																																																																																																					  //            {
																																																																																																																					  //                if (a[start1] < a[start2])
																																																																																																																					  //                    b[k++] = a[start1++];
																																																																																																																					  //                else
																																																																																																																					  //                    b[k++] = a[start2++];
																																																																																																																					  //                //b[k++] = a[start1] < a[start2] ? a[start1] : a[start2];
																																																																																																																					  //            }
																																																																																																																					  //            while (start1 < end1)
																																																																																																																					  //                b[k++] = a[start1++];
																																																																																																																					  //            while (start2 < end2)
																																																																																																																					  //                b[k++] = a[start2++];
																																																																																																																					  //        }
																																																																																																																					  //        int* temp = a;
																																																																																																																					  //        a = b;
																																																																																																																					  //        b = temp;
																																																																																																																					  //    }
																																																																																																																					  //        if (a != arr)
																																																																																																																					  //        {
																																																																																																																					  //            int i;
																																																																																																																					  //            for (i = 0;i < len;i++)
																																																																																																																					  //                b[i] = a[i];
																																																																																																																					  //            b = a;
																																																																																																																					  //       }
																																																																																																																					  //        delete[]b;
																																																																																																																					  //}
																																																																																																																					  //
																																																																																																																					  //
																																																																																																																					  //int main()
																																																																																																																					  //{
																																																																																																																					  //    int arr[7] = { 3,2,1,5,4,8,6};
																																																																																																																					  //    merge_sort(arr, 7);
																																																																																																																					  //    for (int i = 0;i < 7;i++)
																																																																																																																					  //    {
																																																																																																																					  //        cout << arr[i] << ' ';
																																																																																																																					  //    }
																																																																																																																					  // 
																																																																																																																					  //    return 0;
																																																																																																																					  //}
																																																																																																																					  /*int n;
																																																																																																																						  cin >> n;
																																																																																																																						  string s[n];
																																																																																																																						  int y[n], m[n], d[n];
																																																																																																																						  for (int i = 0;i < n;i++)
																																																																																																																							  cin >> s[i] >> y[i] >> m[i] >> d[i];
																																																																																																																						  for (int i = 0;i < n;i++)
																																																																																																																						  {
																																																																																																																							  for (int j = i + 1;j < n;j++)
																																																																																																																							  {
																																																																																																																								  if ((y[i] > y[j] )|| (y[i] == y[j] && m[i] > m[j] )||( y[i] == y[j] && m[i] == m[j] && d[i] >= d[j]))
																																																																																																																								  {
																																																																																																																									  swap(s[i], s[j]);
																																																																																																																									  swap(y[i], y[j]);
																																																																																																																									  swap(m[i], m[j]);
																																																																																																																									  swap(d[i], d[j]);
																																																																																																																								  }
																																																																																																																							  }
																																																																																																																						  }
																																																																																																																						  for (int i = 0;i < n;i++)
																																																																																																																							  cout << s[i] << endl;*/
																																																																																																																							  ////// int n ;
																																																																																																																								 //// //cin >> n;
																																																																																																																								 //// string s[n];
																																																																																																																								 //// int y[n], m[n], d[n];
																																																																																																																								 //// for (int i = 0;i < n;i++)
																																																																																																																								 //// {
																																																																																																																								 ////     cin >> s[i] >> y[i] >> m[i] >> d[i];
																																																																																																																								 //// }
																																																																																																																								 //// for (int i = 0;i < n - 1;i++)
																																																																																																																								 //// {
																																																																																																																								 ////     int min=i;
																																																																																																																								 ////     for (int j = i ;j < n - 1;j++)
																																																																																																																								 ////     {
																																																																																																																								 ////         if (y[min] > y[j])
																																																																																																																								 ////             min = j;
																																																																																																																								 ////     }
																																																																																																																								 ////     int t = y[i];string k = s[i];
																																																																																																																								 ////     y[i] = y[min];s[i] = s[min];
																																																																																																																								 ////     y[min] = t;s[min] = k;
																																																																																																																								 //// }
																																																																																																																								 //// for (int i = 0;i < n - 1;i++)
																																																																																																																								 //// {
																																																																																																																								 ////     int min = i;
																																																																																																																								 ////     for (int j = i ;j < n - 1;j++)
																																																																																																																								 ////     {
																																																																																																																								 ////         if (y[i] == y[j])
																																																																																																																								 ////             min=j;
																																																																																																																								 ////     }
																																																																																																																								 ////     for (int k = i;k < min;k++)
																																																																																																																								 ////     {
																																																																																																																								 ////         int t = k;
																																																																																																																								 ////         for (int d = k;d < min;d++)
																																																																																																																								 ////         {
																																																																																																																								 ////             if (m[k] > m[d])
																																																																																																																								 ////                 t = d;
																																																																																																																								 ////         }
																																																																																																																								 ////         int p = m[k];string p1 = s[k];
																																																																																																																								 ////         m[k] = m[t];s[k] = s[t];
																																																																																																																								 ////         m[t] = p;s[t] = p1;
																																																																																																																								 ////     }
																																																																																																																								 //// }
																																																																																																																								 //// for (int i = 0;i < n - 1;i++)
																																																																																																																								 //// {
																																																																																																																								 ////     int min = i;
																																																																																																																								 ////     for (int j = i ;j < n - 1;j++)
																																																																																																																								 ////     {
																																																																																																																								 ////         if (m[i] == m[j])
																																																																																																																								 ////             min = j;
																																																																																																																								 ////     }
																																																																																																																								 ////     for (int k = i;k < min;k++)
																																																																																																																								 ////     {
																																																																																																																								 ////         int t = k;
																																																																																																																								 ////         for (int d1 = k;d1 < min;d1++)
																																																																																																																								 ////         {
																																																																																																																								 ////             if (d[k] > d[d1])
																																																																																																																								 ////                 t = d1;
																																																																																																																								 ////         }
																																																																																																																								 ////         int p = m[k];string p1 = s[k];
																																																																																																																								 ////         m[k] = m[t];s[k] = s[t];
																																																																																																																								 ////         m[t] = p;s[t] = p1;
																																																																																																																								 ////     }
																																																																																																																								 //// }
																																																																																																																								 //// for (int i = 0;i < n;i++)
																																																																																																																								 ////     cout << s[i] << endl;
																																																																																																																							  /*else if (y[min] == y[j])
																																																																																																																										  {
																																																																																																																											  for (int i = 0;i < n - 1;i++)
																																																																																																																											  {

																																																																																																																											  }
																																																																																																																										  }*/
																																																																																																																										  /*int min = i;
																																																																																																																															  for (int j = i + 1;j < n - 1;j++)
																																																																																																																															  {
																																																																																																																																  if (m[min] > m[j])
																																																																																																																																	  min = j;
																																																																																																																																  else if (m[min] == m[j])
																																																																																																																																  {
																																																																																																																																	  for (int i = 0;i < n - 1;i++)
																																																																																																																																	  {
																																																																																																																																		  int min = i;
																																																																																																																																		  for (int j = i + 1;j < n - 1;j++)
																																																																																																																																		  {
																																																																																																																																			  if (d[min] > d[j])
																																																																																																																																				  min = j;
																																																																																																																																		  }
																																																																																																																																		  int t = d[i];string k = s[i];
																																																																																																																																		  d[i] = d[min];s[i] = s[min];
																																																																																																																																		  d[min] = t;s[min] = k;
																																																																																																																																	  }
																																																																																																																																  }
																																																																																																																															  }
																																																																																																																															  int t = m[i];string k = s[i];
																																																																																																																															  m[i] = m[min];s[i] = s[min];
																																																																																																																															  m[min] = t;s[min] = k;*/
																																																																																																																															  //void P(int a[], int n)
																																																																																																																															  //{
																																																																																																																															  //	for (int i = 0; i < n; i++)
																																																																																																																															  //		cout << a[i] << " ";
																																																																																																																															  //	cout << endl;
																																																																																																																															  //}
																																																																																																																															  //
																																																																																																																															  //int Partition(int arr[], int l, int r)
																																																																																																																															  //{
																																																																																																																															  //	int i = l;
																																																																																																																															  //	int j = r;
																																																																																																																															  //	int x = arr[l];
																																																																																																																															  //	while (i < j)
																																																																																																																															  //	{
																																																																																																																															  //		while (i<j && arr[j]>x)
																																																																																																																															  //			j--;
																																																																																																																															  //		if (i < j)
																																																																																																																															  //			arr[i++] = arr[j];
																																																																																																																															  //		while (i < j && arr[i] < x)
																																																																																																																															  //			i++;
																																																																																																																															  //		if (i < j)
																																																																																																																															  //			arr[j--] = arr[i];
																																																																																																																															  //	}
																																																																																																																															  //	arr[i] = x;
																																																																																																																															  //	return i;
																																																																																																																															  //}
																																																																																																																															  //void QuickSort(int arr[], int l, int r)
																																																																																																																															  //{
																																																																																																																															  //	if (l >= r)
																																																																																																																															  //		return;
																																																																																																																															  //	int i = Partition(arr, l, r);
																																																																																																																															  //	QuickSort(arr, l, i - 1);
																																																																																																																															  //	QuickSort(arr, i+1, r);
																																																																																																																															  //}
																																																																																																																															  //
																																																																																																																															  //int main()
																																																																																																																															  //{
																																																																																																																															  //	
																																																																																																																															  //
																																																																																																																															  //	int a[] = { 72,6,57,88,60,42,83,73,48,85 };
																																																																																																																															  //	//int a[]= {10,9,8,7,6,5,4,3,2,1};
																																																																																																																															  //	P(a, 10);
																																																																																																																															  //	QuickSort(a, 0, 9);//注意最后一个参数是n-1
																																																																																																																															  //	P(a, 10);
																																																																																																																															  //	return 0;
																																																																																																																															  /*int n;
																																																																																																																																  cin >> n;
																																																																																																																																  int m[n];
																																																																																																																																  int s[n] = { 0 };
																																																																																																																																  for (int i = 0;i < n;i++)
																																																																																																																																  {
																																																																																																																																	  cin >> m[i];
																																																																																																																																  }
																																																																																																																																  for (int i = 0;i < n;i++)
																																																																																																																																  {
																																																																																																																																	  for (int j = 0;j < i;j++)
																																																																																																																																	  {
																																																																																																																																		  if (m[i] > m[j])
																																																																																																																																			  s[i]++;
																																																																																																																																	  }
																																																																																																																																  }
																																																																																																																																  for (int i = 0;i < n;i++)
																																																																																																																																  {
																																																																																																																																	  cout<<s[i]<<' ';
																																																																																																																																  }*/
																																																																																																																																  //int BubbleSort(int arr[], int n)
																																																																																																																																  //{
																																																																																																																																  //	int c=0;
																																																																																																																																  //	//每次把最大值放在最后边
																																																																																																																																  //	for (int i = 0;i < n-1;i++)
																																																																																																																																  //	{
																																																																																																																																  //		for (int j = 0;j < n - i - 1;j++)
																																																																																																																																  //		{
																																																																																																																																  //			if (arr[j] > arr[j + 1])
																																																																																																																																  //			{
																																																																																																																																  //				int temp = arr[j];
																																																																																																																																  //				arr[j] = arr[j + 1];
																																																																																																																																  //				arr[j + 1] = temp;
																																																																																																																																  //				c++;
																																																																																																																																  //			}
																																																																																																																																  //
																																																																																																																																  //		}
																																																																																																																																  //	}
																																																																																																																																  //	return c;
																																																																																																																																  //}
																																																																																																																																  /*int n;
																																																																																																																																	  cin >> n;
																																																																																																																																	  int arr[4];
																																																																																																																																	  for (int i = 0;i < n;i++)
																																																																																																																																		  cin >> arr[i];
																																																																																																																																	  cout<<BubbleSort(arr, n);
																																																																																																																																  */
																																																																																																																																  /*int n,m,min;
																																																																																																																																	  cin >> n;
																																																																																																																																	  cin >> m;
																																																																																																																																	  min = m;
																																																																																																																																	  for (int i = 1;i < n;i++)
																																																																																																																																	  {
																																																																																																																																		  cin >> m;
																																																																																																																																		  if (min > m) min = m;
																																																																																																																																	  }
																																																																																																																																	  cout << min;*/
																																																																																																																																	  /*int a, b, c,t;
																																																																																																																																		  cin >> a >> b >> c;
																																																																																																																																		  if (a > b)
																																																																																																																																		  {
																																																																																																																																			  t = a;a = b;b = t;
																																																																																																																																		  }
																																																																																																																																		  if (c > a && c < b)
																																																																																																																																		  {
																																																																																																																																			  t = c;c = b;b = t;
																																																																																																																																		  }
																																																																																																																																		  else if (a > c)
																																																																																																																																		  {
																																																																																																																																			  t = c;c = b;b = a;a = t;
																																																																																																																																		  }
																																																																																																																																		  char x, y, z;
																																																																																																																																		  cin >> x >> y >> z;
																																																																																																																																		  switch (x)
																																																																																																																																		  {
																																																																																																																																		  case 'A':cout << a;break;
																																																																																																																																		  case 'B':cout << b;break;
																																																																																																																																		  case 'C':cout << c;break;
																																																																																																																																		  }
																																																																																																																																		  cout << ' ';
																																																																																																																																		  switch (y)
																																																																																																																																		  {
																																																																																																																																		  case 'A':cout << a;break;
																																																																																																																																		  case 'B':cout << b;break;
																																																																																																																																		  case 'C':cout << c;break;
																																																																																																																																		  }
																																																																																																																																		  cout << ' ';
																																																																																																																																		  switch (z)
																																																																																																																																		  {
																																																																																																																																		  case 'A':cout << a;break;
																																																																																																																																		  case 'B':cout << b;break;
																																																																																																																																		  case 'C':cout << c;break;
																																																																																																																																		  }*/
																																																																																																																																		  /*int a, b, c;
																																																																																																																																			  cin >> a >> b >> c;
																																																																																																																																			  if (a > c)swap(a, c);
																																																																																																																																			  if (b > c)swap(b, c);
																																																																																																																																			  if (a > c)swap(a, c);
																																																																																																																																			  if (b > c)swap(b, c);
																																																																																																																																			  if (a + b <= c) { cout << "Not triangle";return 0; }
																																																																																																																																			  if (pow(a, 2) + pow(b, 2) == pow(c, 2))cout << "Right triangle" << endl;
																																																																																																																																			  if (pow(a, 2) + pow(b, 2) > pow(c, 2))cout << "Acute triangle" << endl;
																																																																																																																																			  if (pow(a, 2) + pow(b, 2) < pow(c, 2))cout << "Obtuse triangle" << endl;
																																																																																																																																			  if (a == b || a == c || b == c)cout << "Isosceles triangle" << endl;
																																																																																																																																			  if (a == b && b == c)cout << "Equilateral triangle" << endl;*/
																																																																																																																																			  /*int n[10];
																																																																																																																																				  int m, c=0;
																																																																																																																																				  for (int i = 0;i < 10;i++)
																																																																																																																																					  cin >> n[i];
																																																																																																																																				  cin >> m;
																																																																																																																																				  m += 30;
																																																																																																																																				  for (int i = 0;i < 10;i++)
																																																																																																																																				  {
																																																																																																																																					  if (m >= n[i]) c++;
																																																																																																																																				  }
																																																																																																																																				  cout << c;
																																																																																																																																				  */
																																																																																																																																				  /*int a, b, c, t;
																																																																																																																																					  cin >> a >> b >> c;
																																																																																																																																					  if (a > b)
																																																																																																																																					  {
																																																																																																																																						  t = a;
																																																																																																																																						  a = b;
																																																																																																																																						  b = t;
																																																																																																																																					  }
																																																																																																																																					  if (a > c)
																																																																																																																																					  {
																																																																																																																																						  t = c;
																																																																																																																																						  c = b;
																																																																																																																																						  b = a;
																																																																																																																																						  a = c;
																																																																																																																																					  }
																																																																																																																																					  else if (a<c && b>c)
																																																																																																																																					  {
																																																																																																																																						  t = b;
																																																																																																																																						  b = c;
																																																																																																																																						  c = t;
																																																																																																																																					  }
																																																																																																																																					  int x = a, y = c;
																																																																																																																																					  while (a != 0)
																																																																																																																																					  {
																																																																																																																																						  t = c % a;
																																																																																																																																						  c = a;
																																																																																																																																						  a = t;
																																																																																																																																					  }
																																																																																																																																					  cout << x / c << '/' << y / c;*/
																																																																																																																																					  /*int x, n,s=0;
																																																																																																																																						  cin >> x >> n;
																																																																																																																																						  for (int i = 0;i < n;i++,x++)
																																																																																																																																						  {
																																																																																																																																							  if (x == 6 || x == 7)
																																																																																																																																							  {
																																																																																																																																								  continue;
																																																																																																																																							  }
																																																																																																																																							  if (x % 8 == 0)
																																																																																																																																							  {
																																																																																																																																								  x = 1;
																																																																																																																																							  }
																																																																																																																																							  s += 250;
																																																																																																																																						  }
																																																																																																																																						  cout << s;*/
																																																																																																																																						  /*int a = 0;
																																																																																																																																							  double b = 0;
																																																																																																																																							  cin >> a;
																																																																																																																																							  if (a <= 150)
																																																																																																																																							  {
																																																																																																																																								  b = a * 0.4463;
																																																																																																																																							  }
																																																																																																																																							  else if (a >= 151 && a <= 400)
																																																																																																																																							  {
																																																																																																																																								  b += 150 * 0.4463;
																																																																																																																																								  b += (a - 150) * 0.4663;
																																																																																																																																							  }
																																																																																																																																							  else
																																																																																																																																							  {
																																																																																																																																								  b += 150 * 0.4463;
																																																																																																																																								  b += (400 - 150) * 0.4663;
																																																																																																																																								  b += (a - 400) * 0.5663;
																																																																																																																																							  }
																																																																																																																																							  b = int((b * 10) + 0.5) / 10.0;
																																																																																																																																							  cout << b;*/
																																																																																																																																							  /*char m[14];
																																																																																																																																								  cin >> m;
																																																																																																																																								  int n = 0;
																																																																																																																																								  char x = 'X';
																																																																																																																																								  for (int i = 1;i <= 1;i++)
																																																																																																																																								  {
																																																																																																																																									  n += (m[i - 1]-'0') * i;
																																																																																																																																								  }
																																																																																																																																								  for (int i = 3;i <= 5;i++)
																																																																																																																																								  {
																																																																																																																																									  n += (m[i - 1] - '0') * (i-1);
																																																																																																																																								  }
																																																																																																																																								  for (int i = 7;i <= 11;i++)
																																																																																																																																								  {
																																																																																																																																									  n += (m[i - 1] - '0') * (i-2);
																																																																																																																																								  }
																																																																																																																																								   n = n % 11;
																																																																																																																																								   if (n == 10)
																																																																																																																																								   {
																																																																																																																																									   if (x == m[12])
																																																																																																																																										   cout << "Right";
																																																																																																																																									   else
																																																																																																																																									   {
																																																																																																																																										   m[12] = x;
																																																																																																																																										   cout << m;
																																																																																																																																									   }
																																																																																																																																								   }
																																																																																																																																								   else
																																																																																																																																								   {
																																																																																																																																									   if (n == (m[12] - '0'))
																																																																																																																																										   cout << "Right";
																																																																																																																																									   else
																																																																																																																																									   {
																																																																																																																																										   m[12] = n + '0';
																																																																																																																																										   cout << m;
																																																																																																																																									   }
																																																																																																																																								   }*/
																																																																																																																																								   /*int n, s = 0,c=0;
																																																																																																																																									   int a, b;
																																																																																																																																									   cin >> n;
																																																																																																																																									   for (int i = 0;i < 3;i++)
																																																																																																																																									   {
																																																																																																																																										   cin >> a >> b;
																																																																																																																																										   if (n % a != 0)
																																																																																																																																										   {
																																																																																																																																											   c=1;
																																																																																																																																										   }
																																																																																																																																										   if (s == 0)
																																																																																																																																										   {
																																																																																																																																											   s = ((n / a) + c) * b;
																																																																																																																																										   }
																																																																																																																																										   if (s > ((n / a) + c) * b)
																																																																																																																																										   {
																																																																																																																																											   s = ((n / a) + c) * b;
																																																																																																																																										   }
																																																																																																																																									   }
																																																																																																																																									   cout << s;*/
																																																																																																																																									   /* int n, m,d=0;
																																																																																																																																										   for (int i = 1;i <= 7;i++)
																																																																																																																																										   {
																																																																																																																																											   cin >> n >> m;
																																																																																																																																											   if (m + n > 8&&d==0)
																																																																																																																																											   {
																																																																																																																																												   d= i;
																																																																																																																																											   }
																																																																																																																																										   }
																																																																																																																																										   cout << d;*/
																																																																																																																																										   //int a, b, c;
																																																																																																																																											   //cin >> a >> b >> c;
																																																																																																																																											   //int t=a;
																																																																																																																																											   //if (a > b)
																																																																																																																																											   //{
																																																																																																																																											   //    a = b;
																																																																																																																																											   //    b = t;
																																																																																																																																											   //}
																																																																																																																																											   //if (c >= a)
																																																																																																																																											   //{
																																																																																																																																											   //    if (c < b)
																																																																																																																																											   //    {
																																																																																																																																											   //        cout << a <<' ' << c << ' ' << b;
																																																																																																																																											   //    }
																																																																																																																																											   //    else
																																																																																																																																											   //        cout << a << ' ' << b << ' ' << c;
																																																																																																																																											   //}
																																																																																																																																											   //else 
																																																																																																																																											   //    cout << c << ' ' << a << ' ' << b;
																																																																																																																																											   //    
																																																																																																																																										   /* int n;
																																																																																																																																											   cin >> n;
																																																																																																																																											   int local = n * 5;
																																																																																																																																											   int  luogu = 11 + n * 3;
																																																																																																																																											   if (local < luogu)
																																																																																																																																												   cout << "Local";
																																																																																																																																											   else
																																																																																																																																												   cout << "Luogu";*/
																																																																																																																																												   //void InsertSort(int ar[], int n) {
																																																																																																																																												   //    for (int i=1;i < n;i++) {
																																																																																																																																												   //        if (ar[i] < ar[i-1]) {
																																																																																																																																												   //            int j = i - 1;
																																																																																																																																												   //            //复制出哨兵x
																																																																																																																																												   //            int x = ar[i];
																																																																																																																																												   //            //移动比哨兵大的数
																																																																																																																																												   //            while (j > 0 && x < ar[j]) {
																																																																																																																																												   //                ar[j + 1] = ar[j];
																																																																																																																																												   //                j--;
																																																																																																																																												   //            }
																																																																																																																																												   //            //把哨兵放在ar[j]后面
																																																																																																																																												   //            ar[j+1] = x;
																																																																																																																																												   //        }
																																																																																																																																												   //    }
																																																																																																																																												   //
																																																																																																																																												   //
																																																																																																																																												   //
																																																																																																																																												   //
																																																																																																																																												   //}
																																																																																																																																												   //void Merge(int ar[], int low,int mid, int high) {
																																																																																																																																												   //    int i = low, j = mid + 1, k = 0;
																																																																																																																																												   //    int* temp = new(nothrow)int[high - low + 1];
																																																																																																																																												   //    if (!temp)
																																																																																																																																												   //        return;
																																																																																																																																												   //    while (i <= mid && j <= high) {
																																																																																																																																												   //        if (ar[i] <= ar[j])
																																																																																																																																												   //            temp[k++] = ar[i++];
																																																																																																																																												   //        else
																																																																																																																																												   //            temp[k++] = ar[j++];
																																																																																																																																												   //    }
																																																																																																																																												   //    while (i <= mid)
																																																																																																																																												   //        temp[k++] = ar[i++];
																																																																																																																																												   //    while (i <= high)
																																																																																																																																												   //        temp[k++] = ar[j++];
																																																																																																																																												   //    for (int i = low, k = 0;i < high;i++)
																																																																																																																																												   //        ar[i] = temp[k++];
																																																																																																																																												   //    delete[]temp;
																																																																																																																																												   //}
																																																																																																																																												   //void MergeSort(int ar[], int low, int high) {
																																																																																																																																												   //    if (low < high)
																																																																																																																																												   //    {
																																																																																																																																												   //        int mid = (low + high) / 2;
																																																																																																																																												   //        MergeSort(ar, low, mid);
																																																																																																																																												   //        MergeSort(ar, mid + 1, high);
																																																																																																																																												   //        Merge(ar, low, mid, high);
																																																																																																																																												   //    }
																																																																																																																																												   //}
																																																																																																																																												   /* int x;
																																																																																																																																													   cin >> x;
																																																																																																																																													   if (x == 1)cout << "Today, I ate 1 apple.";
																																																																																																																																													   else if(x==0)cout << "Today, I ate 0 apple.";
																																																																																																																																													   else
																																																																																																																																														   printf("Today, I ate %d apples.", x);*/
																																																																																																																																														   //#include<iostream>
																																																																																																																																														   //using namespace std;
																																																																																																																																														   //int solve(int n,int m=6) {
																																																																																																																																														   //	if (n == 1) return 6;
																																																																																																																																														   //	for (int i = 1;i < n;i++)
																																																																																																																																														   //		m *= 10;
																																																																																																																																														   //	return (m += solve(n - 1));
																																																																																																																																														   //}
																																																																																																																																														   //int main()
																																																																																																																																														   //{
																																																																																																																																														   //	int n,s=0;
																																																																																																																																														   //	cin >> n;
																																																																																																																																														   //	for (int i = 1;i <= n;i++) {
																																																																																																																																														   //		s += solve(i);	
																																																																																																																																														   //	}
																																																																																																																																														   //	cout << s;
																																																																																																																																														   //	return 0;
																																																																																																																																														   //}
																																																																																																																																														   //int prime[MAX_N];
																																																																																																																																															   //bool is_prime[MAX_N + 1];
																																																																																																																																															   //int sieve(int n) {
																																																																																																																																															   //	int p = 0;
																																																																																																																																															   //	for (int i = 0;i <= n;i++) is_prime[i] = true;
																																																																																																																																															   //	is_prime[0] = is_prime[1] = false;
																																																																																																																																															   //	for (int i = 2;i <= n;i++) {
																																																																																																																																															   //		if (is_prime(i)) {
																																																																																																																																															   //			prime[p++] = i;
																																																																																																																																															   //			//j+=i提升倍数
																																																																																																																																															   //			for (int j = 2 * i;j <= n;j += i) is_prime[j] = false;
																																																																																																																																															   //		}
																																																																																																																																															   //	}
																																																																																																																																															   //	return p;
																																																																																																																																															   //}
																																																																																																																																														   //#include<iostream>
																																																																																																																																														   //using namespace std;
																																																																																																																																														   //int main()
																																																																																																																																														   //{
																																																																																																																																														   //	int s, i,t;
																																																																																																																																														   //	char ch;
																																																																																																																																														   //	scanf("%d %c", &s, &ch);
																																																																																																																																														   //	for (i = 1;2 * i * i - 1 <= s;i++)
																																																																																																																																														   //		t=  s-(2 * i * i - 1) ;i--;
																																																																																																																																														   //	for (int j = i;j > 0;j--)
																																																																																																																																														   //	{
																																																																																																																																														   //		for (int k = i;k - j > 0;k--)
																																																																																																																																														   //			cout << ' ';
																																																																																																																																														   //		for (int k = 2 * j - 1;k > 0;k--)
																																																																																																																																														   //			cout << ch;cout << endl;
																																																																																																																																														   //	}i--;
																																																																																																																																														   //	for (int j = 1;j <= i;j++)
																																																																																																																																														   //	{
																																																																																																																																														   //		for (int k = j;i - k > 0;k++)
																																																																																																																																														   //			cout << ' ';
																																																																																																																																														   //		for (int k = 2 * j + 1;k > 0;k--)
																																																																																																																																														   //			cout << ch;cout << endl;	
																																																																																																																																														   //	}
																																																																																																																																														   //	cout << t;
																																																																																																																																														   //
																																																																																																																																														   //	return 0;
																																																																																																																																														   //}
																																																																																																																																														   //const int INF = 10000000;
																																																																																																																																														   //typedef pair<int, int > P;
																																																																																																																																														   //char maze[1000];
																																																																																																																																														   //int n, m;
																																																																																																																																														   //int sx, sy;
																																																																																																																																														   //int gx, gy;
																																																																																																																																														   //int d[1000][1000];
																																																																																																																																														   //int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
																																																																																																																																														   //int bfs() {
																																																																																																																																														   //	queue<P> que;
																																																																																																																																														   //	for()
																																																																																																																																														   //}
																																																																																																																																														   ////sum s;2n^2-1
																																																																																																																																															   ////int n,i;
																																																																																																																																															   ////char star;
																																																																																																																																															   ////scanf("%d %c",&n,&star);
																																																																																																																																															   ////int s = 2 * n * n - 1;
																																																																																																																																															   ////for (i = 1;2 * i * i - 1 <= s;i++)
																																																																																																																																															   ////	;
																																																																																																																																															   ////i--;
																																																																																																																																															   ////for (int j = i;j > 0;j--)
																																																																																																																																															   ////{
																																																																																																																																															   ////	for (int a = i - j;a > 0;a--)
																																																																																																																																															   ////		cout << ' ';
																																																																																																																																															   ////	for (int a = 1;a <= 2 * j - 1;a++)
																																																																																																																																															   ////		cout << star;
																																																																																																																																															   ////	cout << endl;
																																																																																																																																															   ////}
																																																																																																																																															   ///*for (int j =1;j < i;j++)
																																																																																																																																															   //{
																																																																																																																																															   //	for (;;)
																																																																																																																																															   //		cout << ' ';
																																																																																																																																															   //	for (;;)
																																																																																																																																															   //		cout << '*';
																																																																																																																																															   //	cout << endl;
																																																																																																																																															   //}*/
																																																																																																																																															   //


																																																																																																																																														   /*int n, m;
																																																																																																																																															   char field[10][11];
																																																																																																																																															   void dfs(int x, int y) {
																																																																																																																																																   field[x][y] = '.';
																																																																																																																																																   for (int dx = -1;dx <= 1;dx++) {
																																																																																																																																																	   for (int dy = -1;dy <= 1;dy++) {
																																																																																																																																																		   int nx = x + dx, ny = y + dy;
																																																																																																																																																		   if (0 <= nx && nx < n && 0 <= ny && ny < m && field[nx][ny] == 'w')dfs(nx, ny);
																																																																																																																																																	   }
																																																																																																																																																   }
																																																																																																																																																   return;
																																																																																																																																															   }*/
																																																																																																																																															   ////递归阶乘
																																																																																																																																															   //int fact(int n) {
																																																																																																																																															   //	if (n == 0)return 1;
																																																																																																																																															   //	return n * fact(n - 1);
																																																																																																																																															   //}
																																																																																																																																															   //bool binary_search(int x) {
																																																																																																																																															   //	int n, max;
																																																																																																																																															   //	max = 100;
																																																																																																																																															   //	cin >> n ;
																																																																																																																																															   //	int k[max];
																																																																																																																																															   //	//在k[]中查找x：
																																																																																																																																															   //		int l = 0, r = n;
																																																																																																																																															   //		while (r - l >= 1) {
																																																																																																																																															   //			int i = (l + r) / 2;
																																																																																																																																															   //			if (k[i] == x)return true;
																																																																																																																																															   //			else if (k[i] < i) l = i + 1;
																																																																																																																																															   //			else r = i;
																																																																																																																																															   //		}
																																																																																																																																															   //		return false;
																																																																																																																																															   //	}
																																																																																																																																															   //// 2019/11/24 第一篇博客
																																																																																																																																															   //#include<stdio.h>
																																																																																																																																															   //int main() {
																																																																																																																																															   //	int N;
																																																																																																																																															   //	while (scanf("%d", &N) != EOF)
																																																																																																																																															   //	{
																																																																																																																																															   //		long long fact = 1, sum = 1;
																																																																																																																																															   //		for (int i = 2; i <= N; i++)
																																																																																																																																															   //		{
																																																																																																																																															   //			fact = (fact * i) % 1000000007;//由原理一可知，阶乘的结果每次都保存，不用再算一遍 .由原理1 ，可以把每次相乘后都对1000000007取余       
																																																																																																																																															   //			sum = (fact + sum) % 1000000007;//由原理二可知 ，阶乘和的结果对1000000007取余可以每次对1000000007取余后再加入sum中   
																																																																																																																																															   //		}
																																																																																																																																															   //		printf("%lld\n", sum);
																																																																																																																																															   //	}
																																																																																																																																															   //	return 0;
																																																																																																																																															   //}
																																																																																																																																															   /*double x;
																																																																																																																																																   cin >> x;
																																																																																																																																																   cout << setiosflags(ios::fixed) << setprecision(1);
																																																																																																																																																   if (x == 0)
																																																																																																																																																	   printf("f(0.0) = 0.0");
																																																																																																																																																   else
																																																																																																																																																	   printf("f(%.1lf) = %.1lf",x,1/x);*/
																																																																																																																																																	   /////*cout <<5/9<< endl;
																																																																																																																																																		   ////printf("%d", 5 / 9);*/
																																																																																																																																																		   ////long int m;
																																																																																																																																																		   ////int i = 0;
																																																																																																																																																		   ////cin >> m;
																																																																																																																																																		   ////while (m)
																																																																																																																																																		   ////{
																																																																																																																																																		   ////	i++;
																																																																																																																																																		   ////	m /= 10;
																																																																																																																																																		   ////}
																																																																																																																																																		   ////cout << i;
																																																																																																																																																	   // int m,t,n;
																																																																																																																																																		   //m = 1;
																																																																																																																																																		   //cin >> n;
																																																																																																																																																		   //t = n;
																																																																																																																																																		   //while (t > 9)
																																																																																																																																																		   //{
																																																																																																																																																		   //	t /= 10;
																																																																																																																																																		   //	m *= 10;
																																																																																																																																																		   //}
																																																																																																																																																		   //while (m > 0)
																																																																																																																																																		   //{
																																																																																																																																																		   //	printf("%d ", n / m);
																																																																																																																																																		   //	n%= m;
																																																																																																																																																		   //	m /= 10;
																																																																																																																																																		   //}
																																																																																																																																																		   //
																																																																																																																																																	   ///*for (int i = 0;i < 5;i++)
																																																																																																																																																		   //{
																																																																																																																																																		   //	
																																																																																																																																																		   //}*/

																																																																																																																																																	   //int s;
																																																																																																																																																		   //cout << "[1] apple"<<endl;
																																																																																																																																																		   //cout << "[2] pear" << endl;
																																																																																																																																																		   //cout << "[3] orange" << endl;
																																																																																																																																																		   //cout << "[4] grape" << endl;
																																																																																																																																																		   //cout << "[0] exit" << endl;
																																																																																																																																																		   //for (int i = 0;i < 5;i++)
																																																																																																																																																		   //{
																																																																																																																																																		   //	cin >> s;
																																																																																																																																																		   //	if (s == 0)return 0;
																																																																																																																																																		   //	if (s > 5)return 0;
																																																																																																																																																		   //	if (s < 0)return 0;
																																																																																																																																																		   //	switch (s)
																																																																																																																																																		   //	{
																																																																																																																																																		   //	case 1:cout << "prise =" << 3.00 << endl;break;
																																																																																																																																																		   //	case 2:cout << "prise =" << 2.50 << endl;break;
																																																																																																																																																		   //	case 3:cout << "prise =" << 4.10 << endl;break;
																																																																																																																																																		   //	case 4:cout << "prise =" << 10.20 << endl;break;
																																																																																																																																																		   //	default:cout << "prise =" << 0.00 << endl;break;
																																																																																																																																																		   //	
																																																																																																																																																		   //	}
																																																																																																																																																		   //	
																																																																																																																																																		   //}
																																																																																																																																																		   /*int y,t;
																																																																																																																																																		   double wage;
																																																																																																																																																		   cout << setiosflags(ios::fixed) << setprecision(2);
																																																																																																																																																		   cin >>y >>t;
																																																																																																																																																		   if (y < 5)
																																																																																																																																																		   {
																																																																																																																																																			   if (t <= 40)
																																																																																																																																																				   cout << (wage = 30.0 * t);
																																																																																																																																																			   else
																																																																																																																																																				   cout << (1.5 * (t - 40)*30 + 30.0 * 40);
																																																																																																																																																		   }
																																																																																																																																																		   else
																																																																																																																																																		   {
																																																																																																																																																			   if (t <= 40)
																																																																																																																																																				   cout << (wage = 50.0 * t);
																																																																																																																																																			   else
																																																																																																																																																				   cout << (1.5 * (t - 40)*50 + 50.0 * 40);
																																																																																																																																																		   }*/
																																																																																																																																																		   /*int a, b, c, d, e,n;
																																																																																																																																																			   a = b = c = d = e = 0;
																																																																																																																																																			   cin >> n ;
																																																																																																																																																			   int ar[n];
																																																																																																																																																			   for (int i = 0;i < n;i++)
																																																																																																																																																			   {
																																																																																																																																																				   scanf("%d", &ar[i]);
																																																																																																																																																				   if (ar[i] >= 90)a++;
																																																																																																																																																				   else if (ar[i] >= 80)b++;
																																																																																																																																																				   else if (ar[i] >= 70)c++;
																																																																																																																																																				   else if (ar[i] >= 60)d++;
																																																																																																																																																				   else if (ar[i] < 60)e++;
																																																																																																																																																			   }
																																																																																																																																																			   cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e;
																																																																																																																																																			   */
																																																																																																																																																			   /*double b = 123.456789;
																																																																																																																																																				   double c = 987.654321;
																																																																																																																																																				   cout << b << endl<<c<<endl;
																																																																																																																																																				   cout << setiosflags(ios::fixed) << setprecision(6) << b << endl;
																																																																																																																																																				   cout << c;*/
																																																																																																																																																				   /*int y, m;
																																																																																																																																																		   cin >> y >> m;
																																																																																																																																																		   switch (m)
																																																																																																																																																		   {
																																																																																																																																																		   case 1:cout << 31;break;
																																																																																																																																																		   case 2:
																																																																																																																																																		   {
																																																																																																																																																			   if (y % 4 == 0 && y % 100 != 0)
																																																																																																																																																			   {
																																																																																																																																																				   cout << 29;
																																																																																																																																																			   }

																																																																																																																																																			   else if (y % 400 == 0)
																																																																																																																																																					   cout << 29;


																																																																																																																																																			   else
																																																																																																																																																				   cout << 28;
																																																																																																																																																		   }break;
																																																																																																																																																		   case 3:cout << 31;break;
																																																																																																																																																		   case 4:cout << 30;break;
																																																																																																																																																		   case 5:cout << 31;break;
																																																																																																																																																		   case 6:cout << 30;break;
																																																																																																																																																		   case 7:cout << 31;break;
																																																																																																																																																		   case 8:cout << 31;break;
																																																																																																																																																		   case 9:cout << 30;break;
																																																																																																																																																		   case 10:cout << 31;break;
																																																																																																																																																		   case 11:cout << 30;break;
																																																																																																																																																		   case 12:cout << 31;break;
																																																																																																																																																		   }
																																																																																																																																																		   */







	
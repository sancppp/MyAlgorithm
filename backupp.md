## 1.基本宏定义

```cpp
#include <bits/stdc++.h>

using namespace std;
//-----pre_def----
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = (a); i <= (b); i++)
#define rif(i, a, b) for (int i = (a); i >= (b); i--)
#define endl '\n'
#define init_h memset(h, -1, sizeof h), idx = 0;
#define lowbit(x) x &(-x)

//---------------
const int N = 1e5+10;

void init(){}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    int T = 1;
    scanf("%d",&T);
    while (T--)
    {
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
```

## 2.动态规划

模型整理

### 1.背包模型

### 2. 。。。。。



## 3.数据结构

### 1.线段树

#### 线段树+将问题转化为线段树的区间问题

在卖礼物的超市中有*n*个柜子，每个柜子里都摆放了一个礼物，每个礼物有自己的一个编号，第i*个柜子里的礼物编号为*$a_i$。有*q*次操作，格式如下：
1  *x*，第*x*个柜子里的礼物被买走，保证此时这个柜子里的礼物还在。
2 *l* *r*，茶山牛询问第*l*到第*r*个柜子未被买走的礼物中是否有两个礼物编号相同。

-------

问题转化：

数据结构
$用last_{i}代表与a_{i}相同且小于\mathit i的最大的还没被买走的礼物位置\mathit j，如果没有则置为\text 0。\\
用next_{i}代表与a_{i}相同且大于\mathit i的最小的还没被买走的礼物位置\mathit k，如果没有则置为\mathit n+1。\\
（实质上就是[链表]()）\\
对于修改操作，设被买走的位置是\mathit i，则 \\\mathit next[last[i]]=next[i]\\
\mathit last[next[i]]=last[i]\\
\mathit last[i]=0\\
\mathit next[i]=n+1\\
对于查询操作，实际上就是询问\mathit l到\mathit r范围内是否有位置\mathit i的\mathit next值小于等于\mathit r即可。\\
于是问题变成了单点更新，区间查询最小值，用线段树就可以完成任务了。$

```cpp
#include <bits/stdc++.h>

using namespace std;
//-----pre_def----
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = (a); i <= (b); i++)
#define rif(i, a, b) for (int i = (a); i >= (b); i--)
#define endl '\n'
#define init_h memset(h, -1, sizeof h), idx = 0;
#define lowbit(x) x &(-x)

//---------------
const int N = 1e6 + 10;
int n, m, x;
int las[N], nex[N], d[N], sub[N];
struct node
{
    int l, r, v;
} tr[N << 2];

void init()
{
    fir(i, 1, n)
    {
        las[i] = 0;
        nex[i] = n + 1;
    }
}

void pushup(int u)
{
    tr[u].v = min(tr[u << 1].v, tr[u << 1 | 1].v);
}

void build(int u, int l, int r)
{
    tr[u] = {l, r};
    if (l == r)
    {
        tr[u].v = nex[l];
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int x, int v)
{
    if (tr[u].l == tr[u].r && tr[u].l == x)
    {
        tr[u].v = v;
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid)
        {
            modify(u << 1, x, v);
        }
        else
        {
            modify(u << 1 | 1, x, v);
        }
        pushup(u);
    }
}

int query(int u, int l, int r)
{
    if (l <= tr[u].l && tr[u].r <= r)
    {
        return tr[u].v;
    }
    int res = INF;
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid)
        res = query(u << 1, l, r);
    if (r > mid)
        res = min(res, query(u << 1 | 1, l, r));
    return res;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    scanf("%d%d", &n, &m);
    init();
    fir(i, 1, n)
    {
        scanf("%d", &d[i]);
        if (sub[d[i]])
        {
            nex[sub[d[i]]] = i;
            las[i] = sub[d[i]];
        }
        sub[d[i]] = i;
    }
    build(1, 1, n);
    while (m--)
    {
        int op;
        int l, r;
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d", &l);
            nex[las[l]] = nex[l];
            las[nex[l]] = las[l];
            modify(1, las[l], nex[l]);
            modify(1, l, n + 1);
            nex[l] = n + 1;
            las[l] = 0;
        }
        else
        {
            scanf("%d%d", &l, &r);
            if (query(1, l, r) <= r)
            {
                puts("1");
            }
            else
                puts("0");
        }
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
```

#### 线段树维护最小生成树所用到的边

小 Z 喜欢最小生成树。

小 Z 有一张 *n* 个点 *m* 条边的图，每条边连接点 $u_i,v_i$ ，边权为 $w_i$。他想进行 q 次操作，有如下两种类型：

1. 修改第 x*x* 条边为连接点 *y*,*z* ，边权为 *t* ；
2. 查询只用编号在 [l,r][*l*,*r*] 范围内的边，得到的最小生成树权值是多少。

由于修改和查询量实在是太大了，小 Z 想请你用程序帮他实现一下。

```cpp
#include <bits/stdc++.h>

using namespace std;
//-----pre_def----
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = (a); i <= (b); i++)
#define rif(i, a, b) for (int i = (a); i >= (b); i--)
#define endl '\n'
#define init_h memset(h, -1, sizeof h), idx = 0;
#define lowbit(x) x &(-x)

//---------------
const int N = 210, M = 3e4 + 10;
int n, m, q, u, v, w;
int fa[N];
vector<int> ans;
void init()
{
    fir(i, 1, n) fa[i] = i;
}
struct edges
{
    int u, v, w;
} edge[M];
struct node
{
    int l, r;
    vector<int> seq;
} tr[M << 2];

int find(int x)
{
    if (x != fa[x])
        fa[x] = find(fa[x]);
    return fa[x];
}

bool Union(int a, int b)
{
    a = find(a), b = find(b);
    if (a == b)
        return false;
    fa[a] = b;
    return true; //成功进行了一次合并
}

void pushup(vector<int> &s1, vector<int> &s2, vector<int> &s3) //很厉害的合并操作
{
    static vector<int> tmp; //归并排序进行Kruskal
    init();                 //初始化并查集数组
    tmp.clear();
    int i = 0, j = 0;
    while (i < s2.size() || j < s3.size())
    {
        if (j >= s3.size() || (i < s2.size() && edge[s2[i]].w < edge[s3[j]].w))
        {
            if (Union(edge[s2[i]].u, edge[s2[i]].v)) //如果Union操作成功进行了一次合并
                tmp.push_back(s2[i]);
            i++;
        }
        else
        {
            if (Union(edge[s3[j]].u, edge[s3[j]].v)) //如果Union操作成功进行了一次合并
                tmp.push_back(s3[j]);
            j++;
        }
    }
    s1 = tmp;
}

void pushup(int u)
{
    pushup(tr[u].seq, tr[u << 1].seq, tr[u << 1 | 1].seq);
}

void build(int u, int l, int r)
{
    tr[u].l = l, tr[u].r = r;
    if (l == r)
    {
        tr[u].seq.push_back(l); //节点中维护最小生成树的边（分析可知，父节点的信息可由子节点推出）
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u); //合并操作操作
}

void modify(int u, int l, int r)
{
    if (l <= tr[u].l && tr[u].r <= r)
    {
        tr[u].seq.clear();
        tr[u].seq.push_back(l); //l为当前点的编号
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid)
        modify(u << 1, l, r);
    if (mid < r)
        modify(u << 1 | 1, l, r);
    pushup(u);
}
void query(int u, int l, int r)
{
    if (l <= tr[u].l && tr[u].r <= r)
    {
        pushup(ans, ans, tr[u].seq);
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid)
        query(u << 1, l, r);
    if (mid < r)
        query(u << 1 | 1, l, r);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    scanf("%d%d%d", &n, &m, &q);
    fir(i, 1, m)
    {
        scanf("%d%d%d", &u, &v, &w);
        edge[i] = {u, v, w};
    }
    build(1, 1, m);
    for (int i = 1; i <= q; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 2)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            ans.clear();
            int sum = 0;
            query(1, l, r);
            if (ans.size() != n - 1)
            {
                puts("Impossible");
            }
            else
            {
                for (auto t : ans)
                    sum += edge[t].w;
                printf("%d\n", sum);
            }
        }
        else
        {
            int x, y, z, t;
            scanf("%d%d%d%d", &x, &y, &z, &t);
            edge[x] = {y, z, t};
            modify(1, x, x);
        }
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
/*
5 5 3
1 2 1
2 3 2
3 4 3
4 5 4
1 5 3
2 1 4
2 2 5
2 1 5

10
12
9
*/
```



### 2.树状数组

#### 1.最基本

```cpp
#include <bits/stdc++.h>

using namespace std;
//-----pre_def----
const double PI = acos(-1.0);
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = (a); i <= (b); i++)
#define rif(i, a, b) for (int i = (a); i >= (b); i--)
#define init_h memset(h, -1, sizeof h), idx = 0;
#define lowbit(x) x &(-x)
//---------------
//最基本树状数组模板（单点修改+查询前缀和）
//应用：求逆序对；求区间最大值（RMQ）；通过差分实现"区间修改+单点查询";同时维护两个树状数组实现"区间修改+区间查询"；二维情况：矩阵
const int N = 50010;
int n, x;
int tr[N]; //树状数组的数组

void add(int v, int x) //调整操作：在下标为v的位置加x
{
    for (int i = v; i <= n; i += lowbit(i))
        tr[i] += x;
}

int sum(int v) 
{
    int ans=0;
    for(int i=v;i;i-=lowbit(i))
    {
        ans+=tr[i];
    }
    return ans;
}

void init()
{
    memset(tr,0,sizeof tr);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    int T;
    scanf("%d", &T);
    fir(Q,1,T)
    {
        printf("Case %d:\n",Q);
        init();
        scanf("%d", &n);
        fir(i, 1, n)
        {
            scanf("%d", &x);
            add(i, x);
        }
        string op;
        while(cin>>op,op[0]!='E')
        {
            int i,j;
            cin>>i>>j;
            if(op[0]=='A')
                add(i,j);
            else if(op[0]=='S')
                add(i,-j);
            else
                cout<<sum(j)-sum(i-1)<<endl;
        }
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
```

#### 2.区间修改，区间（单点）查询

```cpp
#include <bits/stdc++.h>

using namespace std;
//-----pre_def----
const double PI = acos(-1.0);
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = (a); i <= (b); i++)
#define rif(i, a, b) for (int i = (a); i >= (b); i--)
#define init_h memset(h, -1, sizeof h), idx = 0;
#define lowbit(x) x &(-x)
//---------------
//树状数组模板（区间修改+区间查询）
//第一个树状数组为差分数组
//第二个树状数组为数学推导出来的：https://www.cnblogs.com/bluefly-hrbust/p/10416808.html
//例题：https://www.luogu.com.cn/problem/P3372
//注意：此题要开long long
const int N = 1e5+10;
LL sum1[N]; //第一个树状数组
LL sum2[N]; //第二个树状数组(数学推导)
LL a[N];
int n, m;

void update(int x, int w)
{ //更新效果：把x位置后面所有的数的值+w
    for (int i = x; i <= n; i += lowbit(i))
    {
        sum1[i] += w;           //维护前缀和c[i]
        sum2[i] += w * (x - 1); //维护前缀和c[i]*(n-1)
    }
}
void range_update(int l, int r, int val) //更新效果：把l位置到r位置所有的数的值+w
{
    //类比差分
    update(l, val);
    update(r + 1, -val);
}
LL sum(int x) //求1-x的和
{
    LL ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        ans += x * sum1[i] - sum2[i];
    }
    return ans;
}
LL range_ask(int l, int r) //求l-r的和
{
    return sum(r) - sum(l - 1);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld", &a[i]);
            update(i, a[i] - a[i - 1]); //维护差分数组
        }
        while(m--)
        {
            int op,x,y,k;
            cin>>op>>x>>y;
            if(op==1)
            {
                cin>>k;
                range_update(x,y,k);
            }
            else
            {
                cout<<range_ask(x,y)<<endl;
            }
            
        }
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
```

#### 3.二维

```CPP
#include <bits/stdc++.h>

using namespace std;
//-----pre_def----
const double PI = acos(-1.0);
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = (a); i <= (b); i++)
#define rif(i, a, b) for (int i = (a); i >= (b); i--)
#define init_h memset(h, -1, sizeof h), idx = 0;
#define lowbit(x) x &(-x)
//---------------
//二维树状数组模板（区间修改+区间查询）
//本质：把树状数组应用到矩阵，同时维护x,y两个下标 + 4个二维树状数组（数学推导出来的）

const int N = 210;

LL n, m, Q;//n*m的矩阵
LL tr1[N][N], tr2[N][N], tr3[N][N], tr4[N][N];
void add(LL x, LL y, LL z)
{
    for (int X = x; X <= n; X += X & -X)
        for (int Y = y; Y <= m; Y += Y & -Y)
        {
            tr1[X][Y] += z;
            tr2[X][Y] += z * x;
            tr3[X][Y] += z * y;
            tr4[X][Y] += z * x * y;
        }
}

void range_add(LL xa, LL ya, LL xb, LL yb, LL z) //(xa, ya) 到 (xb, yb) 的矩形加上z
{
    add(xa, ya, z);
    add(xa, yb + 1, -z);
    add(xb + 1, ya, -z);
    add(xb + 1, yb + 1, z);
}

LL sum(LL x, LL y)
{
    LL res = 0;
    for (int i = x; i; i -= i & -i)
        for (int j = y; j; j -= j & -j)
            res += (x + 1) * (y + 1) * tr1[i][j] - (y + 1) * tr2[i][j] - (x + 1) * tr3[i][j] + tr4[i][j];
    return res;
}

LL range_sum(LL xa, LL ya, LL xb, LL yb)
{
    return sum(xb, yb) - sum(xb, ya - 1) - sum(xa - 1, yb) + sum(xa - 1, ya - 1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    while (~scanf("%d%d", &n, &m))
    {
        range_add(1,1,5,5,3);
        range_add(2,2,4,4,2);
        cout<<range_sum(3,3,4,5)<<endl;
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
```

#### 4.三维

```cpp
#include <bits/stdc++.h>

using namespace std;
//-----pre_def----
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = (a); i <= (b); i++)
#define rif(i, a, b) for (int i = (a); i >= (b); i--)
#define endl '\n'
#define init_h memset(h, -1, sizeof h), idx = 0;
#define lowbit(x) x &(-x)

//---------------
const int N = 1e2 + 10;
int n, tr[N][N][N];
void update(int x, int y, int z, int d)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            for (int k = z; k <= n; k += lowbit(k))
                tr[i][j][k] += d;
}
LL query(int x, int y, int z)
{
    LL ret = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            for (int k = z; k > 0; k -= lowbit(k))
                ret += tr[i][j][k];
    return ret;
}
//无区间修改函数。。
LL solve(int x, int y, int z, int xx, int yy, int zz)
{
    return query(xx, yy, zz)
        - query(xx, yy, z - 1)
        - query(xx, y - 1, zz)
        - query(x - 1, yy, zz)
        + query(xx, y - 1, z - 1)
        + query(x - 1, yy, z - 1)
        + query(x - 1, y - 1, zz)
        - query(x - 1, y - 1, z - 1);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    int T = 1;
    scanf("%d", &T);
    while (T--)
    {
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
```



### 3.并查集

### 4.平衡树

### 5.堆

### 6.主席树（可持久化线段树）

### 7.树上问题



## 4.图论

## 5.计算几何

## 6.杂项


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
#define init_h memset(h, -1, sizeof h), idx = 0;
#define lowbit(x) x &(-x)

//---------------
//splay基本模板（代码长度适中，非常灵活）
//https://www.acwing.com/problem/content/2439/
//https://www.luogu.com.cn/problem/P3391(同一道题)
//基本题意：多次区间翻转，求最终结果（中序遍历）
const int N = 1e5 + 10;

struct node
{
    int s[2], p, v;     //s[0]==lson,s[1]==rson,p=pre,v=val（注意：splay中的val不作为排序依据，只在初始状态下有序）
    int size, lazy_tag; //size==包括自身在内的子树的节点数，懒标记记录反转
    void init(int _v, int _p)
    {
        v = _v;
        p = _p;
        size = 1;
    }
} tr[N];
int n, m;
int root, idx;

void pushup(int u)
{
    tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1; //本题中不会出现cnt（一个节点上有两个相同的val的情况）
}
void pushdown(int u) //传递标记
{
    if (tr[u].lazy_tag)
    {
        swap(tr[u].s[1], tr[u].s[0]);
        tr[tr[u].s[0]].lazy_tag ^= 1;
        tr[tr[u].s[1]].lazy_tag ^= 1;
        tr[u].lazy_tag = 0;
    }
}

void rotate(int x) //核心函数1：将所有情况的左旋右旋写在一个函数里面
{
    int y = tr[x].p, z = tr[y].p; //在这个链上：z是祖宗，y是爸爸，x是儿子。现在要把x移动到最上边
    int k = tr[y].s[1] == x;      // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1];
    tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y;
    tr[y].p = x;
    pushup(y), pushup(x); //顺序不能乱
}

void splay(int x, int k) //核心函数2：将x节点旋转至k下面
{
    while (tr[x].p != k) //但x的父节点不为k时
    {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) //x的祖宗还不是k
        {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) //异或，当zyx不为一条直链的时候
            {
                rotate(x);
            }
            else
            {
                rotate(y);
            }
        }
        rotate(x);
    }
    if (!k) //如果k==0，等加于将x旋转至root
        root = x;
}

void insert(int v)
{
    int u = root, p = 0;
    while (u) //直到叶子节点
    {
        p = u, u = tr[u].s[v > tr[u].v]; //向下找
    }
    u = ++idx;
    if (p) //个人理解：如果有父节点，说明上面的while循环被执行了（特判第一次插入节点）
    {
        tr[p].s[v > tr[p].v] = u;
    }
    tr[u].init(v, p); //初始化
    splay(u, 0);      //splay优化
}

int get_k(int k) //找到中序遍历中第k个元素(并非val的第k大)
{
    int u = root;
    while (true)
    {
        pushdown(u); //传统pushdown
        if (tr[tr[u].s[0]].size >= k)
            u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k)
            return u;
        else
            k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
}

void print(int u) //输出中序遍历
{
    pushdown(u);
    if (tr[u].s[0])
        print(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) //排除哨兵
        printf("%d ", tr[u].v);
    if (tr[u].s[1])
        print(tr[u].s[1]);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    scanf("%d%d", &n, &m);
    insert(0); //哨兵，val=0，
    fir(i, 1, n) insert(i);
    insert(n + 1);
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = get_k(l), r = get_k(r + 2); //[l,r](要找l的前序和r的后继)==>[l-1,r+1]（有哨兵）==>[l,r+2];
        splay(l, 0);
        splay(r, l);
        tr[tr[r].s[0]].lazy_tag ^= 1;
    }
    print(root);
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
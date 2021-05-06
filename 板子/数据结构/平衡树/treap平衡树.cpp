#include <bits/stdc++.h>
using namespace std;
//-----pre_def----
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = a; i <= b; i++)
#define rif(i, a, b) for (int i = a; i >= b; i--)
#define init_h memset(h, -1, sizeof h), idx = 0;
//---------------
//treap平衡树（bst+heap）
//https://www.acwing.com/problem/content/255/
/*
1.插入数值x。
2.删除数值x(若有多个相同的数，应只删除一个)。
3.查询数值x的排名(若有多个相同的数，应输出最小的排名)。
4.查询排名为x的数值。
5.求数值x的前驱(前驱定义为小于x的最大的数)。
6.求数值x的后继(后继定义为大于x的最小的数)。
*/

//需要实现的功能函数(动态维护一颗树)
// void pushup(int u);                   //由子节点更新父节点,算size
// int get_node(int key);                //新建一个节点,返回新节点编号
// void build();                         //初始化，建立两个哨兵节点
// void zig(int &p);                     //右旋
// void zag(int &p);                     //左旋
// void remove(int &p, int key);         //删除一个数据，分情况讨论&处理
// void insert(int &p, int key);         //插入一个节点，分情况讨论&处理
// int get_rank_by_key(int p, int key);  //根据排名找成绩
// int get_key_by_rank(int p, int rank); //根据成绩找排名
// int get_perv(int p, int key);         //找key的前驱
// int get_next(int p, int key);         //找key的后继

const int N = 100010, INF = 1e8 + 10;
struct node
{
    int l, r;
    int key;
    int val;
    int cnt, size; //size表示子树节点个数(包括自己)
} tr[N];

int n, root, idx;


void pushup(int u) //由子节点更新父节点,算size
{
    tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].cnt;
}

int get_node(int key) //新建一个节点
{
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

void zig(int &p) //右旋操作
{
    int q = tr[p].l;
    tr[p].l = tr[q].r, tr[q].r = p;
    p = q;
    pushup(tr[p].r);
    pushup(p);
}

void zag(int &p) //左旋操作
{
    int q = tr[p].r;
    tr[p].r = tr[q].l, tr[q].l = p, p = q;
    pushup(tr[p].l);
    pushup(p);
}

void build()
{
    get_node(-INF), get_node(INF);
    root = 1;
    tr[1].r = 2;
    pushup(root);
    if (tr[1].val < tr[2].val)
        zag(root);
}

void insert(int &p, int key)
{
    if (!p) p = get_node(key);
    else if (tr[p].key == key) tr[p].cnt ++ ;
    else if (tr[p].key > key)
    {
        insert(tr[p].l, key);
        if (tr[tr[p].l].val > tr[p].val) zig(p);
    }
    else
    {
        insert(tr[p].r, key);
        if (tr[tr[p].r].val > tr[p].val) zag(p);
    }
    pushup(p);
}
void insert1(int &p, int key)
{
    if (!p)
        p = get_node(key);
    else if (tr[p].key == key)
        tr[p].cnt++;
    else if (tr[p].key > key)
    {
        insert(tr[p].l, key);
        if (tr[tr[p].l].val > tr[p].val)
            zig(p);
    }
    else if (tr[p].key < key)
    {
        insert(tr[p].r, key);
        if (tr[tr[p].r].val > tr[p].val)
            zag(p);
    }
    pushup(p);
}

void remove(int &p, int key) //将需要删除的节点旋转到叶子节点，再删除
{
    if (!p)
        return;
    if (tr[p].key == key)
    {
        if (tr[p].cnt > 1)
            tr[p].cnt--;
        else if (tr[p].l || tr[p].r)
        {
            if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val)
            {
                zig(p);
                remove(tr[p].r, key);
            }
            else
            {
                zag(p);
                remove(tr[p].l, key);
            }
        }
        else
        {
            p = 0;
        }
    }
    else if (tr[p].key > key)
    {
        remove(tr[p].l, key);
    }
    else
    {
        remove(tr[p].r, key);
    }
    pushup(p);
}

int get_rank_by_key(int p, int key)
{
    if (!p)
        return 0;
    if (tr[p].key == key)
    {
        return tr[tr[p].l].size + 1;
    }
    if (tr[p].key > key)
        return get_rank_by_key(tr[p].l, key);
    return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r, key);
}

int get_key_by_rank(int p, int rank)
{
    if (!p)
        return INF;
    if (tr[tr[p].l].size >= rank)
        return get_key_by_rank(tr[p].l, rank);
    if (tr[tr[p].l].size + tr[p].cnt >= rank)
        {//cout<<tr[p].key<<endl;
        return tr[p].key;}
    return get_key_by_rank(tr[p].r, rank - tr[p].cnt - tr[tr[p].l].size);
}

int get_perv(int p, int key) //难想，重点复习
{
    //cout<<"!"<<tr[p].key<<endl;
    if (!p)
        return -INF;
    if (tr[p].key >= key)
        return get_perv(tr[p].l, key);
    return max(tr[p].key, get_perv(tr[p].r, key));
}

int get_next(int p, int key) //难想，重点复习
{
    if (!p)
        return INF;
    if (tr[p].key <= key)
        return get_next(tr[p].r, key);
    return min(tr[p].key, get_next(tr[p].l, key));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime =clock();
#endif
    build(); //初始化，建立哨兵,根节点；此时树中有两个节点。
    scanf("%d", &n);
    while (n--)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1)
            insert(root, x);
        else if (op == 2)
            remove(root, x);
        else if (op == 3)
            printf("%d\n", get_rank_by_key(root, x)-1);//减1是因为有哨兵存在
        else if (op == 4)
            printf("%d\n", get_key_by_rank(root, x+1));//同理，加1是因为有哨兵存在
        else if (op == 5)
            printf("%d\n", get_perv(root, x));
        else
        {
            printf("%d\n", get_next(root, x));
        }
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
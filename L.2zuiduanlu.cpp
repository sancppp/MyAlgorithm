#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <ctime>

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
const int N = 2000010, M = 1e4 + 10;

vector<int> lsh;

int cnt = 0, n, m;
int f[N], l[N], r[N], op[N], len;
int h[M << 1], e[M << 2], ne[M << 2], idx;
bool in_stack[N];
int out[N];
int color[N], stk[N], top, dfn[N], low[N], times, sizes[N], scc_cnt;

void init()
{
    init_h;
    times = 0;
    memset(dfn, 0, sizeof dfn);
    scc_cnt = 0;
}

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
    e[idx] = a;
    ne[idx] = h[b];
    h[b] = idx++;
}
void tarjan(int u)
{
    dfn[u] = low[u] = ++times;
    stk[++top] = u, in_stack[u] = true;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]); //û���⣡����
        }
        else if (in_stack[j])
        {
            low[u] = min(low[u], dfn[j]); //û���⣡������
        }
    }
    if (dfn[u] == low[u])
    {
        ++scc_cnt;
        int y;
        do
        {
            y = stk[top--];
            in_stack[y] = false;
            color[y] = scc_cnt;
            sizes[scc_cnt]++;
        } while (y != u);
    }
}

bool check(int x)
{
    init();
    //cout << x << ":" << endl;
    fir(i, 1, x)
    {
        if (op[i])
        {
            add(l[i], r[i] + len);
            add(r[i], l[i] + len);
        }
        else
        {
            add(l[i], r[i]);
            add(r[i] + len, l[i] + len);
        }
    }
    for (int i = 1; i <= len; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= len; i++)
    {
        //cout << color[i] << endl;
        if (color[i] == color[i + len])
            return 0;
    }
    return 1;
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
    fir(i, 1, m)
    {
        char tmp[10];
        scanf("%d%d%s", &l[i], &r[i], tmp);
        l[i]--;
        op[i] = (tmp[0] == 'o');
        lsh.push_back(l[i]);
        lsh.push_back(r[i]);
    }
    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
    len = lsh.size();
    fir(i, 1, m) //lsh
    {
        l[i] = lower_bound(lsh.begin(), lsh.end(), l[i]) - lsh.begin() + 1;
        r[i] = lower_bound(lsh.begin(), lsh.end(), r[i]) - lsh.begin() + 1;
    }
    int l = 0, r = m;
    int ans = m;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    cout << ans << endl;
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
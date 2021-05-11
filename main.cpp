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
    return query(xx, yy, zz) - query(xx, yy, z - 1) - query(xx, y - 1, zz) - query(x - 1, yy, zz) + query(xx, y - 1, z - 1) + query(x - 1, yy, z - 1) + query(x - 1, y - 1, zz) - query(x - 1, y - 1, z - 1);
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
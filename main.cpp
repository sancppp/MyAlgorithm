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
const int N = 1e5 + 10;
int n, m;
int a[N], b[N];
void init() {}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    scanf("%d%d", &n, &m);
    fir(i, 1, n) scanf("%d", &a[i]);
    fir(i, 1, m) scanf("%d", &b[i]);
    int j = 1;
    fir(i, 1, m)
    {
        if (a[j] == b[i])
            j++;
    }
    cout << (j == n + 1 ? "Yes" : "No") << endl;
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
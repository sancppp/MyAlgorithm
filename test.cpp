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
int n;
void init(){
    for(int i=1;i<=6;i++)
        printf("elldoe\n");
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    int T = 1;
    scanf("%d",&T);
    init();
    while (T--)
    {
        scanf("%d",&n);
        fir(i,1,n)
        {
            printf("%d ",i);
        }
        puts("");
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
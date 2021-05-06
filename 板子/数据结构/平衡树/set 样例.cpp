#include <bits/stdc++.h>

using namespace std;
//-----pre_def----
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define fir(i, a, b) for (int i = a; i <= b; i++)
#define rif(i, a, b) for (int i = a; i >= b; i--)
#define init_h memset(h, -1, sizeof h), idx = 0;
//---------------
//https://www.acwing.com/problem/content/267/
const int N = 1010;
int n,x;
int d[N];
set<int> s;
set<int>::iterator iter,temp;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    s.insert(INF);
    s.insert(-INF);
    cin>>n;
    int ans=0;
    fir(i,1,n)
    {
        cin>>x;
        if(s.size()==2)
        {
            ans+=x;
            s.insert(x);
        }
        else
        {
            iter = s.lower_bound(x);
            if(*iter != x)
            {
                temp=iter;
                temp--;
                ans+=min(abs(*temp-x),abs(*iter-x));
            }
            s.insert(x);
        }
        //cout<<ans<<endl;
    }
    cout<<ans<<endl;
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
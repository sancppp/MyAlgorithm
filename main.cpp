#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

double a[N], b[N];

int n, m, k, t;
struct cmp
{
    bool operator()(double a, double b) const
    {
        return a > b;
    }
};

double f(int x)
{ // x 个上午取室内
    //cout << x << ":" << endl;
    double ans = 0;
    multiset<double,cmp> q1, q2;
    for (int i = 1; i <= n; i++)
    {
        q1.insert(a[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        q2.insert(b[i]);
    }
    for (int i = 1; i <= x; i++)
    {
        double cur = *q1.begin();
        
        ans += cur;
        q1.erase(q1.begin());
        q1.insert(cur * 0.6);
    }
    for (int i = 1; i <= t - k - x; i++)
    {
        double cur = *q2.begin();
        
        ans += cur;
        q2.erase(q2.begin());
        q2.insert(cur * 0.6);
    }
    for (int i = 1; i <= k; i++)
    {
        if (*q1.begin() > *q2.begin() * 0.8)
        {
            double cur = *q1.begin();
            
            ans += cur;
            q1.erase(q1.begin());
            q1.insert(cur * 0.6);
        }
        else
        {
            double cur = *q2.begin();
            
            ans += cur * 0.8;
            q2.erase(q2.begin());
            q2.insert(cur * 0.6);
        }
    }
    return ans;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    scanf("%d %d %d %d", &n, &m, &t, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &a[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%lf", &b[i]);
    }
    int l = 0, r = t - k;
    while (l + 5 <= r)
    {
        int lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
        if (f(lmid) > f(rmid))
        {
            r = rmid;
        }
        else
        {
            l = lmid;
        }
    }
    double ans = 0;
    // cout << l << " " << r << "\n";
    for (int i = l; i <= r; i++)
    {
        ans = max(ans, f(i));
        // cout << f(i) << "\n";
    }
    printf("%.2f\n", ans);
    return 0;
}
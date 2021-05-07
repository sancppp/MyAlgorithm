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
struct node
{
    int l,r;
    bool operator < (const node & b)const{
        if(l!=b.l)  return l<b.l;
        return r<b.r;
    }
};

multiset<node> s; 
void init(){}
void print()
{
    for(auto t: s)
    {
        cout<<t.l<<" "<<t.r<<endl;
    }
    puts("");
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    s.insert({1,1});
    s.insert({1,1});
    s.insert({2,1});
    s.insert({1,-1});
    print();
    //只删除一个
    s.erase(s.find({1,1}));
    print();
    //删除全部相同的元素
    s.insert({1,1});
    s.erase({1,1});
    print();
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
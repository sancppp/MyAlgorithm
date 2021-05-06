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
//set支持二分搜索（lower_bound&&upper_bound）
//只需要重载小于号就行了
//内部实现：平衡二叉树
const int N = 1010;
int n, x;
int d[N];
struct node
{
    int l, r;
    bool operator<(const node &b) const
    {
        if (l != b.l)
            return l < b.l;
        return r < b.r;
    }
};

set<node> s;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    s.insert({1, 1});
    s.insert({1, 2});
    s.insert({9, 2});
    s.insert({-9, 2});
    node t = {1, 1};
    //基本函数
    s.insert({-9, -2});
    cout << s.empty() << endl;
    cout << s.size() << endl;
    cout << s.count(t) << endl;
    //元素删除
    //1,(常用)size_type erase(value) 移除set容器内元素值为value的所有元素，返回移除的元素个数
    //2,void erase(&pos) 移除pos位置上的元素，无返回值
    //3,void erase(&first, &last) 移除迭代区间[&first, &last)内的元素，无返回值
    //4,void clear()， 移除set容器内所有元素
    //set的遍历
    for (auto item : s)
    {
        cout << item.l << " " << item.r << endl;
    }
    //二分查找
    auto tt = *lower_bound(s.begin(), s.end(), t);
    cout << tt.l << "  " << tt.r << endl;
    tt = *upper_bound(s.begin(), s.end(), t);
    cout << tt.l << "  " << tt.r << endl;

    s.clear();
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
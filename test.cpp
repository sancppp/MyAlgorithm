#include<bits/stdc++.h>
// #define int long long
#define PI pair<int,int>
using namespace std;
const int N = 1e7 + 10;

int prime[N], cnt;

bool st[N];

void init() {
    for (int i = 2; i < N; i++) {
        if (!st[i]) {
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && 1ll * i * prime[j] < N; j++) {
            st[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

signed main(){
    init();
    for (int i = 1; i <= cnt; i++) {
        printf("%d\n", prime[i]);
    }
    return 0;
}

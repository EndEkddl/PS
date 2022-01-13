#define ll long long
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

int n;
vector<int> v[10];
int a[10], b[10], p[10], q[10];
bool vis[10];
ll ans[10];

ll gcd(ll a, ll b) {
    if (!b) return a;
    else return gcd(b, a % b);
}
void dfs(int curr, int prev, int num) {

    vis[curr] = 1;
    ans[curr] *= num;
    for (auto next : v[curr]) {
        if (next != prev && !vis[next]) dfs(next, curr, num);
    }

    return;
}
int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i] >> b[i] >> p[i] >> q[i]; // a:b = p:q <=> qa = pb
        v[a[i]].push_back(b[i]);
        v[b[i]].push_back(a[i]);
        ans[i] = 1; // 초기 값을 1로 설정
    }
    ans[n - 1] = 1; // 초기 값을 1로 설정

    for (int i = 0; i < n - 1; i++) {
        memset(vis, 0, sizeof(vis));
        dfs(a[i], b[i], p[i]); // a[i] 재료와 관련있는 재료들의 비율에 모두 p를 곱해줌
        dfs(b[i], a[i], q[i]); // b[i] 재료와 관련있는 재료들의 비율에 모두 q를 곱해줌
    }

    // 이대로 출력해도 비율 조건은 만족하지만, 재료의 질량을 더한 값이 최소라는 보장은 없음
    // 모든 재료의 비율의 최대공약수(GCD)를 구해 그것으로 나누어야 최소가 됨 
    ll GCD = ans[0];
    for (int i = 1; i < n; i++) GCD = gcd(GCD, ans[i]);

    for (int i = 0; i < n; i++) cout << ans[i] / GCD << ' ';

    return 0;
}
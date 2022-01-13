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
        ans[i] = 1; // �ʱ� ���� 1�� ����
    }
    ans[n - 1] = 1; // �ʱ� ���� 1�� ����

    for (int i = 0; i < n - 1; i++) {
        memset(vis, 0, sizeof(vis));
        dfs(a[i], b[i], p[i]); // a[i] ���� �����ִ� ������ ������ ��� p�� ������
        dfs(b[i], a[i], q[i]); // b[i] ���� �����ִ� ������ ������ ��� q�� ������
    }

    // �̴�� ����ص� ���� ������ ����������, ����� ������ ���� ���� �ּҶ�� ������ ����
    // ��� ����� ������ �ִ�����(GCD)�� ���� �װ����� ������� �ּҰ� �� 
    ll GCD = ans[0];
    for (int i = 1; i < n; i++) GCD = gcd(GCD, ans[i]);

    for (int i = 0; i < n; i++) cout << ans[i] / GCD << ' ';

    return 0;
}
#define MAX 1000000001
#define pii pair<int,int>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int n, a, b, ans = MAX;
vector<int> dist1, dist2;
vector<pii> edge;
vector<vector<pii>> g;
bool vis[100001];

void bfs1() {
    queue<pii> q;
    int x = a;
    vis[x] = 1;
    dist1[x] = 0;
    q.push({ x,0 });

    while (!q.empty()) {
        int curr = q.front().first;
        int cost = q.front().second; q.pop();

        for (auto next : g[curr]) {
            if (!vis[next.first] && dist1[next.first] > dist1[curr] + next.second) {
                dist1[next.first] = dist1[curr] + next.second;
                vis[next.first] = 1;
                q.push({ next.first, dist1[curr] + next.second });
            }
        }
    }

    return;
}
void bfs2() {
    queue<pii> q;
    int x = b;
    vis[x] = 1;
    dist2[x] = 0;
    q.push({ x,0 });

    while (!q.empty()) {
        int curr = q.front().first;
        int cost = q.front().second; q.pop();

        for (auto next : g[curr]) {
            if (!vis[next.first] && dist2[next.first] > dist2[curr] + next.second) {
                dist2[next.first] = dist2[curr] + next.second;
                vis[next.first] = 1;
                q.push({ next.first, dist2[curr] + next.second });
            }
        }
    }

    return;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> a >> b;
    if (a == b) { // ���� ó�� : �� �κ��� ���� ���� ������ �̵��ؾ� �� �Ÿ��� 0
        cout << "0\n";
        return 0;
    }
    dist1.resize(n + 1, MAX);
    dist2.resize(n + 1, MAX);
    g.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int x, y, cost; cin >> x >> y >> cost;
        edge.push_back({ x,y });
        g[x].push_back({ y, cost });
        g[y].push_back({ x, cost });
    }

    bfs1(); // a�κ��� �������� ��� ������� �Ÿ�(dist1)�� ����
    memset(vis, false, sizeof(vis));
    bfs2(); // b�κ��� �������� ��� ������� �Ÿ�(dist2)�� ����

    // ����� �� ��(start, end)�� ���ʷ� ���Ǹ�, a�� start���� �̵��ϰ�, b�� end���� �̵��ϴ� ���
    // b�� start���� �̵��ϰ�, a�� end���� �̵��ϴ� ��츦 ���� ��� �� �ּڰ��� ����
    for (int i = 0; i < n - 1; i++) {
        int start, end;
        start = edge[i].first;
        end = edge[i].second;
        ans = min(ans, dist1[start] + dist2[end]);
        ans = min(ans, dist2[start] + dist1[end]);
    }

    cout << ans;

    return 0;
}

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
    if (a == b) { // 예외 처리 : 두 로봇이 같은 곳에 있으면 이동해야 할 거리는 0
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

    bfs1(); // a로봇을 기준으로 모든 방까지의 거리(dist1)를 구함
    memset(vis, false, sizeof(vis));
    bfs2(); // b로봇을 기준으로 모든 방까지의 거리(dist2)를 구함

    // 통로의 양 끝(start, end)을 차례로 살피며, a가 start까지 이동하고, b가 end까지 이동하는 경우
    // b가 start까지 이동하고, a가 end까지 이동하는 경우를 각각 계산 후 최솟값을 저장
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

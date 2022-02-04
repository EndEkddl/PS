#define _CRT_SECURE_NO_WARNINGS
#define MAX 1000000000
#define pii pair<int,int>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int n, m;
int ans[201][201], dist[201][201];
vector<vector<pii>> v;

void dijkstra(int x) {

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	for (int i = 1; i <= n; i++) ans[x][i] = dist[x][i] = MAX;
	ans[x][x] = dist[x][x] = 0;
	pq.push({ 0,x });

	while (!pq.empty()) {
		int cost = pq.top().first;
		int curr = pq.top().second; pq.pop();
		for (auto& i : v[curr]) { // 'i' is v[curr][idx] where 0 <= idx < v[curr].size().
			int nCost = i.second;
			int nCurr = i.first;
			if (dist[x][nCurr] > dist[x][curr] + nCost) { // We found the shorter path from 'x' to 'nCurr'.
				dist[x][nCurr] = dist[x][curr] + nCost; // Renew the value.
				if (!ans[x][curr]) ans[x][nCurr] = nCurr; // Exception for the first vertex.
				else ans[x][nCurr] = ans[x][curr];
				pq.push({ dist[x][nCurr], nCurr });
			}
		}
	}

	return;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	v.resize(n + 1);

	while (m--) {
		int a, b, cost; cin >> a >> b >> cost;
		v[a].push_back({ b,cost });
		v[b].push_back({ a,cost });
	}
	for (int i = 1; i <= n; i++) dijkstra(i);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) cout << "- ";
			else cout << ans[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}
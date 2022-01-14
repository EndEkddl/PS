#define _CRT_SECURE_NO_WARNINGS
#define MAX 1000001
#define MOD 10000
#define pii pair<int,int>
#define ll long long
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
#include <climits>
#include <queue>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <regex>

using namespace std;
int n, cnt;
vector<vector<int>> v;
int score = MAX;
vector<int> ans;
int vis[51];

int bfs(int x) {
	int ret = 0;
	queue<int> q;
	q.push(x);
	vis[x] = 1;

	while (!q.empty()) {
		int curr = q.front(); q.pop();
		ret = max(ret, vis[curr]);
		for (auto& i : v[curr]) {
			if (!vis[i]) {
				q.push(i);
				vis[i] = vis[curr] + 1; // Save the friend score
			}
		}
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	v.resize(n + 1);

	while (1) {
		int a, b; cin >> a >> b;
		if (a == -1 && b == -1) break;
		v[a].push_back(b);
		v[b].push_back(a);
	}

	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis)); // Initialization of vis array
		int tmp = bfs(i);
		if (score > tmp) { 
			score = tmp;
			vector<int>().swap(ans); // Empty the ans vector
			ans.push_back(i);
		}
		else if (score == tmp) ans.push_back(i); // Add the candidate 
	}

	cout << score-1 << ' ' << ans.size() << '\n';
	for (int i = 0; i < ans.size(); i++) cout << ans[i] << ' ';

	return 0;
}
// 위상 정렬 : 순서가 정해져있는 작업을 차례로 수행할 때 순서 결정을 위한 알고리즘

#define _CRT_SECURE_NO_WARNINGS
#define MAX 1000000000
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

int n, m;
int indegree[32001]; // 위상 정렬
vector<vector<int>> v;
priority_queue<int, vector<int>, greater<int>> pq; // 가능하면 쉬운 문제부터 풀기 위해

int main() {

	cin >> n >> m;
	v.resize(n + 1);

	while (m--) {
		int a, b; cin >> a >> b;
		v[a].push_back(b);
		indegree[b]++;
	}

	for (int i = 1; i <= n; i++) {
		if (!indegree[i]) pq.push(i); // i번 문제보다 먼저 풀어야 하는 문제가 없으면 pq에 삽입
	}

	while (!pq.empty()) {
		int top = pq.top(); pq.pop();
		cout << top << ' ';

		for (auto i : v[top]) { // top번 문제 이후에 풀어야 했던 문제들의 indegree 1 감소
			if (indegree[i]) {
				indegree[i]--;
				if (!indegree[i]) pq.push(i); // 제약 없으면 pq에 삽입
			}
		}
	}

	return 0;
}

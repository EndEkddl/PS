// ���� ���� : ������ �������ִ� �۾��� ���ʷ� ������ �� ���� ������ ���� �˰���

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
int indegree[32001]; // ���� ����
vector<vector<int>> v;
priority_queue<int, vector<int>, greater<int>> pq; // �����ϸ� ���� �������� Ǯ�� ����

int main() {

	cin >> n >> m;
	v.resize(n + 1);

	while (m--) {
		int a, b; cin >> a >> b;
		v[a].push_back(b);
		indegree[b]++;
	}

	for (int i = 1; i <= n; i++) {
		if (!indegree[i]) pq.push(i); // i�� �������� ���� Ǯ��� �ϴ� ������ ������ pq�� ����
	}

	while (!pq.empty()) {
		int top = pq.top(); pq.pop();
		cout << top << ' ';

		for (auto i : v[top]) { // top�� ���� ���Ŀ� Ǯ��� �ߴ� �������� indegree 1 ����
			if (indegree[i]) {
				indegree[i]--;
				if (!indegree[i]) pq.push(i); // ���� ������ pq�� ����
			}
		}
	}

	return 0;
}

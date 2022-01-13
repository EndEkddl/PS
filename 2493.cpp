#define _CRT_SECURE_NO_WARNINGS
#define MAX 1000000001
#define pii pair<int,int>
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	stack<pii> s; // {value, idx}
	cin >> n;
	s.push({ MAX,0 }); // For case that no tower can receive the signal.

	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		// Pop the stack until you find the receiving tower.
		while (s.top().first < x) {
			s.pop();
		}
		cout << s.top().second << ' ';
		s.push({ x,i });
	}
	return 0;
}
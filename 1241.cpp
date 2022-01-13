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

int n;
int cnt[MAX];
vector<int> v;

int main() {

	cin >> n;
	v.resize(n + 1);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		cnt[v[i]]++;
	}

	for (int i = 0; i < n; i++) {
		int sum = 0;
		int idx = sqrt(v[i]);
		for (int j = 1; j <= idx; j++) {
			if (v[i] % j == 0) {// Finding the divisor of v[i]
				sum += cnt[j]; 
				if (j * j != v[i]) sum += cnt[v[i] / j]; // Finding the other divisor of v[i] excluding the square number
			}
		}
		cout << sum - 1 << '\n'; // Subtract 1 becuase of excluding the number itself
	}

	return 0;
}

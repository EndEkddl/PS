#define WALL 1
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL 2
#define ll long long
#include <iostream>

using namespace std;

int n, dir = HORIZONTAL;
int arr[33][33];
ll dp[33][33][3];

int main() {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) cin >> arr[i][j];
	}

	dp[1][2][HORIZONTAL] = 1;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (arr[i][j + 1] != WALL) dp[i][j + 1][HORIZONTAL] += dp[i][j][HORIZONTAL] + dp[i][j][DIAGONAL];
			if (arr[i + 1][j] != WALL) dp[i + 1][j][VERTICAL] += dp[i][j][VERTICAL] + dp[i][j][DIAGONAL];
			if (arr[i + 1][j + 1] != WALL && arr[i + 1][j] != WALL && arr[i][j + 1] != WALL) dp[i + 1][j + 1][DIAGONAL] += dp[i][j][VERTICAL] + dp[i][j][HORIZONTAL] + dp[i][j][DIAGONAL];
		}
	}

	cout << dp[n][n][DIAGONAL] + dp[n][n][VERTICAL] + dp[n][n][HORIZONTAL];

	return 0;
}
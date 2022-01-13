#define _CRT_SECURE_NO_WARNINGS
#define MAX 1000000000
#define MOD 10000
#define HORIZONTAL 0
#define VERTICAL 1
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
using namespace std;

typedef struct _loc{
	int y, x, dir;
}loc;
int n, ans;
loc target, start;
bool sFlag, tFlag;
char arr[51][51];
bool vis[51][51][2]; //vis[row][col][dir] (dir : HORIZONTAL, VERTICAL)
int dy[8] = { 1,-1,0,0,-1,-1,1,1 };
int dx[8] = { 0,0,1,-1,-1,1,-1,1 };

bool canMove(int dir, int y, int x) {

	int step = 1;
	if (dir == HORIZONTAL) { // 통나무가 수평 방향으로 놓여있는 경우
		for (int i = 0; i < 2; i++) { // 통나무 중심점을 기준으로 양 옆에 벌채되지 않은 나무가 있는지 확인
			int nx = x + step;
			if (nx < 0 || nx >= n || arr[y][nx] == '1') return false; // 이동 불가
			step *= -1;
		}
	}
	else {// 통나무가 수직 방향으로 놓여있는 경우
		for (int i = 0; i < 2; i++) { // 통나무 중심점을 기준으로 위 아래에 벌채되지 않은 나무가 있는지 확인
			int ny = y + step;
			if (ny < 0 || ny >= n || arr[ny][x] == '1') return false; // 이동 불가
			step *= -1;
		}
	}


	return true; // 이동 가능
}

bool canRotate(int y, int x) {

	for (int i = 0; i < 8; i++) { // 통나무의 중심점을 기준으로 3*3 정사각형 구역에 나무가 있는지 확인
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= n || nx >= n || arr[ny][nx] == '1') return false;// 회전 불가
	}

	return true; // 회전 가능
}

bool bfs() {

	queue<pair<pii, int>> q; // {{y,x},dir}
	q.push({ { start.y, start.x }, start.dir });
	vis[start.y][start.x][start.dir] = 1;

	int prev = 0, post = 1;
	while (!q.empty()) {
		int size = post - prev; // 최소 동작 횟수를 저장하기 위해 큐의 크기를 저장
		prev = q.size();
		post = prev;
		for (int j = 0; j < size; j++) {
			int y = q.front().first.first;
			int x = q.front().first.second;
			int dir = q.front().second; q.pop();
			if (y == target.y && x == target.x && dir == target.dir) return true; // 통나무 옮기기 성공

			for (int i = 0; i < 4; i++) { // 상하좌우로 통나무를 옮길 수 있는지 확인
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= n || vis[ny][nx][dir] || arr[ny][nx] == '1') continue;
				if (canMove(dir, ny, nx)) { 
					q.push({ {ny,nx}, dir });
					post++;
					vis[ny][nx][dir] = 1;
				}
			}
			// 현재 위치에서 통나무를 회전시킬 수 있는지 확인
			int ndir = (dir) ? 0 : 1;
			if (!vis[y][x][ndir] && canRotate(y, x)) {
				q.push({ {y,x}, ndir });
				post++;
				vis[y][x][ndir] = 1;
			}
		}
		ans++;
	}

	return false; // 통나무 옮기기 실패
}

int main() {

	cin >> n;
	for (int i = 0; i < n; i++) {
		string str; cin >> str;
		for (int j = 0; j < n; j++) {
			arr[i][j] = str[j];
			if (arr[i][j] == 'E') { // 최종 목적지 통나무의 중심점 및 방향을 저장
				if (!tFlag) tFlag = 1; 
				else {
					target.y = i;
					target.x = j;
					if (arr[i][j - 1] == 'E') target.dir = HORIZONTAL;
					else target.dir = VERTICAL;
					tFlag = 0;
				}
			}
			if (arr[i][j] == 'B') {// 시작 지점 통나무의 중심점 및 방향을 저장
				if (!sFlag) sFlag = 1;
				else {
					start.y = i;
					start.x = j;
					if (arr[i][j - 1] == 'B') start.dir = HORIZONTAL;
					else start.dir = VERTICAL;
					sFlag = 0;
				}
			}
		}
	}

	if (bfs()) cout << ans;
	else cout << "0\n";

	return 0;
}

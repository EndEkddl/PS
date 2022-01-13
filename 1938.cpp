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
	if (dir == HORIZONTAL) { // �볪���� ���� �������� �����ִ� ���
		for (int i = 0; i < 2; i++) { // �볪�� �߽����� �������� �� ���� ��ä���� ���� ������ �ִ��� Ȯ��
			int nx = x + step;
			if (nx < 0 || nx >= n || arr[y][nx] == '1') return false; // �̵� �Ұ�
			step *= -1;
		}
	}
	else {// �볪���� ���� �������� �����ִ� ���
		for (int i = 0; i < 2; i++) { // �볪�� �߽����� �������� �� �Ʒ��� ��ä���� ���� ������ �ִ��� Ȯ��
			int ny = y + step;
			if (ny < 0 || ny >= n || arr[ny][x] == '1') return false; // �̵� �Ұ�
			step *= -1;
		}
	}


	return true; // �̵� ����
}

bool canRotate(int y, int x) {

	for (int i = 0; i < 8; i++) { // �볪���� �߽����� �������� 3*3 ���簢�� ������ ������ �ִ��� Ȯ��
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= n || nx >= n || arr[ny][nx] == '1') return false;// ȸ�� �Ұ�
	}

	return true; // ȸ�� ����
}

bool bfs() {

	queue<pair<pii, int>> q; // {{y,x},dir}
	q.push({ { start.y, start.x }, start.dir });
	vis[start.y][start.x][start.dir] = 1;

	int prev = 0, post = 1;
	while (!q.empty()) {
		int size = post - prev; // �ּ� ���� Ƚ���� �����ϱ� ���� ť�� ũ�⸦ ����
		prev = q.size();
		post = prev;
		for (int j = 0; j < size; j++) {
			int y = q.front().first.first;
			int x = q.front().first.second;
			int dir = q.front().second; q.pop();
			if (y == target.y && x == target.x && dir == target.dir) return true; // �볪�� �ű�� ����

			for (int i = 0; i < 4; i++) { // �����¿�� �볪���� �ű� �� �ִ��� Ȯ��
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= n || vis[ny][nx][dir] || arr[ny][nx] == '1') continue;
				if (canMove(dir, ny, nx)) { 
					q.push({ {ny,nx}, dir });
					post++;
					vis[ny][nx][dir] = 1;
				}
			}
			// ���� ��ġ���� �볪���� ȸ����ų �� �ִ��� Ȯ��
			int ndir = (dir) ? 0 : 1;
			if (!vis[y][x][ndir] && canRotate(y, x)) {
				q.push({ {y,x}, ndir });
				post++;
				vis[y][x][ndir] = 1;
			}
		}
		ans++;
	}

	return false; // �볪�� �ű�� ����
}

int main() {

	cin >> n;
	for (int i = 0; i < n; i++) {
		string str; cin >> str;
		for (int j = 0; j < n; j++) {
			arr[i][j] = str[j];
			if (arr[i][j] == 'E') { // ���� ������ �볪���� �߽��� �� ������ ����
				if (!tFlag) tFlag = 1; 
				else {
					target.y = i;
					target.x = j;
					if (arr[i][j - 1] == 'E') target.dir = HORIZONTAL;
					else target.dir = VERTICAL;
					tFlag = 0;
				}
			}
			if (arr[i][j] == 'B') {// ���� ���� �볪���� �߽��� �� ������ ����
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

#define BLACK 0
#define WHITE 1
#define pii pair<int,int>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

int n, black, white, len;
int arr[10][10];
bool color[10][10];
bool vis[10][10];
int dx[2] = { -1,1 };
int dy[2] = { -1,-1 };
vector<pii> v;

// (y,x)에 비숍을 놓을 때 왼쪽 위, 오른쪽 위 대각선에 비숍이 놓여있는지 확인
bool canGo(int y, int x) {
    for (int i = 0; i < 2; i++) {
        int ny = y, nx = x;
        while (1) {
            if (ny < 0 || nx < 0 || ny >= n || nx >= n) break;
            if (vis[ny][nx]) return false;
            ny += dy[i]; nx += dx[i];
        }
    }

    return true;
}

void go(int idx, int cnt, int flag) {
    if (idx >= len) return;

    if (flag == BLACK && black < cnt) black = cnt;
    else if (flag == WHITE && white < cnt) white = cnt;

    for (int i = idx; i < len; i++) {
        int y = v[i].first;
        int x = v[i].second;
        if (color[y][x] != flag || !canGo(y, x)) continue; // 체스판 색깔이 다르거나 비숍을 놓을 수 없는 경우
        vis[y][x] = 1;
        go(i, cnt + 1, flag);
        vis[y][x] = 0;
    }

    return;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            if (arr[i][j]) v.push_back({ i,j });
            if ((i % 2) && (j % 2)) color[i][j] = WHITE;
            else if (!(i % 2) && !(j % 2)) color[i][j] = WHITE;
        }
    }
    len = v.size();

    go(0, 0, BLACK);
    go(0, 0, WHITE);

    cout << black + white;

    return 0;
}

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <iomanip>

using namespace std;
#define X first
#define Y second // pair에서 first, second를 줄여서 쓰기 위해서 사용

string board[1002];
int T_F[1002][1002];
int T_J[1002][1002];
int n, m;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 }; // 상하좌우 네 방향을 의미


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		fill(T_J[i], T_J[i] + m, -1);
		fill(T_F[i], T_F[i] + m, -1);
	}

	for (int i = 0; i < n; i++) {
		cin >> board[i];
	}
	queue<pair<int, int>> Q_J;
	queue<pair<int, int>> Q_F;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 'F') {
				T_F[i][j] = 0;
				Q_F.push({ i, j }); // 이중 포문 돌 때, 미리 Q_F에 F 푸쉬
			}
			else if (board[i][j] == 'J') {
				T_J[j][j] = 0;
				Q_J.push({ i, j });
			}
		}
	}

	// F먼저 BFS
	while (!Q_F.empty()) {
		auto cur = Q_F.front();
		Q_F.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (board[nx][ny] == '#' || T_F[nx][ny] >= 0) continue; // #이 아니고, 방문한 적이 없으면 불 전파 가능 
			T_F[nx][ny] = T_F[cur.X][cur.Y] + 1;
			Q_F.push({ nx, ny });
		}
	}

	while (!Q_J.empty()) {
		auto cur = Q_J.front(); Q_J.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
				cout << T_J[cur.X][cur.Y] + 1;
				return 0;
			}
			if (T_J[nx][ny] >= 0 || board[nx][ny] == '#') continue;
			if (T_F[nx][ny] != -1 && T_F[nx][ny] <= T_J[cur.X][cur.Y] + 1) continue;
			/*if (board[nx][ny] == '.' && T_J[nx][ny] < 0 &&
				(T_J[cur.X][cur.Y] + 1 < T_F[nx][ny])) {*/
			T_J[nx][ny] = T_J[cur.X][cur.Y] + 1;
			Q_J.push({ nx, ny });
			// }
		}
	}

	cout << "IMPOSSIBLE";
	return 0;
}

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
#include<iomanip>
using namespace std;
#define X first
#define Y second // pair에서 first, second를 줄여서 쓰기 위해서 사용

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 }; // 상하좌우 네 방향을 의미

bool board[502][502];
bool vis[502][502]; // 해당 칸을 방문했는지 여부를 저장


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}

	vector<int> paint;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (vis[i][j] || !board[i][j]) continue;
			queue<pair<int, int> > Q;
			vis[i][j] = 1;
			Q.push({ i,j });
			int size = 0;

			while (!Q.empty()) {
				size++;
				pair<int, int> cur = Q.front();
				Q.pop();

				for (int dir = 0; dir < 4; dir++) { // 상하좌우 칸을 살펴볼 것이다. dir = 0, 1, 2, 3
					int nx = cur.X + dx[dir];
					int ny = cur.Y + dy[dir]; // nx, ny에 dir에서 정한 방향의 인접한 칸의 좌표가 들어감
					if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // 범위 밖일 경우 넘어감
					if (vis[nx][ny] || board[nx][ny] != 1) continue; // 이미 방문한 칸이거나 파란 칸이 아닐 경우
					vis[nx][ny] = 1; // (nx, ny)를 방문했다고 명시
					Q.push({ nx,ny });
				}
			}
			paint.push_back(size);
		}
	}

	int max = 0;
	if (!paint.empty()) // 이거 체크 안해줘서 런타임에러 났었음 => 스택을 사용할 땐, 항상 비어있는지 체크 
		max = *max_element(paint.begin(), paint.end());

	cout << paint.size() << "\n" << max;

	return 0;
}
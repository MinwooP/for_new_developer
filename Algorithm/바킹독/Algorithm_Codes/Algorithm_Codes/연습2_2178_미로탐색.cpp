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
#include <tuple>
using namespace std;
#define X first
#define Y second // pair���� first, second�� �ٿ��� ���� ���ؼ� ���


string board[102];
int dist[102][102]; // �ش� ĭ�� �湮�ߴ��� ���θ� ����
int n, m; // n = ���� ��, m = ���� ��

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 }; // �����¿� �� ������ �ǹ�

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	queue<pair<int, int>> Q;

	cin >> n >> m;

	for (int i = 0; i < n; i++)
		cin >> board[i];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			dist[i][j] = -1;
		}
	}

	dist[0][0] = 0; // (0, 0)�� �湮�ߴٰ� ���
	Q.push({ 0,0 }); // ť�� �������� (0, 0)�� ����.

	while (!Q.empty()) {
		pair<int, int> cur = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) { // �����¿� ĭ�� ���캼 ���̴�. dir = 0, 1, 2, 3
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir]; // nx, ny�� dir���� ���� ������ ������ ĭ�� ��ǥ�� ��
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // ���� ���� ��� �Ѿ
			if (dist[nx][ny] != -1 || board[nx][ny] != '1') continue; // �̹� �湮�� ĭ�̰ų� �Ķ� ĭ�� �ƴ� ���
			dist[nx][ny] = dist[cur.X][cur.Y] + 1; // (nx, ny)�� �湮�ߴٰ� ���
			Q.push({ nx,ny });
		}
	}

	cout << dist[n - 1][m - 1] + 1; // ������ �������� ������ �����Ѵٰ� ������ �����Ǿ������Ƿ� 
	return 0;
}
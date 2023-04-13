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
#define Y second // pair���� first, second�� �ٿ��� ���� ���ؼ� ���

int times[1000][1000]; // �ش� ĭ�� �湮�ߴ��� ���θ� ����
int n, m;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 }; // �����¿� �� ������ �ǹ�

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> m >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> times[i][j];
		}
	}

	queue<pair<int, int> > Q;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (times[i][j] == 1) {
				Q.push({ i,j });
			}
		}
	}

	while (!Q.empty()) {
		pair<int, int> cur = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) { // �����¿� ĭ�� ���캼 ���̴�. dir = 0, 1, 2, 3
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir]; // nx, ny�� dir���� ���� ������ ������ ĭ�� ��ǥ�� ��

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // ���� ���� ��� �Ѿ

			if (times[nx][ny] == 0) {
				times[nx][ny] = times[cur.X][cur.Y] + 1;
				Q.push({ nx,ny });
			}
			else
				continue;
		}
	}


	int max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (times[i][j] == 0) {
				cout << -1;
				return 0;
			}
			if (max < times[i][j])
				max = times[i][j];
		}
	}

	cout << max - 1;
	return 0;
}
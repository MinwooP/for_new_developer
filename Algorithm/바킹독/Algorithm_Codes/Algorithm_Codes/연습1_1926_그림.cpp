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

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 }; // �����¿� �� ������ �ǹ�

bool board[502][502];
bool vis[502][502]; // �ش� ĭ�� �湮�ߴ��� ���θ� ����


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

				for (int dir = 0; dir < 4; dir++) { // �����¿� ĭ�� ���캼 ���̴�. dir = 0, 1, 2, 3
					int nx = cur.X + dx[dir];
					int ny = cur.Y + dy[dir]; // nx, ny�� dir���� ���� ������ ������ ĭ�� ��ǥ�� ��
					if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // ���� ���� ��� �Ѿ
					if (vis[nx][ny] || board[nx][ny] != 1) continue; // �̹� �湮�� ĭ�̰ų� �Ķ� ĭ�� �ƴ� ���
					vis[nx][ny] = 1; // (nx, ny)�� �湮�ߴٰ� ���
					Q.push({ nx,ny });
				}
			}
			paint.push_back(size);
		}
	}

	int max = 0;
	if (!paint.empty()) // �̰� üũ �����༭ ��Ÿ�ӿ��� ������ => ������ ����� ��, �׻� ����ִ��� üũ 
		max = *max_element(paint.begin(), paint.end());

	cout << paint.size() << "\n" << max;

	return 0;
}
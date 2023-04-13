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

string M[1000]; // 해당 칸을 방문했는지 여부를 저장
int n, m;
int T[1000][1000];

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 }; // 상하좌우 네 방향을 의미


int main() 
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	for (int i = 0; i < n; i++) { 
		cin >> M[i];
	} 

	queue<pair<int, int>> Q;

	// F보다 J를 먼저 큐에 push => 각 DEPTH에서 J가 F보다 이동해야 하기 때문에  
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (M[i][j] == 'J') {
				Q.push({ i, j });
				T[i][j] = 1;
				break;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (M[i][j] == 'F') {
				Q.push({ i, j });
			}
		}
	}

	// # . J  F  
	while (!Q.empty()) { // 이 전체가 한 DEPTH? => NO
		pair<int, int> cur = Q.front();
		Q.pop();

		if ((M[cur.X][cur.Y] == 'J') &&
			cur.X == n - 1 || cur.X == 0 || cur.Y == m - 1 || cur.Y == 0) {
			cout << T[cur.X][cur.Y];
			return 0;
		}
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];	
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				
			if (M[cur.X][cur.Y] == 'J') { // 
				if (M[nx][ny] == '.') {
					M[nx][ny] = 'J';
					Q.push({ nx, ny });
					T[nx][ny] = T[cur.X][cur.Y] + 1;
				}
				else if (M[nx][ny] == '#' || M[nx][ny] == 'F' || M[nx][ny] == 'J')
					continue;
			}
			else { // 'F'
				if (M[nx][ny] == '.' || M[nx][ny] == 'J') {
					M[nx][ny] = 'F';
					Q.push({ nx, ny });
				}
				else {
					continue;
				}
			}
		}
	}

	cout << "IMPOSSIBLE";
	return 0;
}


//J의 개수를 실시간으로 셀 수 없을까 ?  => j가 없으면 끝내기 리턴하기 
//F가 J를 만났을 대도 J를 F로 변경해줘야 하나?
//시간 세는 변수 추가 완료 
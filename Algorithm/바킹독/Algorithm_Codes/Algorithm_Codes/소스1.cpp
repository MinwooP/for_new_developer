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

int T[1000001];
int dx[2] = {1,-1};

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, K;
	cin >> N >> K;  // K를 찾는 것.

	queue<int> Q;

	for (int i = 0; i <= 1000001; i++) {
		T[i] = -1;
	}

	T[N] = 0; 
	Q.push(N);

	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();

		//cout << cur << ' ' << T[cur] << endl;
		
		if (cur == K) {
			cout << T[cur];
			return 0;
		}

		for (int dir = 0; dir < 3; dir++) { // 상하좌우 칸을 살펴볼 것이다. dir = 0, 1, 2, 3
			int nx;
			if (dir == 2)
				nx = cur * 2; // *2
			else
				nx = cur + dx[dir]; // +1 or -1

			if (nx < 0 || nx > 100000) continue; // 범위 밖일 경우 넘어감
			if (T[nx] >= 0) continue; // 이미 방문한 칸인 경우 넘어감
			T[nx] = T[cur] + 1; // (nx, ny)를 방문했다고 명시
			Q.push(nx);
		}
	}

	return 0;
}

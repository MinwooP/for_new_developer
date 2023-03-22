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
#include<list>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	stack<pair<int, int>> S;

	int N;
	cin >> N;

	S.push(make_pair(100000001, 0));

	for (int i = 1; i <= N; i++) {

		int height;
		cin >> height;

		while (S.top().first < height)
			S.pop();

		cout << S.top().second << " ";

		S.push(make_pair(height, i));
	}
	return 0;
}


// pair를 사용하는 이유 

// 현재의 높이보다 더 큰 높이(신호가 도달할 수 있는 높이)가 나올때까지 스택을 pop 한다.  

// 왼쪽에 있는 수들 중 현재 수보다 큰 수들 중 가장 가까이 있는 수의 index		
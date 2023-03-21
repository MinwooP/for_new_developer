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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	stack<int> S;

	int N;
	cin >> N;
	while (N--) {
		int num;
		cin >> num;
		if (num == 0) {
			S.pop();
		}
		else
			S.push(num);
	}
	int sum = 0;
	while (!S.empty()) {
		sum += S.top();
		S.pop();
	}
	cout << sum;
	return 0;
}

// 이 문제가 stack을 사용해야 하는 이유
// 0을 입력하면 바로 전에 입력한 수를 지우고, 또 차례대로 넣으면 되기 때문에
// 한쪽으로만 넣는 stack의 구조가 활용되기 좋음
// 또 나중에 합을 구할 때는 어느쪽부터 더하는지도 상관없기 때문에 

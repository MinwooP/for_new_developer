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

	int N;
	stack<int> S;
	stack<int> T;


	cin >> N;
	int num = 0;
	while (N--) {
		cin >> num;
		S.push(num);
	}

	int ans = 0;

	while (S.size() > 1) { // S�� ����� 2��1 �ɶ����� �ݺ� ? 
		int current = S.top();
		S.pop();

		int max = S.top();
		T.push(S.top());
		S.pop();
		ans++;

		if (S.empty()) {
			break;
		}

		if (current < max) {
			S.push(T.top());
			T.pop();
			continue;
		}

		while (!S.empty()) { // ���� �� �� ����
			if (S.top() >= max) {
				ans++;
				max = S.top();
			}

			if (S.top() > current) {
				break;
			}

			T.push(S.top());
			S.pop();
		}

		while (!T.empty()) {
			S.push(T.top());
			T.pop();
		}
	}

	cout << ans;

	return 0;
}

// 2 4 1 2 2 5 1 
// 10 


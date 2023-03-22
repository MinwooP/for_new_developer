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

	stack<int> S;
	list<int> L;
	vector<char> ans;
	int N;

	cin >> N;
	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		L.push_back(num);
	}

	int idx = 1;

	while (!L.empty()) {
		if (S.empty()) {
			S.push(idx++);
			ans.push_back('+');
		}
		else {
			if (S.top() > L.front()) {
				cout << "NO";
				return 0;
			}

			while (S.top() < L.front()) {
				S.push(idx++);
				ans.push_back('+');
			}

			if (S.top() == L.front()) {
				S.pop();
				L.pop_front();
				ans.push_back('-');
			}
		}
	} 

	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << '\n';
	}

	return 0;
}

// pop을 통해 얻어야 하는 숫자보다 top이 항상 같거나 작아야 함. 

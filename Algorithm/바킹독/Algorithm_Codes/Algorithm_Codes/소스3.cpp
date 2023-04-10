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
	long long ans = 0;
	stack<int> S;

	cin >> N;
	long long num = 0;

	while (N--) {
		cin >> num;
		if (S.empty()) { // 맨 처음 수는 바로 스택에 넣어줌. 
			S.push(num);
			continue;
		}	
		else if (num < S.top()) {
			ans++;
			S.push(num);
		}
		else {
			ans += S.size();

			while (!S.empty() && S.top() < num) {
				S.pop();
			}

			S.push(num);
		}
	}

	cout << ans;
	return 0;
}

// 2 4 1 2 2 5 1 
// 10 




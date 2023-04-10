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

#define X first
#define Y second

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N;
	long long ans = 0;
	stack<pair<int, int>> S;
	
	cin >> N;
	long long num = 0;

	while (N--) {
		cin >> num;		
		int cnt = 1;
		if (S.empty()) { // 맨 처음 수는 바로 스택에 넣어줌. 
			S.push({ num, cnt });
			continue;
		}
		else if(num < S.top().X) {
			ans++;
			S.push({ num,  cnt });
		}
		else {
			while (!S.empty() && S.top().X <= num) {
				ans += S.top().Y;
				if (S.top().X == num)
					cnt += S.top().Y;
				S.pop();
			}
			if (!S.empty()) ans++;
			S.push({ num, cnt });
		}
	}

	cout << ans;
	return 0;
}

// 2 4 1 2 2 5 1 
// 10 


// 왜 ans가 long long 이어야 할까 ?
// 같은 수 계속 push하지 않고 stack을 pair로 저장 
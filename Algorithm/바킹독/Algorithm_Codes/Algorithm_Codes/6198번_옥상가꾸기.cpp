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
	cin >> N;

	long long ans = 0;
	stack<int> S;

	int height;
	while (N--) {
		cin >> height;

		while (!S.empty() && S.top() <= height) {
			S.pop();
		}

		ans += S.size();

		S.push(height);
	}
	cout << ans;

	return 0;
}


// 각 height을 입력받을 때마다, 현재까지 쌓여진 스택에서 그 height의 건물을 바라볼 수 있는 건물들(입력받은 height보다 큰 값을 가지는 건물들)
// 만 놔두고, 그 건물을 바라볼 수 없는 건물들(입력받은 height보다 작은 값을 가지는 건물들)은 pop 한다.(현재 건물을 바라볼 수 없다면, 그 오른쪽의 건물
// 들도 바라볼 수 없을 것이므로 pop해버려도 됨. 그러면 stack에는 그 height의 건물을 바라볼 수 있는 건물들만 남아있을 것이므로 이때의 stack의 size를 ans에 더해주고, 
// height을 stack에 push한다. 

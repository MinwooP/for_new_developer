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


// �� height�� �Է¹��� ������, ������� �׿��� ���ÿ��� �� height�� �ǹ��� �ٶ� �� �ִ� �ǹ���(�Է¹��� height���� ū ���� ������ �ǹ���)
// �� ���ΰ�, �� �ǹ��� �ٶ� �� ���� �ǹ���(�Է¹��� height���� ���� ���� ������ �ǹ���)�� pop �Ѵ�.(���� �ǹ��� �ٶ� �� ���ٸ�, �� �������� �ǹ�
// �鵵 �ٶ� �� ���� ���̹Ƿ� pop�ع����� ��. �׷��� stack���� �� height�� �ǹ��� �ٶ� �� �ִ� �ǹ��鸸 �������� ���̹Ƿ� �̶��� stack�� size�� ans�� �����ְ�, 
// height�� stack�� push�Ѵ�. 

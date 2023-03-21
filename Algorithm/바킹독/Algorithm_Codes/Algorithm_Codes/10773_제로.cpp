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

// �� ������ stack�� ����ؾ� �ϴ� ����
// 0�� �Է��ϸ� �ٷ� ���� �Է��� ���� �����, �� ���ʴ�� ������ �Ǳ� ������
// �������θ� �ִ� stack�� ������ Ȱ��Ǳ� ����
// �� ���߿� ���� ���� ���� ����ʺ��� ���ϴ����� ������� ������ 

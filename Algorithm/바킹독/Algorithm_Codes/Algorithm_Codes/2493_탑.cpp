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


// pair�� ����ϴ� ���� 

// ������ ���̺��� �� ū ����(��ȣ�� ������ �� �ִ� ����)�� ���ö����� ������ pop �Ѵ�.  

// ���ʿ� �ִ� ���� �� ���� ������ ū ���� �� ���� ������ �ִ� ���� index		
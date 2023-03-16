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

	int N, X;
	vector<int> v;

	cin >> N;
	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		v.push_back(num);
	}
	cin >> X;

	bool occur[200000] = { 0 };
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		if (X - v[i] > 0 && occur[X - v[i]] == 1) {
			cnt++;
		}
		occur[v[i]] = 1;
	}

	cout << cnt;

	return 0;
}
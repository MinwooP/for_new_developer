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

	int N = 0;
	int call[20];

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> call[i];
	}
	
	int Y = 0;
	for (int i = 0; i < N; i++) {
		int remain = call[i] / 30;
		Y = Y + 10 * (1 + remain);
	}

	int M = 0;
	for (int i = 0; i < N; i++) {
		int remain = call[i] / 60;
		M = M + 15 * (1 + remain);
	}

	if (M == Y) {
		cout << "Y M " << M;
	}
	else if (Y < M) {
		cout << "Y " << Y;
	}
	else {
		cout << "M " << M;
	}

	return 0;
}
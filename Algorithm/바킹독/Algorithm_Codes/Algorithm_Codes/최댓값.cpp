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

	int num[9];
	for (int i = 0; i < 9; i++) {
		cin >> num[i];
	}
	
	int max = 0;
	int maxIndex = -1;
	for (int i = 0; i < 9; i++) {
		if (num[i] > max) {
			max = num[i];
			maxIndex = i + 1;
		}
	}

	cout << max << "\n" << maxIndex;

	return 0;
}
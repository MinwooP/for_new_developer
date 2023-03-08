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

	int num[7];
	int sum = 0;
	int min = 100;

	for (int i = 0; i < 7; i++) {
		cin >> num[i];
		if (num[i] % 2 == 1) { 
			sum += num[i];
			if (num[i] < min)
				min = num[i];
		}
	}

	if (sum == 0) {
		cout << -1;
	}
	else {
		cout << sum << '\n' << min;
	}

	return 0;
}	
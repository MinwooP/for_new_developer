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

	int a, b, c;
	cin >> a >> b >> c;

	int ans;

	if (a == b && b == c) {
		ans = 10000 + 1000 * a;
	}
	else if (a != b && b != c && a != c) {
		ans = max({ a, b, c }) * 100;
	}
	else {
		if (a - b == 0) {
			ans = 1000 + a * 100;
		}
		else if (b - c == 0) {
			ans = 1000 + b * 100;
		}
		else {
			ans = 1000 + a * 100;
		}
	}
	
	cout << ans;

	return 0;
}
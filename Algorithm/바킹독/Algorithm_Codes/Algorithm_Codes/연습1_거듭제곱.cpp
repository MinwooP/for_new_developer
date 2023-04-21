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

using ll = long long;

ll POW(ll A, ll B, ll C) {
	if (B == 1)
		return A % C;
	ll val = POW(A, B / 2, C);
	val = val * val % C;

	if (B % 2 == 0)
		return val;
	else
		return val * A % C;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll A, B, C;
	cin >> A >> B >> C;

	cout << POW(A, B, C);

	return 0;
}

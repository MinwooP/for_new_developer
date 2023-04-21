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

int Z(int n, int r, int c) {
	if (n == 0)
		return 0;

	int half = (1 << (n - 1));
	int skip = half * half;
	if (r < half && c < half) return Z(n - 1, r, c);
	if (r < half && c >= half) return skip + Z(n - 1, r, c - half);
	if (r >= half && c < half) return 2 * skip + Z(n - 1, r - half, c);
	if (r >= half && c >= half) return 3 * skip + Z(n - 1, r - half, c - half);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int N = 0;
	int r, c;
	cin >> N >> r >> c;
	cout << Z(N, r, c);

	return 0;

}
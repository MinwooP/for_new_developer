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


int cnt = 0;

void hanoi(int a, int b, int n) {

	if (n == 1) {
		cout << a << " " << b << "\n";
		return;
	}

	hanoi(a, 6 - a - b, n - 1);
	hanoi(a, b, 1); // cout << a << " " << b << "\n";·Î ¾²´Â°Ô ´õ ±ò²û => È£Ãâ ÇÑ¹ø ´ú ÇÏ´Ï±î 
	hanoi(6 - a - b, b, n - 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;


	cout << (1 << n) - 1 << "\n";
	hanoi(1, 3, n);

	return 0;
}
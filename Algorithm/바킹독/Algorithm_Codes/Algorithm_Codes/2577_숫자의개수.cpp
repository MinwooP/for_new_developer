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

	int freq[10] = {};

	int A, B, C;
	cin >> A >> B >> C;

	int num = A * B * C;

	while (num != 0) { // ex) num = 123466
		freq[num % 10]++;
		num = num / 10;
	}

	for (int i = 0; i < 10; i++) {
		cout << freq[i] << '\n';
	}

	return 0;
}


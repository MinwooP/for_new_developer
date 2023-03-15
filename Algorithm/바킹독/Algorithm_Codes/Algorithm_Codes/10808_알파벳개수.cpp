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

	int numOfChar[123] = { 0 };
	string s;

	cin >> s;

	for (int i = 0; i < s.size(); i++) {
		numOfChar[s[i]]++;
	}

	for (int i = 97; i < 123; i++) {
		cout << numOfChar[i] << ' ';
	}
	return 0;
}

// 97 ~ 122
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
#include <list>
#include<iomanip>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int M;
	cin >> M;

	while (M--) {
		string cmd;
		cin >> cmd;

		list<char> L = {};
		auto cursor = L.begin();

		for (auto c : cmd) {
			if (c == '<') {
				if (cursor != L.begin())
					cursor--;
			}
			else if (c == '>') {
				if (cursor != L.end())
					cursor++;
			}
			else if (c == '-') {
				if (cursor != L.begin()) {
					cursor--;
					cursor = L.erase(cursor);
				}
			}
			else {
				L.insert(cursor, c);
			}
		}

		for (auto c : L) cout << c;
		cout << '\n';
	}
	return 0;
}


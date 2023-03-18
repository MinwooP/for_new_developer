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

	string s;
	cin >> s;

	list<char> L = {};
	for (auto c : s) {
		L.push_back(c);
	}

	list<char>::iterator cursor = L.end();

	int M;
	cin >> M;

	while (M--) {
		string cmd;
		cin >> cmd;

		if (cmd == "L") {
			if (cursor != L.begin())
				cursor--;
		}
		else if (cmd == "D") {
			if (cursor != L.end())
				cursor++;
		}
		else if (cmd == "B") {
			if (cursor != L.begin()) {
				cursor--;
				L.erase(cursor);
			}
		}
		else if(cmd == "P") {
			char letter;
			cin >> letter;

			if (cursor != L.begin()) {
				L.insert(cursor,letter);
			}
		}
	}

	for (list<char>::iterator it = L.begin(); it != L.end(); it++)
		cout << *it;

	return 0;
}


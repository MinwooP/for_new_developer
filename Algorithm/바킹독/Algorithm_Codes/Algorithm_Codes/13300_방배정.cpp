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

	int N, K;
	int students[2][7] = { 0 };
	int gender, grade;

	cin >> N >> K;
	while (N--) {
		cin >> gender >> grade;
		students[gender][grade]++;
	}


	int room = 0;

	for (int i = 0; i <= 1; i++) {
		for (int j = 1; j <= 6; j++) {
			if (students[i][j] == 0) {

			}
			else if (students[i][j] <= K) {
				room++;
			}
			else {
				while (students[i][j] > 0) {
					students[i][j] -= K;
					room++;
				}
			}
		}
	}

	cout << room;

	return 0;
}
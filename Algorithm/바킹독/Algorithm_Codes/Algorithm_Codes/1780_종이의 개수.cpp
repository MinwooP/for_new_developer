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


int arr[3000][3000];
int total0, total1, total_1 = 0;

void check(int num) {
	if (num == 0) {
		total0++;
	}
	else if (num == 1) {
		total1++;
	}
	else {
		total_1++;
	}
}

void recur(int n, int x, int y) {
	if (n == 1) {
		check(arr[x][y]);
		return;
	}


	int first = arr[x][y]; // 0 1 -1
	for (int i = x; i < x + n; i++) {
		for (int j = y; j < y + n; j++) {
			if (arr[i][j] != first) {
				first = 2;
			}
		}
	}

	if (first == 2) { // 다른게 있으면 
		for (int i = 0; i < n; i += n / 3) {
			for (int j = 0; j < n; j += n / 3) {
				recur(n / 3, x + i, y + j);
			}
		}
	}
	else { // 다 같으면 
		check(first);
		return;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	recur(N, 0, 0);

	cout << total_1 << "\n" << total0 << "\n" << total1 << "\n";
	return 0;

}
	
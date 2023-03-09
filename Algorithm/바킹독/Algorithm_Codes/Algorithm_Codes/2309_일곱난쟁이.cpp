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

	vector<int> v;
	int N = 9;
	int temp, sum = 0;
	while (N--) {
		cin >> temp;
		sum += temp;
		v.push_back(temp);
	}

	sort(v.begin(), v.end());

	for (int i = 0; i < 9; i++) { 
		for (int j = i + 1; j < 9; j++) {
			if (sum - v[i] - v[j] == 100) {
				for (int k = 0; k < 9; k++) {
					if (k != i && k != j) {
						cout << v[k] << '\n';
					}
				}
				return 0;
			}
		}
	}f
}
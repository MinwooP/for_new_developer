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

int n, m; // 1~n 까지의 수 중에 m개를 고른 수열 

int seq[10]; // 수열
bool isused[10]; 

void f(int k) { // seq[k]를 정하는 것.
	if (k == m) { // 이미 m개가 정해져 있을 것  
		// 수열 출력
		for (int i = 0; i<m ; i++) {
			cout << seq[i] << ' ';
		}
		cout << "\n";
		return;
	}

	for (int i = 1; i <= n; i++) {
		if (isused[i]) continue;

		seq[k] = i;
		isused[i] = true;
		f(k + 1); // 이제 다음 수를 고를 차례
		isused[i] = false;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	f(0);
	return 0;
}
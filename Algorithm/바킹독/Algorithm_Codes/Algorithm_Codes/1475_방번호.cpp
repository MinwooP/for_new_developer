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

	// 9999 => 2 999 => 2 
	// 9나 6일 때는 0.5씩 증가시켜야함

	int N;

	cin >> N;

	int freq[10] = {};
	int flag = 1;

	while (N != 0) {
		if (N % 10 == 6 || N % 10 == 9) {
			if (flag == 1) {
				freq[6]++;
			}
			flag *= -1;
		}
		else {
			freq[N % 10]++;
		}

		N = N / 10;
	}

	int max = *max_element(begin(freq), end(freq));
	cout << max;

	return 0;
}


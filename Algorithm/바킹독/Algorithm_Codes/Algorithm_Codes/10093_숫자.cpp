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

	unsigned long long A, B = 0;
	 
	cin >> A >> B;

	if (A == B) {
		cout << 0 << '\n';
	}
	else if(A > B){ 
		cout << A - B - 1 << '\n';
		for (unsigned long long i = B + 1; i < A; i++) {
			cout << i << ' ';
		}
	}
	else {
		cout << B - A - 1 << '\n';
		for (unsigned long long i = A + 1; i < B; i++) {
			cout << i << ' ';
		}
	}
	
	return 0;
}
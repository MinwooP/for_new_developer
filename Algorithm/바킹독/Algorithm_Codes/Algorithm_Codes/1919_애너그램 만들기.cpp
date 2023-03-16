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

	int alphabet[26] = { 0 };

	string s1, s2;
	cin >> s1 >> s2;

	for (auto c : s1) { 
		alphabet[c - 'a']++;
	}

	for (auto c : s2) {
		alphabet[c - 'a']--;
	}

	int cnt = 0;

	for (int i = 0; i < 26; i++) {
		if (alphabet[i] > 0) {
			while (alphabet[i] != 0) {
				alphabet[i]--;
				cnt++;
			}
		}
		else if (alphabet[i] < 0) {
			while (alphabet[i] != 0) {
				alphabet[i]++;
				cnt++;
			}
		}
		else {
			continue;
		}
	}

	cout << cnt;
	cin >> s1 >> s2;

	return 0;
}

// 두 단어가 서로 애너그램 관계에 있도록 만들기 위해서 제거해야 하는 최소 개수의 문자 수를 구하는 프로그램


# [1759번_암호만들기](https://www.acmicpc.net/problem/1759)

##  Category : 브루트포스

-----

## 🎖 내 풀이

+ 

<br>

<br>

-------

## 🎖 Solution

### 시간 복잡도 계산 

















<br>

### 핵심 아이디어













<br>

### 정답과 내 풀이 비교









































<br>

<br>

-----

## 🎖 전체 코드

### 내 코드

```c++
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



char arr[15];
bool if_aeiou[15]; // 모음인지 판단해주는 함수

vector <char> temp;

// go(0, 0, 0, 0, l, c)
void go(int count, int index, int numofbcd, int numofaeiou, int l, int c) { 
	if (count == l) {
		if (numofaeiou >= 1 && numofbcd >= 2) {
			for (int i = 0; i < l; i++) {
				cout << temp[i];
			}
			cout << '\n';
			return;
		}
		else
			return;
	}

	if (index >= c)
		return;

	if (count > l)
		return;

	// count < l

	// 현재 index의 수 선택
	temp.push_back(arr[index]);

	if (if_aeiou[index]) // 모음이면
		go(count + 1, index + 1, numofbcd, numofaeiou + 1, l, c);
	else
		go(count + 1, index + 1, numofbcd + 1 , numofaeiou, l, c);


	// 복구해주는 과정?
	temp.pop_back();

	// 현재 index의 수 선택x
	go(count, index + 1, numofbcd, numofaeiou, l, c);
}



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int L, C;
	cin >> L >> C;

	for (int i = 0; i < C; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + C);

	// arr[i]가 모음이면 if_aeiou[i] = true로 설정해줌
	for (int i = 0; i < C; i++) {
		if (arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u')
			if_aeiou[i] = true;
	}

	go(0, 0, 0, 0, L, C);

	return 0;
}
```

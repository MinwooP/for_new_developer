# [18290번_NM과 K (1)](https://www.acmicpc.net/problem/18290)

##  Category : 브루트포스

-----

## 🎖 내 풀이

+ N과 M (1), (2)번 문제처럼 **재귀**를 이용해 풀 수 있을 것 같아서 그 문제의 재귀 코드를 참고해 짜보았지만, 재귀를 아직 완벽하게 이해하지 못한 탓일까 중간에 꼬였다. 

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
#include <iostream>
using namespace std;


int k;
int m, n;
int ans = 0;
int temp = 0;

int table[10][10];
int cannotuse[10][10] = { 0 }; // 기본값 false이므로 다 사용가능



void selectrc(int r, int c) {
	// r, c를 선택했을 때 인접한 수들은 사용하지 못하게 만드는 함수

	// 1. [r, c] 사용 불가능
	cannotuse[r][c]++;

	// 2. 위쪽 [r-1, c] 사용 불가능
	if (r > 0)
		cannotuse[r - 1][c]++;

	// 3. 아래쪽 사용 불가능
	if (r + 1 < m)
		cannotuse[r + 1][c]++;

	// 4. 왼쪽
	if (c > 0)
		cannotuse[r][c - 1]++;

	// 5. 오른쪽
	if (c + 1 < n)
		cannotuse[r][c + 1]++;

}

void releaserc(int r, int c) {
	// r, c를 놓아줄 때 그 인접한 수도 이제 사용가능하게 만들어주는 함수
	
	// 1. [r, c] 사용가능
	cannotuse[r][c]--;

	// 2. 위쪽 [r-1, c] 사용가능
	if (r > 0)
		cannotuse[r - 1][c]--;

	// 3. 아래쪽 사용가능
	if (r + 1 < m)
		cannotuse[r + 1][c]--;

	// 4. 왼쪽
	if (c > 0)
		cannotuse[r][c - 1]--;

	// 5. 오른쪽
	if (c + 1 < n)
		cannotuse[r][c + 1]--;

}




void go(int i, int j, int selected) { // go(0, 0, 0)

	if (selected == k) {// 이미 k개 선택 후  go(k)을 호출했으므로 
		if (temp > ans)
			ans = temp;// 기존 최댓값과 비교해서 더 크면 업데이트
		return;
	}

	if (i > n - 1 || j > m - 1)
		return;

	// 해당 i, j를 선택할 때
	if (cannotuse[i][j] == 0) { // 사용할 수 있을 때, 즉 이미 선택한 수에 인접하지 않을 때
		temp = temp + table[i][j];
		selectrc(i, j); // 이제 [i,j]와 이에 근접한 수들은 잠시 사용 못함

		if (j == m - 1)// 제일 오른쪽일 때 
			go(i + 1, 0, selected + 1);
		else
			go(i, j + 1, selected + 1);
	}
	else {
		// 현재 i, j  선택 하지 않고 다음 재귀 호출
		if (j == m - 1)// 제일 오른쪽일 때 
			go(i + 1, 0, selected);
		else
			go(i, j + 1, selected);
	}

	// release
	temp = temp - table[i][j];
	releaserc(i, j);

	// 현재 i, j  선택 하지 않고 다음 재귀 호출
	if (j == m - 1)// 제일 오른쪽일 때 
		go(i + 1, 0, selected);
	else
		go(i, j + 1, selected);

/*

	// 현재 i, j  선택 후 다음 재귀 호출
	if (j == m - 1)// 제일 오른쪽일 때 
		go(i + 1, 0, selected + 1);
	else
		go(i, j + 1, selected + 1);

	// 현재 i, j  선택 하지 않고 다음 재귀 호출
	if (j == m - 1)// 제일 오른쪽일 때 
		go(i + 1, 0, selected);
	else
		go(i, j + 1, selected );

*/


	// 언제 release 해줘야 할까 
	// 해당 i, j를 선택안할 때
	// 오른쪽, 아래쪽으로 선형적으로 탐색하면서 사용할 수 있는(cannnotuse == false인)수를 선택
	// 


	// 오른쪽 끝일 때, 즉, j = m-1일 때 고려
	// temp 초기화
}


int main() {
	cin >> n >> m >> k;; // 4 , 2
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
		}
	}

	go(0, 0, 0);

	return 0;
}
```



```c++
void go(int i, int j, int selected) { // go(0, 0, 0)

	if (selected == k) {// 이미 k개 선택 후  go(k)을 호출했으므로 
		if (temp > ans)
			ans = temp;// 기존 최댓값과 비교해서 더 크면 업데이트
		return;
	}

	if (i > n - 1 || j > m - 1)
		return;

	// 해당 i, j를 선택할 때
	if (cannotuse[i][j] == 0) { // 사용할 수 있을 때, 즉 이미 선택한 수에 인접하지 않을 때
		temp = temp + table[i][j];
		selectrc(i, j); // 이제 [i,j]와 이에 근접한 수들은 잠시 사용 못함

		if (j == m - 1)// 제일 오른쪽일 때 
			go(i + 1, 0, selected + 1);
		else
			go(i, j + 1, selected + 1);
	}
	else {
		// 현재 i, j  선택 하지 않고 다음 재귀 호출
		if (j == m - 1)// 제일 오른쪽일 때 
			go(i + 1, 0, selected);
		else
			go(i, j + 1, selected);
	}

	// release
	temp = temp - table[i][j];
	releaserc(i, j);

	// 현재 i, j  선택 하지 않고 다음 재귀 호출
	if (j == m - 1)// 제일 오른쪽일 때 
		go(i + 1, 0, selected);
	else
		go(i, j + 1, selected);
```

함수 호출 과정

+ go(0, 0, 0)           // temp = 1,  select(0, 0)

  + go(0, 1, 1)      // **1번**을  호출

    + go(0, 2, 1)   // temp = 1 + 3 = 4; 셀렉트(0, 2)   // **1번**에서 호출

      + go(1, 0, 2)   // ans = 4; return;

    + go(0, 2, 1)   // temp = 1  ; 릴리즈(0, 2)  **2번**을 호출

      + go(1, 0, 1)   // **2번**에서 호출

        + go(1, 1, 1)   // temp = 1+ 5 = 6;  셀렉트

          + go(1, 2, 2)   // ans = 6; return; 

        + go(1, 1, 1)   // temp = 1;  릴리즈

          + go(1, 2, 1)  // temp = 1 + 6 = 7; 셀렉트

            + go(2, 0, 2)  // ans = 7; return;

          + go(1, 2, 1)  // temp = 1; 릴리즈 

            + go(2, 0, 1)  // temp = 1 + 7 = ;

              

    



































go(0, 0, 0)           // temp = 1,  select(0, 0)

+ go(0, 1, 1)      // 사용못해서
  + go(0, 2, 1)   // temp = 1 + 3 = 4; 셀렉트(0, 2)
    + go(1, 0, 2)   // ans = 4; return;
  + go(0, 2, 1)   // temp = 1  ; 릴리즈(0, 2)
    + go(1, 0, 1)   // 사용못해서
      + go(1, 1, 1)   // temp = 1+ 5 = 6;  셀렉트
        + go(1, 2, 2)   // ans = 6; return; 
      + go(1, 1, 1)   // temp = 1;  릴리즈
        + go(1, 2, 1)  // temp = 1 + 6 = 7; 셀렉트
          + go(2, 0, 2)  // ans = 7; return;
        + go(1, 2, 1)  // temp = 1; 릴리즈 
          + go(2, 0, 1)  // temp = 1 + 7 = 8;

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

int n, m; // 1~n ������ �� �߿� m���� �� ���� 

int seq[10]; // ����
bool isused[10]; 

void f(int k) { // seq[k]�� ���ϴ� ��.
	if (k == m) { // �̹� m���� ������ ���� ��  
		// ���� ���
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
		f(k + 1); // ���� ���� ���� �� ����
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
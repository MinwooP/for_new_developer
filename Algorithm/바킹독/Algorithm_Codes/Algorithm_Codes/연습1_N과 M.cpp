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

int n, m;
int arr[10]; // �� ������ �ڸ����� ��Ÿ��
bool isused[10]; // �� ���� ���Ǿ����� 

void func(int k) { // ���� k������ ���� ������. ���� arr[k]�� �����ؾ� �ϴ� ��Ȳ 
	if (k == m) { // m���� ��� ��������
		for (int i = 0; i < m; i++)
			cout << arr[i] << ' '; // arr�� ����ص� ���� ���
		cout << '\n';
		return;
	}

	for (int i = 1; i <= n; i++) { // 1���� n������ ���� ����
		if (!isused[i]) { // ���� i�� ������ �ʾ�����
			arr[k] = i; // k��° ���� i�� ����
			isused[i] = 1; // i�� ���Ǿ��ٰ� ǥ��
			func(k + 1); // ���� ���� ���Ϸ� �� �ܰ� �� ��
			isused[i] = 0; // k��° ���� i�� ���� ��� ��쿡 ���� �� Ȯ�������� i�� ���� �������ʾҴٰ� �����.
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	func(0);
}
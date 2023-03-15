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


int num[21];

void swap(int a, int b) {
	int temp = num[a];
	num[a] = num[b];
	num[b] = temp;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for (int i = 1; i <= 20; i++) {
		num[i] = i;
	}

	int N = 10;
	int a, b;
	while (N--) {
		cin >> a >> b;
	
		int dif = b - a;
		if (dif % 2) { // Ȧ��
			for (int i = 0; i < dif/2 + 1; i++) {
				swap(a + i, b - i);
			}
		}
		else { // ¦��
			for (int i = 0; i < dif/2; i++) {
				swap(a + i, b - i);
			}
		}
	}
	
	for (int i = 1; i <= 20; i++) {
		cout << num[i] << ' ' ;
	}
	return 0;
}

//1~20 �ε��� �迭 ����
//1~20���� �ֱ�
//���� a,b �Է¹ޱ�
//
//a,b���� ¦������� ab�� swap, a-1, b-1, ����
//1 10 => n = 10+1 / 2 = 5�� swap a, a+! ,,, a+n ��
//
//3 12 
//
//a,b������ Ȧ�������
//1 9 => 19 28 37 46 4�� ����
//n = 1+9/2 = 5 -1 => 4�� swap 
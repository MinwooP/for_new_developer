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


void print_(int cnt) {
	for (int i = 0; i < cnt * 4; i++) {
		cout << "_";
	}
}
void recursion(int n, int cnt) {

	if (n == 1) {
		print_(cnt); cout << "\"����Լ��� ������?\"\n";
		print_(cnt); cout << "\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"\n";
		print_(cnt); cout << "��� �亯�Ͽ���.\n";
		return;
	}

	print_(cnt);
	cout << "\"����Լ��� ������?\"\n";
	print_(cnt);
	cout << "\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.\n";
	print_(cnt);
	cout << "���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.\n";
	print_(cnt);
	cout << "���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"\n";

	recursion(n - 1, cnt + 1);

	print_(cnt); cout << "��� �亯�Ͽ���.\n";
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	cout << "��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n";
	cout << "\"����Լ��� ������?\"\n";
	cout << "\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.\n";
	cout << "���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.\n";
	cout << "���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"\n";

	recursion(n, 1);

	cout << "��� �亯�Ͽ���.";

	return 0;
}	
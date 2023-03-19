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
#include <list>
#include<iomanip>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N, K;
	cin >> N >> K;
	
	list<int> L = {};
	for (int i = 1; i <= N; i++) {
		L.push_back(i);
	}

	auto it = L.begin();

	vector<int> ans;

	while (!L.empty()) {
		for (int i = 1; i < K; i++) {
			if (it == L.end())
				it = L.begin();
			it++;
			if (it == L.end())
				it = L.begin();
			// it�� ������Ű�� ������, �Ŀ��� it�� ���� ����Ű�� �ִٸ�, ������ �Ű���� ��.
		}

		ans.push_back(*it);
		it = L.erase(it);
	}


	cout << "<";
	for (int i=0;i<ans.size();i++){
		if (i != ans.size() - 1) {
			cout << ans[i] << ", ";
		}
		else {
			cout << ans[i];
		}
	}
	cout << ">";
	return 0;
}

/*
�� ������ ���Ḯ��Ʈ�� Ǯ��� �ϴ� ���� 
=> 


*/
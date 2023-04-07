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
#include<list>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int N;
	vector<int> V;
	stack<int> S;
	stack<int> ans;
	cin >> N;

	int num;
	for(int i=0;i<N;i++){
		cin >> num;
		V.push_back(num);
	}

	for(int i=N-1;i>=0;i--) {
		while (!S.empty() && V[i] >= S.top()) {
			S.pop();
		}
		if (S.empty()) {
			ans.push(-1);
			S.push(V[i]);
		}
		else {
			ans.push(S.top());
			S.push(V[i]); 
		}
	}

	while (!ans.empty()) {
		cout << ans.top() << " ";
		ans.pop();
	}

	return 0;
}

// 3 5 2 7 
// -1 


## 최댓값, 최솟값 구하기

`min(a, b)`, `max(a, b)`

a와 b중 최솟값을 반환하는 함수



`min({a, b, c})`, `max({a, b c})`

3개 이상의 수를 비교하고 싶다면, 중괄호를 이용해 감싸주면 된다. 



### vector에서 최댓값, 최솟값 구하기

vector에서 최댓값, 최솟값 구하기

```c++
vector<int> v;
int max = *max_element(v.begin(), v.end());
int min = *min_element(v.begin(), v.end());
```

`max_element`의 결과로 최대값을 가리키는 **반복자를 반환**한다. 따라서 이를 `*` 연산자를 사용하면 최대값을 구할 수 있다.



vector에서 가장 큰 수의 인덱스 구하기

```c++
int max_index = max_element(v.begin(), v.end()) - v.begin();
```

또한, vector는 일련의 반복자로 구성되어 있으므로 최대값을 가리키는 반복자를 맨 처음을 가리키는 `v.begin()`만큼 빼준다면 인덱스 값을 구할 수 있다.





### 배열 혹은 벡터 정렬하기

배열 정렬

`sort(arr, arr + 10);`



벡터 정렬

`sort(v.begin(), v.end());`



내림차순 정렬

`sort(v.rbegin(), v.rend());`



그런데 오름차순이 아니라 내가 원하는 정렬 기준을 세워서 정렬하고 싶다면? 정렬하고 싶은 대상이 기초 타입이 아니라면? 

=> sort() 함수의 세 번째 인자로 비교기준이 되는 함수포인터 또는 함수 객체를 넣어주면 된다.
그 함수는 반환타입이 bool 타입이어야 하고 매개변수는 두 개이며 두 매개변수의 타입은 정렬할 데이터의 타입과 일치해야 한다.

내림차순으로 정렬하고 싶다면 compare 함수를 이렇게 만들면 된다.

```c++
bool cmp(int a, int b) { 
  return a > b; 
}
sort(v.begin(), v.end(), cmp);
```












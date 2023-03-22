### 최댓값, 최솟값 구하기

`min(a, b)`, `max(a, b)`

a와 b중 최솟값을 반환하는 함수



`min({a, b, c})`, `max({a, b c})`

3개 이상의 수를 비교하고 싶다면, 중괄호를 이용해 감싸주면 된다. 





### 배열에서 최댓값, 최솟값 구하기

```c++
int arr[10] = {1, 2, 3, ... , 10};
int max = *max_element(begin(arr), end(arr))
```

​		

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









### Pair

+ Pair class는 사용자가 지정한 2개의 타입의 데이터를 저장하는데 사용된다. 

+ pair class는 `#include <utility>`라는 헤더파일에 존재하는 STL 이지만, `<algorithm>`, `<vector>` 헤더파일에 `utility` 헤더 파일이 이미 포함되어 있기 때문에, 

  `#inlucde <vector>`만 해도 된다. 

+ Pair 함수의 사용

  + `pair<type1,type2> p`
    pair 클래스의 객체 p를 생성합니다. 객체 이름은 p가 아니어도 상관없습니다.

    ```c++
    pair<int, int> p; // int 타입 데이터 2개를 관리할 수 있는 pair 클래스의 p객체
    pair<int, double> p;// int타입과 double 타입 데이터를 한번에 관리할 수 있는 pair 클래스의 p객체
    ```

  + `p.first`
    p의 첫번째 인자를 반환합니다.

  + `p.second`
    p의 두번째 인자를 반환합니다.

  + `make_pair(값1, 값2)`
    값1, 값2를 한쌍으로 하는 pair를 만들어서 반환합니다.

+ 예제 코드

  ```c++
  pair<int, double> p;
  
  int main()
  {
  	p.first = 1; //pair의 첫번째 인자에 접근
      p.second = 2.1; //pair의 두번째 인자에 접근
      
      cout<<"first value: "<<p.first<<endl;
      cout<<"second value: "<<p.second<<endl;
      
      p = make_pair(1, 2.1); // p.first = 1, p.second = 2.1 과 동일
      return 0;
  }
  ```

  

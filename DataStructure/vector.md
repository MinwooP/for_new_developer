# vector 정리



## vector란?

+ 자동으로 메모리가 할당되는 배열로, vector를 생성하면 heap 메모리에 동적으로 할당된다.
+ 기본적으로 맨 뒤쪽에서 삽입과 삭제가 가능하며, 중간에서도 가능하지만 크게 효율적이지 않다.
+ 배열과 달리 자동으로 메모리를 할당해주므로 처음부터 원소의 개수를 지정할 필요가 없다. 
+ 배열 기반이므로 랜덤 접근(Random Access)이 가능하다.
+ 배열 기반이므로 원소의 삽입, 삭제가 자주 수행되면 시간적인 측면에서 비효율적이다.
+ vector의 연산에 대한 시간복잡도
  + 임의 접근 = O(1)
  + 벡터의 끝에 원소를 삽입하거나 삭제 = O(1)
  + 원소의 삽입과 삭제 = O(n) (마지막 원소로부터의 거리에 비례)

<img src = "https://user-images.githubusercontent.com/31370590/124488909-5e0e9880-ddeb-11eb-8ac2-7bded5e06d5a.PNG " width = "600" height = "300">

##  vector 연산

+ 초기화 방법

```C++
#include <vector>

vector <int> v1;  // 빈 vector
vector <int> v2(5); // {0, 0, 0, 0, 0}
vector <int> v3(5,1); // {1, 1, 1, 1, 1}
vector <int> v4(v3); // v4 = v3;
vector <vector<int>> v5; // 2차원 벡터
vector <int> v6 = {1,2,3,4,5};
```



+ vector  멤버함수
  + v.at(index) : index번째 원소를 반환한다. 유효한 index인지 체크하기 때문에 안전하다.
  + v[index] : index번째 원소를 반환한다. 배열과 같은 방식이며 유효성을 체크하지 않는다.
  + v.front() : 첫번째 원소를 반환한다.
  + v.back() : 마지막 원소를 반환한다.
  + v.clear() : 모든 원소를 제거한다.  메모리는 그대로 남아있게 된다. (size는 줄어들고 capacity는 유지)
  + v.begin() : 첫번째 원소를 가리키는 반복자(iterator)를 반환한다.
  + v.end() : __마지막 원소 다음__을 가리키는 반복자(iterator)를 반환한다.
  + v.push_back(m) : 마지막 원소 뒤에 원소 m을 삽입한다.
  + v.pop_back() : 마지막 원소를 제거한다. 













## 참고

+ [Rebro의 코딩 일기장](https://rebro.kr/37)
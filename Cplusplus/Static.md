## Static 



#### Static 변수

C언어에서 전역 변수를 함수 내부로 옮기는 방법으로 **static** 지역 변수를 사용하듯이 C++에서 전역변수를 클래스 내부로 옮기기 위해 static 멤버 변수를 사용한다. 

```c++
#include <iostream>
using namespace std;

class Tipsware{
    private:
    	// 동일한 객체들 간에 공유하는 멤버 변수 선언
    	// 이 클래스 안에서만 사용 가능한 전역 변수라고 생각하면 됨 
    	static int m_object_cnt;
    
    public:
    	Tipsware(){ // 생성자
            // static 변수의 값을 1 증가시킨다.
            m_object_count++;
        }
    
    	~Tipsware(){ // 생성자
            // static 변수의 값을 1 감소시킨다.
            m_object_count++;
        }
    
    
}
```

+ 클래스 안 `private: static int m_object_cnt;`의 의미

  => 실제로 `m_object_cnt` 변수는 전역변수이고, 해당 클래스에서만 이 전역변수를 사용하겠다는 뜻 

  => 클래스 외부에 전역변수를 선언하듯이 이 static 변수를 선언하고, 초기화해줘야 함

  + 클래스 외부에서 초기화 : `int Tipsware::m_object_cnt = 0;`
  + 클래스 내부에서 초기화 : `static int m_object_cnt = 0;`

<br>

#### static 멤버 함수

+ C++ 언어에서는 클래스의 멤버 함수를 호출하려면 당연히 객체를 먼저 선언하고 그 객체의 멤버 함수를 사용해야 한다. 하지만 예외적으로 아래와 같이 static 멤버 함수를 선언하면 이 함수는 **객체를 선언하지 않고 클래스의 네임스페이스만 가지고 호출이 가능하다.** 

  => 

  ```c++
  class Tipsware{
      private:
      		~
      public:
      		~
      	static int GetObjectCount(){ // static 멤버 함수
                  return m_object_count;
              }
  ```



+ static 멤버 함수의 사용상 제한 ?

  static 멤버 함수가 객체 선언 없이 클래스 네임스페이스만 가지고 호출이 가능한 이유는 **static 멤버함수를 호출할 때 내부적으로 this 포인터가 넘어가지 않기 때문**입니다. 즉, static 함수에서는 this 포인터 사용이 불가능하다.

  **따라서 지금처럼 this 포인터에 의존하지 않는 static 멤버 변수는 static 멤버 함수 내에서 사용이 가능**하지만 this 포인터를 사용해야 하는 다른 일반 멤버 변수에는 접근이 불가능하다. 

  => 따라서 대부분의 static 멤버 함수는 static 멤버 변수를 사용하기 위해 만들어진다고 보면 된다. 결국 static 멤버 변수와 static 멤버 함수는 결국 전역 변수와 전역 함수를 클래스의 네임스페이스로 옮겨 놓은 문법 표현일 뿐이다. 
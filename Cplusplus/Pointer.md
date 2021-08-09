# 포인터

## 변수는 메모리에 어떻게 저장되는가 - 메모리 주소

+ 데이터를 저장하면 메모리에 어떻게 저장이 되는지

  ```c++
  #incude <stdio.h>
  int main(){
      int n = 10;
      double d = 3.141592;
      return 0;
  }
  ```

  + "n이라는 이름을 가진 박스에다가 10을 저장했다"라는 말은 곧 10을 메모리 어딘가에 저장하고 우리가 쉽게 쓸 수 있는 n이라는 이름을 붙인 것이다. 

  <img src = "https://user-images.githubusercontent.com/31370590/127466713-66ead353-9330-494b-b63e-688b9d8322d7.PNG" width = "500" height = "300">

  + 현재 **00120B14**라는 메모리 주소에 4byte(sizeof int)만큼 공간을 잡고 10을 넣어준 것이다. C언어는 항상 메모리 시작번지만 가지고 위치를 표현하고 거기서부터 자료형의 크기만큼 공간을 할당한다. **00120B14**는 16진수로 나타낸 것이므로 실제로는 한 숫자가 4bit를 나타내므로 32bit(8x4) = 4Byte 주솟값이다.(그래서 포인터의 크기가 4byte이다.) **하나의 메모리 주소에는 1byte만 포함될 수 있다** 이는 컴퓨터 하드웨어적으로 정해진 것? 이다.  



## 포인터란?

+ 포인터란, **메모리 주소값을 저장할 수 있는 자료형**이다. 즉, 포인터도 결국 하나의 자료형, data type이다. 

+ `&num` : 변수 num의 주소값을 반환

  `*num` : 포인터변수 num에 저장되어 있는 주소에 들어있는 값을 반환

+ 포인터 변수를 초기화하지 않고 선언만 하면, 의도하지 않은 곳의 주소를 가리키게 될수도 있으므로, Null로 초기화하거나 원하는 값을 바로 넣어주는 것이 좋다. 



## 포인터 연산

+ 포인터에다 연산을 할 때, 그 포인터가 어떤 data type의 변수를 가리키는지를 보고, 그 data type의 크기를 단위로 연산을 진행한다. 

  예를 들어 `int num = 13;`,  `int *ptr = &num;` 이라고 하면, `num`은 int형 포인터이므로, num + 1은 num + 4로 계산이 된다. 즉, num + 1했을 때, num과 4byte 차이가 나는 것이다. 

  만약, int형 포인터 변수 ptr의 값이 **0x00000001** 이라고 하면, 이 주솟값에는 4byte 크기의 int값이 저장되기 때문에, **0x00000001~0x00000004**까지는 이 int가 저장되야 하므로, **0x00000002**나 **0x00000003**은 접근이 불가능하다. 따라서, 포인터는 그 data type의 크기(byte)를 단위로 연산을 진행하는 것 같다. 

  

### 명령행 인자

쉘에서 사용하는 새로운 프로세스를 실행하면서 인자를 전달할 수 있습니다. 이처럼 **프로세스를 실행하면서 전달하는 인자**를 **명령행 인자**(Command Line Argument)라고 부릅니다. C언어에서는 이와 같이 명령행 인자를 main 함수의 입력 인자로 받아 사용할 수 있다. 

<br>

`int main(int argc, char** argv, char** envp);`

+ int argc 

  메인 함수에 전달되는 정보의 개수

+ char* argv[ ]

  메인 함수에 전달되는 실질적인 정보로, 문자열의 배열을 의미한다. 첫번째 문자열은 프로그램의 실행경로로 항상 고정이 되어 있다. 

+ envp - 환경 변수 목록

<br>

아무것도 전달하지 않을 채, 실행한다면

`$ HelloWorld.exe`

+ argc = 1

  argv[0] = Helloworld.exe => 프로그램의 실행경로 

  이와 같이 아무정보도 전달하지 않는다면 **기본적으로 argv의 첫번째 값으로 실행경로**가 들어가 있으며, 실행경로 정보 1개뿐이므로 **argc = 1**이 된다.

<br>

이번에는 정보를 전달해서, 실행한다면

`$ HelloWorld.exe I Love You Always`

+ argc = 5;
+ argv[0] = Helloworld.exe
+ argv[1] = I
+ argv[2] = Love
+ argv[3] = You
+ argv[4] = Always

=> HelloWorld.exe 프로그램을 실행하면서, **최초에 전달하고 싶은 정보를 공백 기준 문자열 형태로 전달할 수 있으며**, 이 정보는 main 함수의 argv로 들어간다. 또한,  argc에는 그 갯수가 전달된다. 
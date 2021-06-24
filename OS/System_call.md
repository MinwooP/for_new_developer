# System call



#### system call이란

+ Mechanism used by an application  program to ___request service from the Operating system___
+ 응용 프로그램이 os에게 서비스를 요청할 수 있는 유일한 방법
+ 시스템 콜은 커널 영역의 기능을 user mode에서 사용 가능하도록, 즉 프로세스가 하드웨어에 직접 접근해서 필요한 기능을 사용할 수 있게 해준다.
+ 응용 프로그램이 system call을 직접적으로 호출하는 것이 아니라, 응용 프로그램은 API를 호출하고 이에 해당하는 system call이 호출된다 -> 계층화
+ 각 system call에는 system call number가 할당되고, system call interface는 각 번호에 해당하는 system call을 가지고 있는 table이다. 





####  system call 과정

1. 프로세스가 system call 호출
2. Trap이 발생하여 kernel mode 진입 -> 이때 현재 상태 저장
3. 요청받은 system call 수행
4. user mode로 return





#### kernel mode VS user mode

<img src = "https://user-images.githubusercontent.com/31370590/123226402-98845580-d50e-11eb-9712-878d64a09ffc.PNG" width = "600"  height = "370" >

+ process A가 프로그램 명령 수행 중에 디스크 입출력 명령을 읽은 경우를 생각해 보자. 사용자 프로그램은 입출력 장치에 접근하는 명령을 수행할 수 없다. user mode에서 특권 명령을 수행할 수 없기 때문이다. 

+ 이런 경우, 사용자 프로그램은 운영체제에게 system call을 통해 특권명령을 대신 수행해달라고 요청한다. 시스템 콜은 주소 공간 자체가 다른 곳(커널의 code 영역)으로 이동해야 하므로 프로그램이 인터럽트 라인에 인터럽트를 세팅하는 명령을 통해 이루어진다. 

  > 시스템 콜은 커널 영역의 기능을 사용자 모드가 사용 가능하도록, 즉 프로세스가 하드웨어에 직접 접근해 필요한 기능을 사용할 수 있게 해준다. 

+ CPU가 인터럽트 라인을 검사하고 인터럽트가 발생한 것을 감지하게 된다. 현재 수행 중인 사용자 프로그램을 잠시 멈추고 CPU의 제어권을 운영체제에게 양도한다(kernel mode). 그리고 이 때 하드웨어적으로 mode bit가 1에서 0으로 자동으로 세팅되어 특권 명령을 수행할 수 있게 된다. 





#### Linux system call example

<img src = "https://user-images.githubusercontent.com/31370590/123280456-be781d00-d543-11eb-98cd-3395e51b0c1c.PNG" width = "600" height = "400">

+ user program에서 fork() API를 호출 
+ fork() 함수가 정의되어 있는 library인 lib.c에서 __system call number인 2를 eax에 전달__, IDT(Interrupt Description Table)을 look up해서 0x80의 system call 호출
+ system call을 호출하기 전, _SAVE_ALL_을 통해 register 값들을 stack에 저장
+ __sys_call_table을  look up __해서 system call number 2에 해당하는 sys_fork() 시스템 콜 호출

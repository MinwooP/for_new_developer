# ✔ Process



## Process

+ a program in execution
+ program은 실행 파일로, 파일 시스템으로 존재하지만 process는 실행되고 있는 주체
+ 실행중인 program의 하나의 instance 
+ program이 실행되면 그 프로세스의 process address space가 memory에 할당된다. 





## PCB 

+ process에 대한 모든 정보를 담고 있는 data structure 
+ process state
  process number - PID?
  program counter - next instruction
  CPU registers 
+ PCB는 프로세스 생성 시 만들어지며 주기억장치에 유지된다. 





## Process address space

<img src = "https://user-images.githubusercontent.com/31370590/123648766-3015db00-d864-11eb-8a8c-5611dfa4c856.PNG" align = "left">




+ program이 memory로 올라가서, memory를 차지하고 있는 상태에서 실행이 되어야 한다.
+ memory address에 저장된 process의 형태이다. 
+ data segment & text segment
  
  + 실행 파일안의 내용이 이 부분에 들어간다. 우리가 작성한 코드가 컴파일되면 exe 파일이 기계어 코드로 생성되고, 이 실행파일을 누르면 기계어 코드가 이 부분에 올라간다. 
  + text segment(code segment)에는 code data가 들어간다
  + data segment(static data)에는 전역 변수 또는 static 변수가 들어간다. 
+ 프로그램을 실행하면 실행 파일에 있는 내용을 가지고 code segment와 static data 부분을 채우고, heap과 stack 부분들은 프로그램을 실행하면서 생겼다 없어졌다 하면서 메모리를 사용하는 것   
  
  + heap은 동적 할당에 의해 생기는 공간
  + stack
    
    + push, pop 연산을 통해 관리
    + 함수 호출 시, stack에 매개변수로 데이터가 push 됨
    + 함수 호출 후, 다시 돌아가기 위한 return address도 stack을 통해 관리
    + 지역변수 관리
    + 컴파일 타임에 stack의 크기 결정됨





## process state

+ __new__ : the process is being created
+ __running__ : instructions are being executed
+ __waiting__ : 어떤 event가 일어나기를 기다리는 상태, I/O request 후, waiting state로 전환, 자발적으로 I/O request에 의해 실행 상태에서 밀려남

+ __ready__ : CPU의 할당을 받으려고 기다리는 상태
  다른 프로세스에 밀려서 비자발적으로 밀려남
+ __terminated__



#### state diagram<img src = "https://user-images.githubusercontent.com/31370590/123633467-3734ed00-d854-11eb-9eb7-30170b69124a.PNG" width = "600" height = "300">



+ ready state VS waiting state
  + ready state란 running state가 될 준비를 마친 상태 
  + 그런데 수행이 안 될까? 다른 process가 실행 중이므로 
  + 즉, 오로지 다른 process가 실행 중이기 때문에 기다리는 것 뿐이지 실행 될 준비를 다 마친 상태
  + 하지만, waiting state는 I/O나 다른 event가 발생하기를 기다리는 것을 나타내는 상태
  + 따라서, running -> waiting -> ready -> running 의 순서로 진행





> __Q)__ interrupt가 발생하면 ready 상태가 되는 이유?
>
> + interrupt가 발생하면 ISR을 수행하게 되고, ISR이 종료되면서 scheduling decision이 일어남, 이 때 우선순위가 높은 다른 process에 의해 현재 process가 ready state로 밀려날 수 있기 때문





## context switching & PCB

<img src = "https://user-images.githubusercontent.com/31370590/123646847-8d109180-d862-11eb-96d5-c638c55e8fde.PNG" width = "600" height = "400">

+ PC, Stack pointer 등의 레지스터들은 CPU내에 존재한다. 따라서, 현재 수행중인(running state) 프로세스 정보는 CPU 내부, 즉 레지스터에서 저장하고 있습니다. 따라서 __현재 실행중인 프로세스까지는 정보를 담는 레지스터가 있으니 PCB라는 저장공간이 따로 필요하지 않다.__

+ 현재 process P0가 실행중이다. CPU에 있는 레지스터들은 P0의 상태로 실행이 되고 있다. 그러다가 interrupt가 걸리면, OS가 실행되야 하는데, 우선 현재 실행되는 process의 상태를 먼저 저장해야 한다. 

+ process가 waiting state가 되면, CPU가 다른 process를 running state로 올린다. interrupt가 걸렸다는 것은 지금 내가 running state인 process를 잠깐 내려놓고, 다른 process를 실행하는 동안 기다리게 한다는 뜻이다. 즉, 레지스터의 저장 값이 앞으로 수행될 process에 대한 값으로 교체될 것이므로 현재 CPU의 레지스터들의 값이 다른 것으로 바뀌기 전에 이를 어딘가에 저장해야 한다. 

+ 이때 PCB에 CPU에서 실행되던 레지스터들의 값이 저장된다. 

  1. 내가 수행하던 process가 어디까지 수행됐는지 (PC)
  2. Stack pointer의 위치가 어디인지 
     

  > #### context switching

  > CPU가 이전의 process state를 PCB에 저장하고, 또 다른 process state를 PCB에서 읽어 레지스터에 적재하는 과정

+ __overhead__ in context switching
  
  context switching 하는 동안, 시스템이 아무런 유용한 일을 하지 못하기 때문에, 이는 순수한 overhead이다. process가 실행되는 동안, I/O event가 발생해서, disk에서 처리해줘야 한다면, disk에서의 I/O operation이 끝날 때 까지 기다려야 하는데, context switching을 통해 다른 process에게 CPU의 할당을 넘겨주지 않으면 그 시간 동안 CPU가 낭비되는 것이므로, 
  조금 수고스럽지만 다른 process로 바꾸면서까지 CPU를 더 써먹는게 더 이득이라는 것이다. 
  약간의 overhead를 치르면서도 기존 프로세스를 새 프로세스로 바꾸는 것이 더 낫다. 
  
  

> ___scheduling___ : ready state인 process들 중 수행될 하나를 고르는 것
>
> 1. scheduling : 여러 process 중 하나를 선택
> 2. dispatch : 선택된 process를 CPU에 올려놓는 것





## operations on process 



## inter-process communication











###### 참고

+ [양햄찌가 만드는 세상](https://jhnyang.tistory.com/notice/31)
+ 
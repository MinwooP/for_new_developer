# Interrupt

#### Interrupt란?

+ CPU가 프로그램을 실행하고 있을 때, I/O device나 Exception이 발생하여 처리가 필요한 경우 CPU에게 알려, 적절하게 처리하도록 하는 것. 

+ 예를 들어, A라는 프로그램이 CPU를 할당받아 명령을 수행하고 있는데, Interrupt가 발생하면 A는 현재 수행 중인 프로세스의 정보를 PCB에 저장해 놓고 Interrupt를 처리한 후, 다시 돌아와 A의 작업을 다시 실행한다.

+ Interrupt를 발생시키는 이유는, I/O Operation이 CPU 수행 속도보다 현저히 느리기 때문에,  중요한 자원인 CPU가 I/O Operation이 종료될 동안 다른 작업을 수행하지 못하고, 종료될 때 까지 기다린다면, 시스템적으로 굉장히 큰 손해이며, 자원 낭비이기 때문이다. 

   
  
  

#### Interrupt의 종류

###### hardware interrupt

+ CPU가 아닌, 하드웨어 장치의 컨트롤러가 CPU의 서비스를 요청하거나 어떤 사실을 알려주기 위해 발생시키는 인터럽트이다. 

- 외부 인터럽트, 비동기적 인터럽트라고 불리며, 주로 인터럽트라고 하면, 이 h/w interrupt를 말한다.

- I/O interrupt
  어떤 작업을 진행하는 데, I/O operation이 필요해 interrupt를 거는 것. 키보드로부터 아이디나 패스워드를 입력받아야 하는 로그인이나, 프린트에서 출력을 할 때 등의 상황에서 CPU는 작업을 하다가 I/O device에게 작업을 토스한다. I/O device는 I/O operation 중, CPU가 가지고 있는 정보가 필요하거나, I/O operation을 다 마치면 CPU에게 Interrupt를 걸어 이를 CPU에게 알린다. 
  즉, I/O device가 CPU를 부를 때 사용하는 것이 I/O interrupt이다. 

- Timer Interrupt

  os가 각 프로그램들이 공평간 시간 동안 CPU를 할당 받을 수 있도록 interrupt를 걸어주는 것. 각 프로그램이 세팅된 시간 동안 CPU를 사용하고, 사용이 끝나면 Timer가 expire 되었다고 interrupt 걸어준다. 따라서, 주기적으로 os가 수행된다. 보통 10ms마다 interrupt를 걸어준다(10ms마다 os가 실행된다).
  
  

__software interrupt__

+ 내부 인터럽트, 동기적 인터럽트라고도 불리며, Trap, Exception이라고도 불린다. 구분이 명확하지 않은 것 같다. 
+ Exception
  프로그램이 허용되지 않은 연산을 수행하려고 할 때, 자동적으로 발생하는 interrupt이다.  예를 들어 0으로 나누기, 권한 없는 메모리 참조(page fault) 등의 상황에서 발생한다. 
+ System call
  프로세스가 os의 서비스를 요청하기 위해 커널의 함수를 호출하는 경우 발생하는 interrupt





#### Interrupt의 발생 및 처리

+ 인터럽트의 발생은 I/O device에 의한 h/w interrupt, exception이나 system call에 의한 s/w interrupt에 의해 발생하고, 발생한 인터럽트에 대해 CPU가 인터럽트 라인을 통해 인터럽트를 확인하고 Interrupt vector와 Interrupt handler를 통해 상황에 맞는 인터럽트를 처리한다. 
+ Interrupt vector
  여러 가지 인터럽트 상황에 대해 해당 인터럽트 발생 시 처리해야 할 루틴의 주소를 담고 있는 테이블
+ Interrupt handler
  실제 인터럽트를 처리하기 위한 루틴으로, 인터럽트 서비스 루틴이라고도 한다.

* [x] PC값의 변화 : current program -> Interrupt vector -> ISR  -> next instruction  













































---

###### 참고

+ [adam2님의 블로그](https://velog.io/@adam2/%EC%9D%B8%ED%84%B0%EB%9F%BD%ED%8A%B8)

+ [양햄찌가 만드는 세상](https://jhnyang.tistory.com/167)

+ [Easy is perfect](http://melonicedlatte.com/computerarchitecture/2019/02/12/213856.html)

+ [탕구리's 블로그](https://real-dongsoo7.tistory.com/m/93?category=784608)
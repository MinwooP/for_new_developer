OS

+ There is no universally accepted definition of OS
+ OS is a program
  1. that manages the __computer hardware__ -> 하드웨어 관리
  2. that controls the __execution of programs__ -> 프로그램 실행을 제어



DMA

+ Direct Memory Access

+ 특정 하드웨어 시스템이 __CPU와 독립적으로 메인 시스템 메모리__에 접근할 수 있게 해주는 컴퓨터 시스템의 기능이다.

+ 처음에 CPU가 I/O transaction을 initiate하면, device의 데이터는 device controller에 의해 local buffer로 이동한다.  device controller가 데이터의 한 블록을 이동시키는데 이 과정에서 DMA로 인해 __CPU의 개입이 필요없게__ 된다. CPU에서는 데이터 이동이 완료되었다는 단 한 번의 interrupt만 발생한다. 데이터가 전송되는 동안 __CPU는 다른 작업을 수행할 수 있게 되어__ 효율성이 높아진다. 

+ DMA controller가 bus를 제어하고 I/O와 memory 정보를 직접 전송한다.

  > PIO란?
  >
  > Program Input/output 
  >
  > DMA의 반대개념으로, 장치들 사이에 모든 데이터가 __CPU를 거쳐가는 방식__이다.
  >
  > DMA는 PIO의 단점을 보완하기 위해 고안된 기능이다. 




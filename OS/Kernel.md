# Microkernel VS Monolithic kernel

### monolithic kernel

+ Application을 제외한 모든 system 관련 기능들(VFS, IPC, File system)을 커널이 관리하며 각 영역들은 단계적으로 나뉘어 있다. 
+ 따라서 커널의 크기가 크지만, 시스템 자원을 보다 효율적으로 관리한다.
+ system call을 이용해 microkernel에 비해 빠른 성능
+ 각 component간의 커뮤니케이션이 효율적이다.
+ device dricer를 추가/삭제하려면 커널을 재빌드 해야 한다. 또 하나가 죽으면 전체 커널 시스템이 죽는다.
+ Unix, Linux



### microkernel

+ 핵심적인 기능(스케줄링, 메모리관리 등)만 커널에 담고 나머지는 제외해 가볍게 만든 커널이다.
+ 기존의 monolithic kernel이 갖고 있던 시스템 기능들(VFS, IPC, Device driver)은 커널 위의 서버의 형태로 존재한다. 즉, File system이나 Driver가 user space에 들어간다.
+ 서버를 추가하는 방식이기 때문에 기능을 추가하기 쉽고, 시스템이 견고하며 리얼타임성이 높다.
+ 시스템 기능들이 서버의 형태로 존재하기 때문에 커뮤니케이션 오버헤드가 있다. 
+ 하나의 서비스가 죽더라도 커널 전체가 panic 되지는 않는다. 
+ 리얼 타임성이 중요한 임베디드 시스템에서 주로 사용된다.
+ Windows NT, MacOS X 



### monolithic kernel VS microkernel

<img src = "https://user-images.githubusercontent.com/31370590/123578882-ba811f00-d811-11eb-9ecd-4a58b1efe3fe.png" width = "650" height = "400">





###### 참고

+ [아는 개발자](https://selfish-developer.com/entry/%EB%AA%A8%EB%86%80%EB%A6%AC%EC%8B%9DMonolithic-kernel%EA%B3%BC-%EB%A7%88%EC%9D%B4%ED%81%AC%EB%A1%9CMicro-%EC%BB%A4%EB%84%90)

  
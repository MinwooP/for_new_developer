# UNIX System Programming

## CH2

### UNIX file access primitives

+ UNIX 커널에 의해 제공되는 I/O 설비에 직접 접근을 제공하는 system call 들의 집합
+ 다른 파일 접근방식은 궁극적으로 이들에 기반하고 있음

1. open
2. creat
3. close
4. read
5. write
6. lseek
7. unlink
8. remove
9. fcntl

<br>

<br>

#### UNIX file access primitives example)

```c
/* a rudimentary example program */

/* these header files are discussed below */
#include <fcntl.h>
#include <unistd.h>

main()
{
    int fd;
    ssize_t nread;
    char buf[1024];

    /* open file “data” for reading */
    fd = open(“data”, O_RDONLY); 

    /* read in the data */
    nread = read(fd, buf, 1024);

    /* close the file */
    close(fd);
}

```

+ `   fd = open(“data”, O_RDONLY); ` 
  + `data` => 현재 디렉토리에 있는 `data` file을 open한다. 
  + `O_RDONLY` => 헤더파일 `<fcntl.h>`에 정의된 정수형 상수로서 파일을 **읽기 전용**으로 연다. 
  + `fd` => file open에 성공하면 정수의 `file desciptor` 값 반환
    + file descriptor 
      + 시스템에 의해 결정되는 음이 아닌 정수값으로 오픈된 파일을 식별하고, read, write, lseek, close와 같은 다른 file access primitives에 인수로써 전달된다. 
      + open에 실패하면 -1을 리턴한다. 

<br>

+ ` nread = read(fd, buf, 1024);`

  + fd로 식별되는 파일로부터 가능하면 1024 byte의 문자를 읽어서 buf에 저장하라

  + `nread` => 실제로 읽은 문자 byte의 수

  + file access primitives는 문자 또는 바이트의 단순한 선형 열(linear seqeunce)만을 다룬다

    => read sysem call은 정수값의 문자 표현을 컴퓨터 내부에서 사용되는 형태로 바꾸어주지 않는다. 

    => 

<br>

+ `ssize_t nread`

  + system call을 안전하게 사용할 수 있게 하기 위해 정의된 다양한 특수 타입의 첫 번째 예이다. 

  + 이는 통상 기본 정수 타입으로 처리된다.

<br>

<br>

------

#### open system call

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char* pathname, int flags, [mode_t mode]);
```

+ `const char* pathname`

  + open될 file의 경로를 나타내는 문자열에 대한 포인터

  + 절대 경로 혹은 상대 경로가 될 수 있다.

    ex) 

    + /usr/keith/junk

    + keith/junk
    + junk

<br>

+ `int flags`
  + 접근 방식을 지정
    + `O_RDONLY` : 읽기 전용
    + `O_WRONLY` : 쓰기 전용
    + `O_RDWR` : 읽기, 쓰기 전용
  + `flags`의 값은 `<fcntl.h>`내에 정의된 상수값으로 취해지며, 이 값은 `<fcntl.h>`에서 전처리 명령어 `#define`에 의해 정의된다.

<br>

+ `[mode_t mode]`
  + 생략해도 되는 인수로 `O_CREAT` flag와 함께 사용된다. 

<br>

+ 리턴값 filedes
  + 음이 아닌 정수의 file descriptor 값을 가진다.
  + `open()`을 호출한 processs에 의해 현재 file desciptor로 사용되지 않는 음이 아닌 가장 작은 정수 값을 할당한다. 
  + 프로그래머는 사실 이러한 내용을 알 필요가 없다. 
  + 파일이 존재하지 않을 경우 `-1`을 반환한다. 

<br>

+ open system call example

```c
#include <stdlib.h>	/* exit() */
#include <fcntl.h>	/* open() */

char *workfile = “junk”;

main()
{
    int fd;
    if( (fd = open(workfile, O_RDWR)) == -1)
    {
        printf(“Couldn’t open %s\n”, workfile);
        exit(1);
    }

    exit(0);
}
```

+ 오류가 발생할 때는 인수를 1로 하고, 성공적으로 종료될때는 0으로 하여 `exit`을 사용하는 것에 유의하라. 이것은 UNIX 규약에 따른 것이고, 좋은 프로그래밍 습관이다. `exit`에 전달되는 인수(프로그램의 종료상태)는 수행이 끝난 뒤에 접근 가능하다. 

<br>

+ 다양한 `flags`를 이용한 open system call

  + `filedes = open("/tmp/newfile", O_WRONLY | O_CREAT, 0644)`

    => 만일 `tmp/newfile`이 이미 존재하지 않는다면, 길이가 0인 파일로 새로 생성되어, **쓰기 전용**으로 열릴 것이다.

  <br>

  + `filedes = open(filename, O_RDWR | O_CREAT, PERMS)`

    => 파일이 존재할 경우, `O_CREAT`이 지정되지 않은 것처럼 쓰기 전용으로 열리고

    ​	 file이 존재하지 않는다면, 파일을 생성하고 쓰기 전용?

  <br>

  + `fd = open("lock", O_WRONLY | O_CREAT | O_EXCL, 0644)`

    => 파일이 존재할 경우, open 호출은 실패

    ​	 파일이 존재하지 않을 경우, permission 0644와 쓰기 전용으로 파일을 생성

  <br>

  + `fd = open("lock", O_WRONLY | O_CREAT | O_TRUNC, 0644)`

    => 파일이 존재할 경우 파일을 0byte로 자르고 open

    ​	 파일이 존재하지 않을 경우, 새로 만들어서 open

<br>

<br>

--------

#### creat system call

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int creat(const char* pathname, mode_t mode);
```

+ creat system call은 파일을 생성하는 대안적 방법으로 사용될 수 있다. 실제로는, 원래 creat가 파일을 생성하는 방법이었으나 이제는 다소 중복된 감이 있으며, **open보다 제어 기능이 떨어진다.**

  <br>

+ open과 마찬가지로, **파일이 존재한다면** 두 번째 인수인 `mode`는 무시된다. 하지만 open과 달리, creat는 기존 파일의 file descriptor를 return 하기 전에, **파일을 항상 잘라버린다.** 

  `filedes = creat("/tmp/newfile", 0644)`와

  `filedes = open("/tmp/newfile", O_WRONLY | O_CREAET | O_TRUNC, 0644);`는 서로 같은 명령이다.

  <br>

+ creat는 파일을 항상 **쓰기 전용**으로 연다. 예를 들면, creat으로 파일을 생성한 후, 그 파일에 자료를 쓰고, 뒤로 되돌아가 다시 그 파일로부터 읽을 수는 없다. 이를 위해서는 반드시 그 파일을 닫고 open으로 다시 열어야 한다. 

<br>

<br>

--------

#### close system call

```c
#include <unistd.h>

int close(int filedes);
```

+ close system call은 닫혀질 file descriptor를 인수로 취한다. 이는 앞서 호출된 open이나 creat에 의해서 만들어진다.
+ 호출에 성공하면, 즉 파일이 성공적으로 닫힌다면 0을 반환하고, 오류가 발생하면 -1을 반환한다.

<br>

<br>

-----

#### read system call

```c
#include <unistd.h>

ssize_t read(int filedes, void *buffer, size_t n)
```

+ 파일의 current file position으로부터 n byte만큼 내용을 읽고, file position을 업데이트 하고 읽은 내용을 buffer로 복사한다. 

+ `int filedes` 

  + 이전의 open 또는 creat 호출로부터 얻은 file descriptor

+ `void *buffer` 

  + 자료가 복사되어질 문자 배열에 대한 포인터, 대부분 이것은 배열 자체의 이름이다. 

  + 버퍼가 어느 타입의 데이터라도 저장할 수 있음을 의미함.
  + 버퍼는 보통 `char`의 배열이지만, 사용자가 정의한 struct가 될 수도 이다.

+ `size_t n`

  + 파일로부터 읽혀질 바이트의 수
  + 양의 정수(size_t 타입으로 정의)

+ read의 return 값 

  + 실제로 읽힌 바이트의 수를 나타낸다.

  + 보통 이는 프로그램에 의해 요청된 문자의 수인 n

  + read의 경우, 시스템은 각 호출 후에 읽혀진 바이트 수만큼 file pointer를 전진시킨다. 

    > 시스템은 **읽기-쓰기 포인터** 혹은 **파일 포인터**인 - 를 사용하여 파일 안에서의 프로세스의 위치를 관리한다. 이 포인터는 특정 file descriptor를 통해 **읽혀지거나 쓰여질 파일의 다음 바이트 위치**를 기록한다. 

  + 파일이 이미 읽기전에 endoffile에 도달했다면, 아무것도 읽기 못함 -> 0 return;

    => read의 리턴 값이 0인가를 조사하는 것이 파일의 끝을 조사하는 보통의 방법이다.

<br>

#### read system call이 실행될  때 OS내부에서의 변화

<img src = "https://user-images.githubusercontent.com/31370590/133953074-67afa8d4-061a-4ec0-86c0-c6ade719dbe5.PNG" width = "600" height = "400">

+ user program에서 file을 open하면 File descriptor table을 생성한다.
+ File descriptor table의 한 요소가 File table을 가리키고, File table의 마지막 위치가 disk의 file을 가리킨다.
+ File table의 `count`값은 현재 이 file table을 가리키는 file descriptor의 개수를 나타냄. 이는 여러개 일 수 있음.
+ File table의 file offset이 현재 file의 file position pointer의 값을 나타냄.

<br>

<br>

-----

#### write system call

```c
#include <unistd.h>

ssize_t write(int filedes, const void *buffer, size_t n)
```

+ buffer로부터 n byte만큼 내용을 읽어, file로 복사한다. 

<br>

<br>

#### copy file 예시

```c
#define BUFSIZE 512  /* 읽혀질 덩어리의 크기 */
#define PERM 0644	 /* 새 파일의 file permission */

int copyfile ( const char *name1, const char *name2){
    int infile, outfile;
    ssize_t nread;
    char buffer[BUFSIZE];	/* BUFSIZE : 512 */

    if ( (infile = open (name1, O_RDONLY ) )== -1) // 파일1 읽기 전용으로 open
	return(-1); /* file1 open error */

    /* FMODE : O_WRONLY｜O_CREAT｜O_TRUNC */  
    /* 파일이 존재할 경우 파일을 0byte로 자르고 open
	   파일이 존재하지 않을 경우, 새로 만들어서 open */
    if ( (outfile = open (name2, FMODE, PERM) )== -1){  // 파일 2 open
        close (infile);
        return (-2); /* file2 open error */
    }
    
    while ( (nread = read (infile, buffer, BUFSIZE) ) > 0){
        if ( write(outfile, buffer, nread) < nread ){ // 다 적었으면 
	   close (infile);
	   close (outfile);
	   return (-3); 		/* 쓰기 오류 */
        }
    }

    close (infile);
    close (outfile);

    if ( nread == -1)  return (-4)	/* 마지막 읽기에서 오류 발생 */
    else   return (0); 		/* 만사가 잘 되었음*/
}
```

+ 한 파일의 내용을 다른 파일로 복사하는 함수

+ 사용 예시

  `retcode = copyfile("squarepeg", "roundhole");`

  => squarepeg라는 파일의 내용을 roundhole로 복사한다.

<br>

#### read, write의 효율성

+ `$ time ./copyfile`

  => UNIX의 time 명령으로 생성된 프로그램의 수행시간을 측정

<br>

+ `copyfile`이라는 코드? or 실행 파일? or 프로그램?

```c
// ~ 
main() {
    copyfile("test.in", "test.out");
}
// ~ copy file 함수 정의 ~
```

<br>

+ **실행 결과**

<img src = "https://user-images.githubusercontent.com/31370590/133952292-b9b8964f-662c-41b9-ae5d-6f45c3d9f86f.PNG" width = "600" height = "300">  

+ Real time : 프로세스의 수행에 소요된 실제로 경과된 시간

+ User time : 시스템 호출을 제외한 프로그램 부분에 의해 소요된 시간의 양인 사용자 시간

+ System time : 커널이 시스템 호출을 처리하는데 소요된 시간의 양

+ User time + System time = Real time 이 아닌 이유

  => UNIX System은 많은 프로세스를 동시에 실행시키기 때문에, 시스템이 전체 수행시간 동안 당신의 프로그램만 실행시키지 않는다.

<br>

+ 실행결과 해석

  + 한번에 한 바이트씩 읽고 쓰는 경우 성능이 형편 없음

  + BUFSIZE를 증가시키면 성능이 크게 향상된다.

    => BUFSIZE가 512, 4096, 8192 바이트 일 때의 결과에서 보듯, BUFSIZE가 **multiple of system's natural disk blocking factor**(시스템의 자연적 디스크 블록킹 인수의 배수)일 때 성능이 가장 좋다.

  + 효율성 향상의 대부분은 단순히 **system call의 호출 횟수를 줄이는데서** 얻어진다. 

    => 시스템 호출이 발생할 때 program과 kernel 사이의 mode 전환에 비교적 많은 비용이 들 수 있다.

<br>

+ `write` system call은 너무 빠르다. 

  + When you issue a write system call, it does not perform the write and then return.

  + It just **transfer the data to a *buffer cache* in the kernel and then returns** => delayed writing

    => 4K가 꽉 차야

  + However, if there is a disk error, or if the kernel stops for any reason, then the game is up. We discover that the data we “wrote” isn’t on the disk at all.

<br>

<br>

-----

#### lseek system call

```c
#include <unistd.h>

/* the character l in the name lseek means “long integer” */
off_t lseek(int filedes, off_t offset, int start_flag);
```

+ **읽기-쓰기 포인터, 즉 다음에 읽거나 쓸 바이트의 위치를 변경**한다.

+ filedes의 file pointer를 **`start_flag`으로부터 `offset`만큼 옮긴다**.

+ Arguments

  + filedes : file descriptor ( obtained from open or creat)

  + offset : number of bytes from start_flag

  + start_flag : starting position

    + SEEK_SET	#0  => 파일의 시작 위치 

      SEEK_CUR   #1  => 파일의 현재 위치

      SEEK_END   #2  => end of file

      <img src = "https://user-images.githubusercontent.com/31370590/133954185-c49f009d-4fc3-46ab-ad04-deb7f74663ce.PNG" width = "300" height = "150">

  + start_flag에 의해 지시된 시작점으로 부터 거꾸로 움직이는 것이 가능하다. 즉, offset에 음수 값을 넣을 수 있다. 하지만, 파일의 시작점보다 더 앞으로 움직일 때에만 오류가 발생한다. 파일의 끝보다 더 뒤의 위치를 지정하는 것도 가능하다.


<br>

#### lseek system call example

```c
off_t nepos;

newpos = lseek(fd, (off_t)-16, SEEK_END);
```

+ file pointer의 위치를 파일의 끝에서부터 16 byte 전으로 옮긴다.

<br>

```c
fd = open(fname, O_RDWR);
lseek(fd, (off_t)0, SEEK_END);
write(fd, outbuf, OBSIZE);

	==
       
fd = open(fname, O_WRONLY|O_APPEND);
write(fd, outbuf, OBSIZE);
```

+ file을 열고, filepointer를 file의 끝으로 옮기고, 쓴다
+ file을 `O_APPEND`로, 즉 이어쓰기 모드로 연다. 그리고 쓴다.

<br>

```c
off_t filesize;
int filedes;

filesize = lseek(fd, (off_t)0, SEEK_END); /* filesize is the size of file */
```

+ file의 크기가 700K라면, endoffile은 700K를 가리키고 있을 것이므로 

<br>

<br>

#### lseek example)

+ 투숙한 사람들의 이름을 기록한 `residents`라는 파일이 있다고 가정
+ 첫째줄은 1호실에 투숙한 사람의 이름, 둘째줄은 2호실에 투숙한 사람의 이름
+ 각 줄의 길이는 정확히 41개의 문자 , 처음 40개 문자는 이름을 수록, 41번째 문자는 개행문자로 UNIX cat 명령으로 파일을 표시할 수 있게 해준다. 
+ `getoccupier` 함수는 정수형 방 번호가 주어지면, 투숙객 이름의 첫 바이트의 위치를 계산하고, 그 위치로 이동한 후 거기에 있는 자료를 읽는다. 리턴값은 투숙객 이름을 수록하는 문자열에 대한 포인터거나, 오류시는 null pointer
+ file descriptor 변수 infile에 초기값 -1을 부여함으로써 파일이 한번만 open되는지 확인

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define NAMELength 41

char namebuf[NAMELENGTH]; /* 각 투숙객의 이름을 담을 버퍼 */
int file = -1 /* 파일 디스크립터 */
    
char *getoccupier(int roomno){
    off_t offset;
    ssize_t nread;
    
    /* 파일을 처음으로 개방 */
    if(infile == -1 && 
       (infile = open ("residents",  O_RDONLY)) == -1){
        return (NULL);  // 파일 OPEN 불가능
    }
    offset = (roomno - 1) * NAMELENGTH;
    // file pointer를 주어진 roomno번째 줄로 이동. 거기부터 읽어야 그 roomno에 해당하는 투숙객 이름이 시작 
    
    /*방의 위치를 찾아 투숙객의 이름을 읽는다*/
    if(lseek(infile, offset, SEEK_GET) == -1)
        return (NULL);
    
    if( (nread = read(infile, namebuf, NAMELENGTH)) <= 0)
        return (NULL);
    
    /* 개행 문자를 널 종결자로 대체하여 하나의 스트링을 생성 */
    namebuf[nread-1] = '\0';
    
    return(namebuf);
}
```

<br>

<br>

#### 한 file의 끝에 자료를 추가하기

`lseek(filedes, (off_t)0, SEEK_END);`

위의 코드를 이용하여 파일의 끝에 자료를 추가할 수도 있지만,

open 함수에 추가 플래그 `O_APPEND`를 사용하는 것이다. 
만일 `O_APPEND`가 설정되어 있으면, **write할 때마다 file poiner가 file의 끝에 위치**하게 된다. 
이것은 프로그래머가 file 내용을 예기치 못한 사고로부터 보호하고, 자료를 단지 file의 끝에 추가하기를 원할 때 유용하다. 

`filedes = open("yetanother", O_WRONLY | O_APPEND);`

<br>

그리고 이후, write는 자료를 file의 끝에 추가할 것이다. 

`write(filedes, appbuf, BUFSUZE)`

<br>

<br>

-----

#### unlink & remove => file의 제거

한 file을 시스템으로부터 제거하는 데는 두 가지 방법이 있다. `unlink`와 `remove` 호출이다.

```c
#include <unistd.h>
int unlink(const char *pathname);

#include <stdio.h>
int remove(const char *pathname);
```

+ 두 함수 모두 하나의 인수(제거될 파일의 이름의 스트링)을 취한다. 

  `unlink("\tmp\usedfile");`

  `remove("\tmp\usedfile");`

<br>

<br>

#### fcntl

+ 이미 열려 있는 file에 대해 어느 정도의 제어를 제공하기 위함
+ fcntl은 잘 정의된 기능을 가진 system call이 아니라 여러 기능을 수행하는 다소 이상한 system call이다.



------

#### dup, dup2

+ file descriptor를 복제하는 system call

```c
#include <unistd.h>

int dup(int filedes);
int dup2(int filedes, int filedes2);

Both return: new file descriptor if OK, -1 on error
```











------

### 참고

+ `ssize_t`

  <unistd.h> 헤더파일은 ssize_t type을 사용하기 위해 include하는 것.

  ssize_t type은 사실 int type, 

  \#typedef ssize_t int 라는 명령이 <sys/types.h>에 정의되어있음

  ssize_t 처럼 _t로 끝나는 data type을 primitive system data types 이라고 하고 이게 사용되는 이유는

  유닉스는 여러 버전이 있는데 어떤 버전에서는 read의 return type을 short로 쓰기도 하고, 어떤 버전에서는 long을 쓰기도 한다. 이를 표준화하기 위해 read의 return type을 하나로 통일했다.

  \#typedef ssize_t int

  \#typedef ssize_t short 

  이렇게 각 버전에 정의되어있는 것. 그리고 이것이 <sys.types.h>에 저장되어있음. 그리고 <unistd.h>를 include하면 <sys.types.h>는 <unistd.h>에 포함되어 있으므로 자동 include 됨


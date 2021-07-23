# 🔥 Backup

## 🚩 용어정리

+ local repository
+ remote repository
+ push
+ clone
+ pull
+ 백업의 중심 -> remote repository



## 🚩 공부의 방향

|      | Local => Remote | Remote => local |
| ---- | --------------- | --------------- |
| HTTP |                 |                 |
| SSH  |                 |                 |



## 🚩 원격 저장소와 연결

+ push an existing  repositoty from  the command line
  + `git remote add [원격저장소의 별명] [https주소]` : 현재 지역 저장소와 원격 저장소 연결, 보통 `origin` 사용
  + `git remote` => origin으로 나옴.
  + `git  remote -v` => 주소가 나옴.

+ 하나의 local 저장소에 여러개의 remote 저장소 연결 가능



## 🚩 git push

+ `git push` 
  +  `git push --set-upstream origin master` : 지역 저장소는 여러개의 원격 저장소와 연결될 수 있는데, 그 중 어떤 원격저장소와 기본적으로 연결시킬 것인지를 세팅 => 이는 처음에 딱 한번만 쳐주면 됨
  + 앞으로, `git push`라고 하면, `git push origin master`가 실행되는 것



## 🚩 git clone

+ `git clone [https주소]` => 새로운 디렉토리 이름으로 지역 저장소를 생성하고 싶다면 https주소뒤에 원하는 디렉토리 이름을 써주면 된다.  

  

#### git clone으로 받은 저장소에 브랜치로 이동하기

+ git에서 `git clone [https 주소]`로 저장소를 내려받으면 저장소에 저장된 브랜치들을 사용할 수 있다. 그러나 처음에 `git branch`로 확인하였을 때, `master` branch만 보이고, 나머지 branch들은 확인할 수 없다.  

+ `git branch -a` 을 통해 브랜치들을 볼 수 있다.

  ```git
  $ git branch -a
  * master
    remotes/origin/HEAD -> origin/master
    remotes/origin/develop
    remotes/origin/feature/mingyeong
    remotes/origin/feature/minwoo
    remotes/origin/feature/김혜인
    remotes/origin/feature/오형석
    remotes/origin/master
  ```

+ `git branch -t [저장소이름]/[branch이름]` 을 통해 remote 저장소의 브랜치를 그래도 로컬 브랜치로 생성할 수 있다. 

  `git checkout -t `옵션을 이용하면, branch를 로컬에 생성함과 동시에 그 브랜치로 checkout 가능

  ```git
  $ git checkout -t origin/develop
  
  Switched to a new branch 'develop'
  Branch 'develop' set up to track remote branch 'develop' from 'origin'.
  ```

  



## 🚩 git pull

+ 어느 한쪽의 local 저장소에서 작업을 한후, `commit`, `push`
+ remote 저장소에 반영됨
+ 다른 쪽의 local 저장소에서 이를 **동기화**하려면, `git pull` 을 해야함. 

> SSH
>
> git hosting  기능들 자세히 살펴보기 - Issue tracker
>
> 백업 -> 협업

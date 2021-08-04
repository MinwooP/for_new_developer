# 🔥 Branch & Conflict

+ branch : 같은 뿌리에서 나왔지만 서로 다른 역사를 써가고 있는 버전들

+ conflict : 같은 파일인데 같은 부분이 수정되었다면,  

  > 충돌은 사고가 아니라 Git이 제공하는 가장 멋진 기능이다.



## 🚩 브랜치의 사용법

+ 고객사마다 다른 내용을 추가해야 하는 상황 
+ `$ git log --all --graph --oneline` :  각 버전이 한 줄로 간결하게 표시됨
+ `$ git branch [branch_name]`
+ `head -> master` : 현재 사용자가 master에 속해있는 상태이다. 
+ `$ git checkout [branch_name]` : 해당 브랜치로 checkout하면 **사용자의 working copy가 그 브랜치의 마지막 커밋 상태로 바뀐다.** 

```git
$ git log --all --graph --oneline
* 23b0d5e (HEAD -> ms) ms work 4
| * 75f0c51 (google) google work 4
|/
| * ed7bc5c (apple) apple work 4
|/
| * 3bb404f (master) master work 4
|/
* e033790 work3g
* d4c3092 work2
* b415f32 work1

// ms, google, appple, master 모두 work3이 부모이다. 
```





## 🚩 브랜치 병합

<img src = "https://user-images.githubusercontent.com/31370590/125619603-49a7a3ae-a4c0-4bf8-9778-355868521811.PNG" width = "600" height = "400">

+ `header -> [base]` 인 상태에서,  `$ git merge [merge_branch]`

  `$ git merge o2` `(header -> master)`

  ```git
  $ git log --all --graph --oneline
  *   d053bea (HEAD -> master) Merge branch 'o2' // o2.txt, master.txt, work.txt 
  |\
  | * 8c0aa74 (o2) o2 work 2 // o2.txt( o2 2 )
  * | d6fd50d master work 2  // master.txt( 2 )
  |/
  * 4e2cbb4 work 1 // work.txt ( 1 )
  ```



+  `merge` 했을 때 같은 파일 안에서 다른 부분 수정이 있을 때 알아서 합쳐줌



## Conflict 

<= 서로 다른 branch에서 같은 파일 안의 같은 부분을 수정 하고 merge 하려고 할 때, conflict 발생

1. master에서 첫번째 commit

   + `$ nano work.txt`  => `$ git add work.txt` => `$ git commit -m "work 1"`

     ```nano
     #title
     content
     
     
     
     #title
     content
     ```



2. o2 branch 생성

   + `$ git branch o2`

   

3. master에서 두 번째 commit

   + `$ nano work.txt` => `$ git commit -am "master work 2"`

     ```nano
     #title
     content
     
     master
     
     #title
     content
     ```



4. o2에서 두 번째 commit

   + `$ git checkout o2` => `$ nano work.txt` => `$ git commit -am "o2 work 2"`

     ```nano
     #title
     content
     
     o2
     
     #title
     content
     ```



5. master를 base로 o2 branch merge => conflict 발생

   + `$ git chekcout master` => `$ git merge o2` => `conflict 발생`  => 

     ```nano
     #title
     content
     
     <<<<<<< HEAD
     master
     =======
     o2
     >>>>>>> o2
     
     #title
     content
     ```

      

6. conflict 해결 

   + 사용자가 수동으로 코드 수정해줘야함 => `$ nano work.txt`

     ```nano
     #title
     content
     
     master, o2
     
     #title
     content
     ```

   + `$ git log --all --graph --oneline`

     ```nano
     *   35b6449 (HEAD -> master) Merge branch 'o2'
     |\
     | * b529e50 (o2) o2 work 2
     * | c1620ee master work 2
     |/
     * 4be7bd1 work 1
     ```




## 🚩 3 way merge

+ git은 어떻게 충돌을 파악하는가

  | here  | origin | there |
  | :---: | :----: | :---: |
  |   A   |   A    |   A   |
  | **H** |   B    |   B   |
  |   C   |   C    | **T** |
  | **H** |   D    | **T** |



+ merge

  | here | base | there |           2 way merge            |           3 way merge            |
  | :--: | :--: | :---: | :------------------------------: | :------------------------------: |
  |  A   |  A   |   A   |                A                 |                A                 |
  |  H   |  B   |   B   | <span style="color:red">?</span> |                H                 |
  |  C   |  C   |   T   | <span style="color:red">?</span> |                T                 |
  |  H   |  D   |   T   | <span style="color:red">?</span> | <span style="color:red">?</span> |

  git은 3 way merge 방식으로 merge를진행한다.



## 🚩 외부 도구를 이용한 병합, 보충

+ `git mergetool`  : 외부 도구를 실행하여 merge를 진행

  ex) p4merge

+ 보충
  + git flow
  + cherry pick
  + rebase 



## 🚩 reset vs checkout

+ HEAD, branch, commit과 checkout, reset

+ 우리가 저장소를 만들면 master branch가 생성이 되고,  우리가 어떤 작업을 하는 것은 기본적으로 master  branch 위에서 버전을 만들어 가는 것이다. 저장소를 만들면 HEAD가 생성이 되고, 이 HEAD는 master branch를 가리키게 된다. HEAD를 통해 현재 나의 저장소는 master branch에 checkout 되어 있구나를 알 수 있음 . 

+ `git checkout [branch_name]` : HEAD가 branch_name의 branch를 가리키도록 변경한다. 

+ HEAD가 branch가 아닌 특정 commit을 가리키고 있는 것을 `detached` 상태에 있다고 말한다. 

  

1. `git init` : 기본적으로 master branch가 생성이 되고, head는 master branch를 가리킴. 우리는 HEAD를 보고, 현재 저장소는 master branch에  checkout 되어있구나를 알 수 있음.   

   <img src = "https://user-images.githubusercontent.com/31370590/125761885-4ab4d148-eda8-4b4a-9fe2-a7ded681c8a3.PNG" width = "300" height = "400">  

<br>

2. `git commit -am "1"`  : master branch에서 버전을 생성하면, 현재 master branch가 1번 버전을 가리키게 되고, 이를 통해 우리는 현재 이 저장소가 master branch에 checkout 되있다는 것은 HEAD를 통해 알 수 있다.  그리고 현재 이 저장소가 어떤 버전 상태에 있는지를 알고 싶다면, HEAD가 가리키는 master가 가리키는 1이라는 버전을 통해 알 수 있다.  

   <img src = "https://user-images.githubusercontent.com/31370590/125762155-4cd9757a-dc74-41a9-bd12-bcbd856436fa.PNG" width = "300" height = "400">    

<br>

3. `git commit -am "2"` : 현재 이 저장소의 버전은 HEAD가 가리키는 master가 가리키는 2번 버전이다.   

     <img src = "https://user-images.githubusercontent.com/31370590/125763292-b9332fcb-3b60-48e1-a39f-26f8159b1462.PNG" width = "300" height = "400">     

<br>

4. `git branch google` : 이 **branch가 어떤 버전으로 시작할 것인가**를 결정해야 하는데, 그때 **HEAD가 가리키는 master가 가리키는 2번 버전으로 시작**한다.     

   <img src = "https://user-images.githubusercontent.com/31370590/125763837-9451f33e-0d7c-4c9c-b4fb-91b9ec34f6c4.PNG" width = "400" height = "400">     

<br>

5. `git checkout google` : HEAD가 google을 가리키도록 변경한다. 이를 통해, HEAD를 보고, HEAD가 google 이까 현재 google branch에 checkout 되어있구나~ 이 저장소의 최신 상태는 2번 버전이구나~를 알 수 있다.  

   <img src = "https://user-images.githubusercontent.com/31370590/125764232-7e33b201-1eba-4343-82b6-98a1a66b0b3f.PNG" width = "450" height = "400">     

<br>

6. `git commit -am "3"` : 3번이라는 버전이 생길 것이고,  이 3번 버전의 부모는 2번이고, 현재 google에 checkout 되어있는 상태로 버전을 만들었기 때문에, google 이라는 branch는 이제 3번 버전을 가리키게 됨. 이로써 master에서 시작한 google은 master와는 다른 버전을 가리키게 됨. 

   <img src = "https://user-images.githubusercontent.com/31370590/125764971-39a306cb-c5ba-4195-aabb-636e1a3c7fd6.PNG" width = "450" height = "400">      

<br>

7. `git checkout master` : HEAD가 가리키는 것을 master로 변경하는 것이고, master가 가리키고 있는 2번 버전을 저장소의 최신상태로 만든다.

<br>

8. `git checkout [1번커밋]` : HEAD는 branch가 아닌, 1번이라는 이름의 버전을 직접 가리킴. 이 저장소는 1번 저장소의 상태가 됨.    

   
   
   <img src = "https://user-images.githubusercontent.com/31370590/125765502-fc6af1af-dbf3-487c-b984-3ceb332e8e79.PNG" width = "450" height = "400">   

<br>

+ checkout vs reset

  + checkout : 무엇인가를 바꾸는 느낌
  + reset : 무엇인가를 지우는 느낌

  => **checkout은 HEAD를 제어한다.** reset은 HEAD가 branch를 가리키고 있는 동안은  branch를 제어한다.   

   <br>

  + ` git reset master` `(HEAD=>google)인 상태` => google이라는 branch가 master가 가리키고 있는 버전을 가리키도록 바꾼다. 이제 더이상 3번 커밋은  이제 google branch 소속이 아니기 때문에, 삭제의 느낌을 받게 된다.    

  <img src = "https://user-images.githubusercontent.com/31370590/125767322-8b61f64f-febb-4aaa-9b8a-ca6f5051de34.PNG" width = "500" height = "400"">

  

  + `git reset 1` : google이라는 현재 branch는 1번 커밋을 가리키게 되면서, 2번, 3번 commit은 이제 더이상 google의 소속이 아니니까 삭제의 느낌이 나는 것.   

    
    
    <img src = "https://user-images.githubusercontent.com/31370590/125767588-51a096d7-4f6c-4c63-818b-418f868d5592.PNG" width = "500" height = "400">     



<br>

> 우리 인생에도 branch가 있다면 얼마나 좋을까. 하지만 인생에는 버전만 있고 reset도 없고, branch는 더더욱 없다. 잃어버려야먄 그 소중함을 알게 되는 것들이 참 많다.


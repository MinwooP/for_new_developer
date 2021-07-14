# 🔥 Branch & Conflict

+ branch : 같은 뿌리에서 나왔지만 서로 다른 역사를 써가고 있는 버전들

+ conflict : 같은 파일인데 같은 부분이 수정되었다면,  

  > 충돌은 사고가 아니라 Git이 제공하는 가장 멋진 기능이다.



## 🚩 브랜치의 사용법

+ 고객사마다 다른 내용을 추가해야 하는 상황 
+ `$ git log --all --graph --oneline` :  각 버전이 한 줄로 간결하게 표시됨
+ `$ git branch [branch_name]`
+ `head -> master` : 현재 사용자가 master에 속해있는 상태이다. 
+ `$ git checkout [branch_name]` : 해당 브랜치로 checkout하면 사용자의 working copy가 그 브랜치의 마지막 커밋 상태로 바뀐다. 

```git
$ git log --all --graph --oneline
* 23b0d5e (HEAD -> ms) ms work 4
| * 75f0c51 (google) google work 4
|/
| * ed7bc5c (apple) apple work 4
|/
| * 3bb404f (master) master work 4
|/
* e033790 work3
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

     


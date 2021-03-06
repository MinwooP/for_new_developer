# ๐ฅ Branch & Conflict

+ branch : ๊ฐ์ ๋ฟ๋ฆฌ์์ ๋์์ง๋ง ์๋ก ๋ค๋ฅธ ์ญ์ฌ๋ฅผ ์จ๊ฐ๊ณ  ์๋ ๋ฒ์ ๋ค

+ conflict : ๊ฐ์ ํ์ผ์ธ๋ฐ ๊ฐ์ ๋ถ๋ถ์ด ์์ ๋์๋ค๋ฉด,  

  > ์ถฉ๋์ ์ฌ๊ณ ๊ฐ ์๋๋ผ Git์ด ์ ๊ณตํ๋ ๊ฐ์ฅ ๋ฉ์ง ๊ธฐ๋ฅ์ด๋ค.



## ๐ฉ ๋ธ๋์น์ ์ฌ์ฉ๋ฒ

+ ๊ณ ๊ฐ์ฌ๋ง๋ค ๋ค๋ฅธ ๋ด์ฉ์ ์ถ๊ฐํด์ผ ํ๋ ์ํฉ 
+ `$ git log --all --graph --oneline` :  ๊ฐ ๋ฒ์ ์ด ํ ์ค๋ก ๊ฐ๊ฒฐํ๊ฒ ํ์๋จ
+ `$ git branch [branch_name]`
+ `head -> master` : ํ์ฌ ์ฌ์ฉ์๊ฐ master์ ์ํด์๋ ์ํ์ด๋ค. 
+ `$ git checkout [branch_name]` : ํด๋น ๋ธ๋์น๋ก checkoutํ๋ฉด **์ฌ์ฉ์์ working copy๊ฐ ๊ทธ ๋ธ๋์น์ ๋ง์ง๋ง ์ปค๋ฐ ์ํ๋ก ๋ฐ๋๋ค.** 

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

// ms, google, appple, master ๋ชจ๋ work3์ด ๋ถ๋ชจ์ด๋ค. 
```





## ๐ฉ ๋ธ๋์น ๋ณํฉ

<img src = "https://user-images.githubusercontent.com/31370590/125619603-49a7a3ae-a4c0-4bf8-9778-355868521811.PNG" width = "600" height = "400">

+ `header -> [base]` ์ธ ์ํ์์,  `$ git merge [merge_branch]`

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



+  `merge` ํ์ ๋ ๊ฐ์ ํ์ผ ์์์ ๋ค๋ฅธ ๋ถ๋ถ ์์ ์ด ์์ ๋ ์์์ ํฉ์ณ์ค



## Conflict 

<= ์๋ก ๋ค๋ฅธ branch์์ ๊ฐ์ ํ์ผ ์์ ๊ฐ์ ๋ถ๋ถ์ ์์  ํ๊ณ  merge ํ๋ ค๊ณ  ํ  ๋, conflict ๋ฐ์

1. master์์ ์ฒซ๋ฒ์งธ commit

   + `$ nano work.txt`  => `$ git add work.txt` => `$ git commit -m "work 1"`

     ```nano
     #title
     content
     
     
     
     #title
     content
     ```



2. o2 branch ์์ฑ

   + `$ git branch o2`

   

3. master์์ ๋ ๋ฒ์งธ commit

   + `$ nano work.txt` => `$ git commit -am "master work 2"`

     ```nano
     #title
     content
     
     master
     
     #title
     content
     ```



4. o2์์ ๋ ๋ฒ์งธ commit

   + `$ git checkout o2` => `$ nano work.txt` => `$ git commit -am "o2 work 2"`

     ```nano
     #title
     content
     
     o2
     
     #title
     content
     ```



5. master๋ฅผ base๋ก o2 branch merge => conflict ๋ฐ์

   + `$ git chekcout master` => `$ git merge o2` => `conflict ๋ฐ์`  => 

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

      

6. conflict ํด๊ฒฐ 

   + ์ฌ์ฉ์๊ฐ ์๋์ผ๋ก ์ฝ๋ ์์ ํด์ค์ผํจ => `$ nano work.txt`

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




## ๐ฉ 3 way merge

+ git์ ์ด๋ป๊ฒ ์ถฉ๋์ ํ์ํ๋๊ฐ

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

  git์ 3 way merge ๋ฐฉ์์ผ๋ก merge๋ฅผ์งํํ๋ค.



## ๐ฉ ์ธ๋ถ ๋๊ตฌ๋ฅผ ์ด์ฉํ ๋ณํฉ, ๋ณด์ถฉ

+ `git mergetool`  : ์ธ๋ถ ๋๊ตฌ๋ฅผ ์คํํ์ฌ merge๋ฅผ ์งํ

  ex) p4merge

+ ๋ณด์ถฉ
  + git flow
  + cherry pick
  + rebase 



## ๐ฉ reset vs checkout

+ HEAD, branch, commit๊ณผ checkout, reset

+ ์ฐ๋ฆฌ๊ฐ ์ ์ฅ์๋ฅผ ๋ง๋ค๋ฉด master branch๊ฐ ์์ฑ์ด ๋๊ณ ,  ์ฐ๋ฆฌ๊ฐ ์ด๋ค ์์์ ํ๋ ๊ฒ์ ๊ธฐ๋ณธ์ ์ผ๋ก master  branch ์์์ ๋ฒ์ ์ ๋ง๋ค์ด ๊ฐ๋ ๊ฒ์ด๋ค. ์ ์ฅ์๋ฅผ ๋ง๋ค๋ฉด HEAD๊ฐ ์์ฑ์ด ๋๊ณ , ์ด HEAD๋ master branch๋ฅผ ๊ฐ๋ฆฌํค๊ฒ ๋๋ค. HEAD๋ฅผ ํตํด ํ์ฌ ๋์ ์ ์ฅ์๋ master branch์ checkout ๋์ด ์๊ตฌ๋๋ฅผ ์ ์ ์์ . 

+ `git checkout [branch_name]` : HEAD๊ฐ branch_name์ branch๋ฅผ ๊ฐ๋ฆฌํค๋๋ก ๋ณ๊ฒฝํ๋ค. 

+ HEAD๊ฐ branch๊ฐ ์๋ ํน์  commit์ ๊ฐ๋ฆฌํค๊ณ  ์๋ ๊ฒ์ `detached` ์ํ์ ์๋ค๊ณ  ๋งํ๋ค. 

  

1. `git init` : ๊ธฐ๋ณธ์ ์ผ๋ก master branch๊ฐ ์์ฑ์ด ๋๊ณ , head๋ master branch๋ฅผ ๊ฐ๋ฆฌํด. ์ฐ๋ฆฌ๋ HEAD๋ฅผ ๋ณด๊ณ , ํ์ฌ ์ ์ฅ์๋ master branch์  checkout ๋์ด์๊ตฌ๋๋ฅผ ์ ์ ์์.   

   <img src = "https://user-images.githubusercontent.com/31370590/125761885-4ab4d148-eda8-4b4a-9fe2-a7ded681c8a3.PNG" width = "300" height = "400">  

<br>

2. `git commit -am "1"`  : master branch์์ ๋ฒ์ ์ ์์ฑํ๋ฉด, ํ์ฌ master branch๊ฐ 1๋ฒ ๋ฒ์ ์ ๊ฐ๋ฆฌํค๊ฒ ๋๊ณ , ์ด๋ฅผ ํตํด ์ฐ๋ฆฌ๋ ํ์ฌ ์ด ์ ์ฅ์๊ฐ master branch์ checkout ๋์๋ค๋ ๊ฒ์ HEAD๋ฅผ ํตํด ์ ์ ์๋ค.  ๊ทธ๋ฆฌ๊ณ  ํ์ฌ ์ด ์ ์ฅ์๊ฐ ์ด๋ค ๋ฒ์  ์ํ์ ์๋์ง๋ฅผ ์๊ณ  ์ถ๋ค๋ฉด, HEAD๊ฐ ๊ฐ๋ฆฌํค๋ master๊ฐ ๊ฐ๋ฆฌํค๋ 1์ด๋ผ๋ ๋ฒ์ ์ ํตํด ์ ์ ์๋ค.  

   <img src = "https://user-images.githubusercontent.com/31370590/125762155-4cd9757a-dc74-41a9-bd12-bcbd856436fa.PNG" width = "300" height = "400">    

<br>

3. `git commit -am "2"` : ํ์ฌ ์ด ์ ์ฅ์์ ๋ฒ์ ์ HEAD๊ฐ ๊ฐ๋ฆฌํค๋ master๊ฐ ๊ฐ๋ฆฌํค๋ 2๋ฒ ๋ฒ์ ์ด๋ค.   

     <img src = "https://user-images.githubusercontent.com/31370590/125763292-b9332fcb-3b60-48e1-a39f-26f8159b1462.PNG" width = "300" height = "400">     

<br>

4. `git branch google` : ์ด **branch๊ฐ ์ด๋ค ๋ฒ์ ์ผ๋ก ์์ํ  ๊ฒ์ธ๊ฐ**๋ฅผ ๊ฒฐ์ ํด์ผ ํ๋๋ฐ, ๊ทธ๋ **HEAD๊ฐ ๊ฐ๋ฆฌํค๋ master๊ฐ ๊ฐ๋ฆฌํค๋ 2๋ฒ ๋ฒ์ ์ผ๋ก ์์**ํ๋ค.     

   <img src = "https://user-images.githubusercontent.com/31370590/125763837-9451f33e-0d7c-4c9c-b4fb-91b9ec34f6c4.PNG" width = "400" height = "400">     

<br>

5. `git checkout google` : HEAD๊ฐ google์ ๊ฐ๋ฆฌํค๋๋ก ๋ณ๊ฒฝํ๋ค. ์ด๋ฅผ ํตํด, HEAD๋ฅผ ๋ณด๊ณ , HEAD๊ฐ google ์ด๊น ํ์ฌ google branch์ checkout ๋์ด์๊ตฌ๋~ ์ด ์ ์ฅ์์ ์ต์  ์ํ๋ 2๋ฒ ๋ฒ์ ์ด๊ตฌ๋~๋ฅผ ์ ์ ์๋ค.  

   <img src = "https://user-images.githubusercontent.com/31370590/125764232-7e33b201-1eba-4343-82b6-98a1a66b0b3f.PNG" width = "450" height = "400">     

<br>

6. `git commit -am "3"` : 3๋ฒ์ด๋ผ๋ ๋ฒ์ ์ด ์๊ธธ ๊ฒ์ด๊ณ ,  ์ด 3๋ฒ ๋ฒ์ ์ ๋ถ๋ชจ๋ 2๋ฒ์ด๊ณ , ํ์ฌ google์ checkout ๋์ด์๋ ์ํ๋ก ๋ฒ์ ์ ๋ง๋ค์๊ธฐ ๋๋ฌธ์, google ์ด๋ผ๋ branch๋ ์ด์  3๋ฒ ๋ฒ์ ์ ๊ฐ๋ฆฌํค๊ฒ ๋จ. ์ด๋ก์จ master์์ ์์ํ google์ master์๋ ๋ค๋ฅธ ๋ฒ์ ์ ๊ฐ๋ฆฌํค๊ฒ ๋จ. 

   <img src = "https://user-images.githubusercontent.com/31370590/125764971-39a306cb-c5ba-4195-aabb-636e1a3c7fd6.PNG" width = "450" height = "400">      

<br>

7. `git checkout master` : HEAD๊ฐ ๊ฐ๋ฆฌํค๋ ๊ฒ์ master๋ก ๋ณ๊ฒฝํ๋ ๊ฒ์ด๊ณ , master๊ฐ ๊ฐ๋ฆฌํค๊ณ  ์๋ 2๋ฒ ๋ฒ์ ์ ์ ์ฅ์์ ์ต์ ์ํ๋ก ๋ง๋ ๋ค.

<br>

8. `git checkout [1๋ฒ์ปค๋ฐ]` : HEAD๋ branch๊ฐ ์๋, 1๋ฒ์ด๋ผ๋ ์ด๋ฆ์ ๋ฒ์ ์ ์ง์  ๊ฐ๋ฆฌํด. ์ด ์ ์ฅ์๋ 1๋ฒ ์ ์ฅ์์ ์ํ๊ฐ ๋จ.    

   
   
   <img src = "https://user-images.githubusercontent.com/31370590/125765502-fc6af1af-dbf3-487c-b984-3ceb332e8e79.PNG" width = "450" height = "400">   

<br>

+ checkout vs reset

  + checkout : ๋ฌด์์ธ๊ฐ๋ฅผ ๋ฐ๊พธ๋ ๋๋
  + reset : ๋ฌด์์ธ๊ฐ๋ฅผ ์ง์ฐ๋ ๋๋

  => **checkout์ HEAD๋ฅผ ์ ์ดํ๋ค.** reset์ HEAD๊ฐ branch๋ฅผ ๊ฐ๋ฆฌํค๊ณ  ์๋ ๋์์  branch๋ฅผ ์ ์ดํ๋ค.   

   <br>

  + ` git reset master` `(HEAD=>google)์ธ ์ํ` => google์ด๋ผ๋ branch๊ฐ master๊ฐ ๊ฐ๋ฆฌํค๊ณ  ์๋ ๋ฒ์ ์ ๊ฐ๋ฆฌํค๋๋ก ๋ฐ๊พผ๋ค. ์ด์  ๋์ด์ 3๋ฒ ์ปค๋ฐ์  ์ด์  google branch ์์์ด ์๋๊ธฐ ๋๋ฌธ์, ์ญ์ ์ ๋๋์ ๋ฐ๊ฒ ๋๋ค.    

  <img src = "https://user-images.githubusercontent.com/31370590/125767322-8b61f64f-febb-4aaa-9b8a-ca6f5051de34.PNG" width = "500" height = "400"">

  

  + `git reset 1` : google์ด๋ผ๋ ํ์ฌ branch๋ 1๋ฒ ์ปค๋ฐ์ ๊ฐ๋ฆฌํค๊ฒ ๋๋ฉด์, 2๋ฒ, 3๋ฒ commit์ ์ด์  ๋์ด์ google์ ์์์ด ์๋๋๊น ์ญ์ ์ ๋๋์ด ๋๋ ๊ฒ.   

    
    
    <img src = "https://user-images.githubusercontent.com/31370590/125767588-51a096d7-4f6c-4c63-818b-418f868d5592.PNG" width = "500" height = "400">     



<br>

> ์ฐ๋ฆฌ ์ธ์์๋ branch๊ฐ ์๋ค๋ฉด ์ผ๋ง๋ ์ข์๊น. ํ์ง๋ง ์ธ์์๋ ๋ฒ์ ๋ง ์๊ณ  reset๋ ์๊ณ , branch๋ ๋๋์ฑ ์๋ค. ์์ด๋ฒ๋ ค์ผ๋จ ๊ทธ ์์คํจ์ ์๊ฒ ๋๋ ๊ฒ๋ค์ด ์ฐธ ๋ง๋ค.


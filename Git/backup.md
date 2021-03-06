# ๐ฅ Backup

## ๐ฉ ์ฉ์ด์ ๋ฆฌ

+ local repository
+ remote repository
+ push
+ clone
+ pull
+ ๋ฐฑ์์ ์ค์ฌ -> remote repository



## ๐ฉ ๊ณต๋ถ์ ๋ฐฉํฅ

|      | Local => Remote | Remote => local |
| ---- | --------------- | --------------- |
| HTTP |                 |                 |
| SSH  |                 |                 |



## ๐ฉ ์๊ฒฉ ์ ์ฅ์์ ์ฐ๊ฒฐ

+ push an existing  repositoty from  the command line
  + `git remote add [์๊ฒฉ์ ์ฅ์์ ๋ณ๋ช] [https์ฃผ์]` : ํ์ฌ ์ง์ญ ์ ์ฅ์์ ์๊ฒฉ ์ ์ฅ์ ์ฐ๊ฒฐ, ๋ณดํต `origin` ์ฌ์ฉ
  + `git remote` => origin์ผ๋ก ๋์ด.
  + `git  remote -v` => ์ฃผ์๊ฐ ๋์ด.

+ ํ๋์ local ์ ์ฅ์์ ์ฌ๋ฌ๊ฐ์ remote ์ ์ฅ์ ์ฐ๊ฒฐ ๊ฐ๋ฅ



## ๐ฉ git push

+ `git push` 
  +  `git push --set-upstream origin master` : ์ง์ญ ์ ์ฅ์๋ ์ฌ๋ฌ๊ฐ์ ์๊ฒฉ ์ ์ฅ์์ ์ฐ๊ฒฐ๋  ์ ์๋๋ฐ, ๊ทธ ์ค ์ด๋ค ์๊ฒฉ์ ์ฅ์์ ๊ธฐ๋ณธ์ ์ผ๋ก ์ฐ๊ฒฐ์ํฌ ๊ฒ์ธ์ง๋ฅผ ์ธํ => ์ด๋ ์ฒ์์ ๋ฑ ํ๋ฒ๋ง ์ณ์ฃผ๋ฉด ๋จ
  + ์์ผ๋ก, `git push`๋ผ๊ณ  ํ๋ฉด, `git push origin master`๊ฐ ์คํ๋๋ ๊ฒ



## ๐ฉ git clone

+ `git clone [https์ฃผ์]` => ์๋ก์ด ๋๋ ํ ๋ฆฌ ์ด๋ฆ์ผ๋ก ์ง์ญ ์ ์ฅ์๋ฅผ ์์ฑํ๊ณ  ์ถ๋ค๋ฉด https์ฃผ์๋ค์ ์ํ๋ ๋๋ ํ ๋ฆฌ ์ด๋ฆ์ ์จ์ฃผ๋ฉด ๋๋ค.  

  

#### git clone์ผ๋ก ๋ฐ์ ์ ์ฅ์์ ๋ธ๋์น๋ก ์ด๋ํ๊ธฐ

+ git์์ `git clone [https ์ฃผ์]`๋ก ์ ์ฅ์๋ฅผ ๋ด๋ ค๋ฐ์ผ๋ฉด ์ ์ฅ์์ ์ ์ฅ๋ ๋ธ๋์น๋ค์ ์ฌ์ฉํ  ์ ์๋ค. ๊ทธ๋ฌ๋ ์ฒ์์ `git branch`๋ก ํ์ธํ์์ ๋, `master` branch๋ง ๋ณด์ด๊ณ , ๋๋จธ์ง branch๋ค์ ํ์ธํ  ์ ์๋ค.  

+ `git branch -a` ์ ํตํด ๋ธ๋์น๋ค์ ๋ณผ ์ ์๋ค.

  ```git
  $ git branch -a
  * master
    remotes/origin/HEAD -> origin/master
    remotes/origin/develop
    remotes/origin/feature/mingyeong
    remotes/origin/feature/minwoo
    remotes/origin/feature/๊นํ์ธ
    remotes/origin/feature/์คํ์
    remotes/origin/master
  ```

+ `git branch -t [์ ์ฅ์์ด๋ฆ]/[branch์ด๋ฆ]` ์ ํตํด remote ์ ์ฅ์์ ๋ธ๋์น๋ฅผ ๊ทธ๋๋ ๋ก์ปฌ ๋ธ๋์น๋ก ์์ฑํ  ์ ์๋ค. 

  `git checkout -t `์ต์์ ์ด์ฉํ๋ฉด, branch๋ฅผ ๋ก์ปฌ์ ์์ฑํจ๊ณผ ๋์์ ๊ทธ ๋ธ๋์น๋ก checkout ๊ฐ๋ฅ

  ```git
  $ git checkout -t origin/develop
  
  Switched to a new branch 'develop'
  Branch 'develop' set up to track remote branch 'develop' from 'origin'.
  ```

  



## ๐ฉ git pull

+ ์ด๋ ํ์ชฝ์ local ์ ์ฅ์์์ ์์์ ํํ, `commit`, `push`
+ remote ์ ์ฅ์์ ๋ฐ์๋จ
+ ๋ค๋ฅธ ์ชฝ์ local ์ ์ฅ์์์ ์ด๋ฅผ **๋๊ธฐํ**ํ๋ ค๋ฉด, `git pull` ์ ํด์ผํจ. 

> SSH
>
> git hosting  ๊ธฐ๋ฅ๋ค ์์ธํ ์ดํด๋ณด๊ธฐ - Issue tracker
>
> ๋ฐฑ์ -> ํ์

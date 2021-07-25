# Class



코틀린 class의  특징

+ 코틀린은 클래스를 정의할 때 생성자도 함께 정의할 수 있습니다. 하지만 변수만 할당하고 구현부는 추가할 수 없습니다.
+ 초기화의 구현부는 `init`에 추가할 수 있습니다.
+ 코틀린 클래스의 변수는 프로퍼티(property)라는 개념을 사용하며, 자바의 (필드 + get/set메소드)의 역할을 합니다
+ 프로퍼티를 선언하면 `val/var` 여부에 따라서 `get/set` 메소드를 생성해줍니다.
+ get/set 메소드의 이름은 앞에 get/set 을 붙이고 PascalCase로 변수 이름을 붙여줍니다.
+ 프로퍼티를 `private`으로 선언하면 `get/set` 메소드가 생성되지 않고, 객체 내부에서만 접근할 수 있습니다.



+ 생성자 인자에 `var/val`을 붙여주면 클래스 내부에 프로퍼티를 생성하고 초기화를 합니다.





> 자바 `final` keyword
>
> `final`변수
>
> - 상수
> - 변수를 선언과 동시에 초기화하며 이후에 값을 수정할 수 없다.
> - 오직  get만 가능하다.
> - 일반적으로 final 변수는 프로그램 전체에 걸쳐 사용되는 경우가 많아서 특정 method 내부에 선언하기보다는 클래스에 `static` keyword와 함께 정의되어 사용한다.
> - 코틀린의 `val` keyword와 비슷한 역할
>
> `final` 메서드
>
> + overriding이 불가능
> + 상속 받은 그대로 사용해야 한다.
>
> `final` class
>
> + 상속이 불가능하다
> + subclass를 만들 수 없다.
>
> => `final` 메서드와 클래스는 주로 라이브러리 형태의 프로젝트를 작성할 때 사용, 자신이 작성한 메소드와 클래스를 다른 사람이 상속 받아서 사용하지 못하게 금지하고 싶을 때 이용하면 됨.





-----

### toString

+ toString() 메서드 재정의

  + **객체 인스턴스를 출력하면 객체의 `toString()` 메서드가 호출**됩니다. Kotlin에서는 모든 클래스가 자동으로 `toString()` 메서드를 상속합니다. 이 메서드의 기본 구현에서는 **인스턴스의 메모리 주소가 있는 객체 유형**을 반환합니다. 

    ```kotlin
    open class Item(val name: String, val price: Int)
    
    class Noodles : Item("Noodles", 10)
    class Vegetables : Item("Vegetables", 5)
    
    fun main() {
        val noodles = Noodles()
        val vegetables = Vegetables()
        println(noodles)
        println(vegetables)
    }
    
    
    // print result
    Noodles@5451c3a8
    Vegetables@76ed5528
    ```

  + 좀 더 의미 있고 사용자 친화적인 내용을 반환하도록 `toString()`을 재정의해야 합니다.    

  + ```kotlin
    class Noodles : Item("Noodles", 10) {
       override fun toString(): String {
           return name // 상위 클래스 Item에서 name을 상속받음
       }
    }    
    ```

  

+ #### data class => toString 제공

  + data class에서는 toString을 제공해준다. data에 포함되어 있는 데이터를 빠르게 출력하여 볼 수 있으며, 아래 변수를 추가로 정의한다고 해도 toString을 매번 수정할 필요 없이 kotlin에서 자동으로 정의해 주기 때문에 매우 편하다.

    ```kotlin
    data class UserInfo(
        val name: String,
        val age: Int
    )
    
    // 실제로 UserInfo class에서 toString은 이렇게 자동으로 정의된다. 
    @NotNull
    public String toString() {
       return "UserInfo(name=" + this.name + ", age=" + this.age + ")";
    }
    ```

    



-----

## Data class

+ 클래스의 용도 중 하나로 데이터 전달이 있다. 코틀린에서는 데이터 전달용 객체(Data Transfer Object, DTO)를 편리하게 선언할 수 있도록 `data class`라는 키워드를 지원한다. 데이터를 표현하는 객체는 다음의 메소드를 지원해야 한다. 자바로 `DTO`를 선언하려면 위의 메소드를 모두 정의해야 한다. 그러나 코틀린에서는 프로퍼티만 잘 정의하면 `data class`가 위의 메소드를 모두 정의해 준다

  + getters, setters: 프로퍼티 읽기/쓰기용 메소드

  + `equals()`: 데이터의 값이 같은지 비교할 때 사용

  + `toString()`: 데이터를 문자열로 쉽게 알아보고 싶을 때 사용

  + `hashCode()`: `Map` 등에서 해시값을 계산할 때 사용

  + `copy()`: 객체 복사

    > 코틀린에서의 객체 비교 
    >
    > 자바에서 == 연산자를 사용하면 두 변수가 **동일한 객체를 가리키는지** 검사한다. 그러나 코틀린에서는 가리키는 객체가 아닌 **객체의 값을 비교**한다. 코틀린에서 동일한 객체를 가리키는지 검사하고 싶다면 ===를 사용해야 한다.

+ Data Class 선언

  ```kotlin
  data class Customer(var name: String, var email: String)
  ```

+ 메서드 사용 예시

  ```kotlin
  val cus1 = Customer("hsk", "hsk@email.com")
  val cus2 = Customer("hsk", "hsk@email.com")
  
  println(cus1 == cus2) // 객체의 값을 비교 -> true
  ```

  ```kotlin
  val cus3 = cus1.copy(name = "hsk2") // name만 변경하고 나머지는 그대로 가져옴
  println(cus3) // Customer(name=hsk2, email=hsk@email.com)
  ```

+ Destructuring

  + 코틀린에서는 `data class`의 프로퍼티를 위와 비슷한 방법으로 가져올 수 있다.

  ```kotlin
  val (name, email) = cus1
  println(name, email) // hsk, hsk@email.com
  ```

  + 특정 프로퍼티를 쓰지 않을 경우 `_`로 대체해도 된다.

  ```kotlin
  val (_, email) = cus1
  ```

  + for문에서도 사용할 수 있다.

  ```kotlin
  for ((name, email) in customers) {
      println("name = $name, email = $email")
  }



#### 참고

+ [이동식저장소](https://thinking-face.tistory.com/entry/Kotlin-%EB%8D%B0%EC%9D%B4%ED%84%B0-%ED%81%B4%EB%9E%98%EC%8A%A4)


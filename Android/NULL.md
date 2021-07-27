# NULL



```kotlin
fun strLenSafe(s: String?): Int = 
	if (s != null) s.length else 0 

fun main(args: Array) { 
    val x: String? = null 
    println(strLenSafe(x)) 
    println(strLenSafe("abc")) 
}
```

+ `type`에 `?`를 붙임으로써 null이 가능한 변수임을 명시적으로 표현합니다. 
+ 만약 위 코드에서 `if(s!=null)` 없이 `s.length()`를 호출한다면 이 역시 컴파일에러가 발생합니다. null이 들어올 수 있는 타입인데, 내부에서 null check없이 사용했기 때문.



#### null safe operator

```kotlin
fun printAllCaps(s: String?) { 
    val allCaps: String? = s?.toUpperCase() 
    println(allCaps) 
} 

fun main(args: Array) { 
    printAllCaps("abc") 
    printAllCaps(null) 
}
```

+ `?.` 연산자를 사용하면, 앞의 변수가 null이 아닐 때만 오른쪽 함수가 수행되고 null이면 `null`을 반환합니다.
+ 즉 `if (s != null) s.toUpperCase() else null` 와 같습니다.

+ 또한,  property 접근  시에도 `?.`를 이용하여 쉽게 null 처리를 할 수 있습니다.

  ```kotlin
  class Address(val streetAddress: String, val zipCode: Int, 
                val city: String, val country: String) 
  
  class Company(val name: String, val address: Address?) 
  
  class Person(val name: String, val company: Company?) 
  
  fun Person.countryName(): String { 
      val country = this.company?.address?.country 
      return if (country != null) country else "Unknown" 
  } 
  
  fun main(args: Array) { 
      val person = Person("Dmitry", null) 
      println(person.countryName()) 
  }
  ```

  

#### Elvis operator

+ `?.` 연산자는 좌항이 null이면 null을 반환하는데, null인 경우 **default** 값을 주고 싶은 경우가 있다. 이 때 `?:`연산자를 사용할 수 있다. 

  즉, **좌항이 null이 아니면 좌항을 반환, null이면 우항을 반환**

  ```kotlin
  fun getName(str: String?) { 
      qhval name = str ?: "Unknown" 
  }
  ```

  + 이 코드는 `if (str != null) str else "Unknown"`과 같은 코드입니다. 
  + 엘비스 연산자는 우항으로 `return`이나 `throw`도 넣을 수 있습니다.

  ```kotlin
  un printShippingLabel(person: Person) { 
      val address = person.company?.address 
        ?: throw IllegalArgumentException("No address") //company 정보가 없으면 exception 강제 발생 
      with (address) { 
          println(streetAddress) 
          println("$zipCode $city, $country") 
      } 
  }
  ```

  

#### null 값이 아님을 보증 (!!)

+ 변수 뒤에 `!!`를 추가하면 null 값이 아님을 보증하는 것을 의미한다. 
+ 아래의 예제를 보면 name1의 타입은 `String?`이다. `String?` 타입은 `String` 타입과 명백히 다르다. `String?` 타입의 변수를 다른 변수에 저장할 때, 
  + `String?` 타입에 저장하거나
  + `String?` 타입의 변수의 뒤에 `!!`를 붙여서 String 타입으로 변환시켜주어야 한다.

```kotlin
val name1: String? = "과일"
val name2: String  = name1            // 에러
val name3: String? = name1            // 정상
val name4: String  = name1!!          // 정상
```













#### 참고

+ [투덜이의 리얼 블로그](https://tourspace.tistory.com/114)

+ [gosgjung.log]( https://velog.io/@gosgjung/3%EB%B6%84-kotlin-5-%EC%BD%94%ED%8B%80%EB%A6%B0%EC%9D%98-%EC%97%AC%EB%9F%AC%EA%B0%80%EC%A7%80-null-%EC%B2%98%EB%A6%AC%EB%B0%A9%EC%8B%9D%EB%93%A4)


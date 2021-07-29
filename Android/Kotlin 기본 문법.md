# Kotlin 기본 문법

### when 문 사용

```kotlin
fun main() {
    val myFirstDice = Dice(6)
    val rollResult = myFirstDice.roll()
    val luckyNumber = 4

    when (rollResult) {
        luckyNumber -> println("You won!")
        1 -> println("So sorry! You rolled a 1. Try again!")
        2 -> println("Sadly, you rolled a 2. Try again!")
        3 -> println("Unfortunately, you rolled a 3. Try again!")
        4 -> println("No luck! You rolled a 4. Try again!")
        5, 6 -> println("Don't cry! You rolled a 5 or 6 Try again!")
    }
}
```

+ `rollResult`가 `luckyNumber`이면 `"You win!"` 메시지를 출력합니다

+ `when`에서의 `else문`은 필수로 들어가야 한다.
+ `in` 키워드를 사용하여 특정 값의 범위를 지정 할 수도 있습니다.
+ 하위 코드처럼 변수에 특정 값을 할당할 때 이렇게 쓸 수도 있다. 

```kotlin
val number = 1;
val numberString = when(number) {
  0 -> "zero"
  1 -> "one"
  2 -> "two"
  3 -> "three"
  else -> null
}
```












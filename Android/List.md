## List

+ List : 특정 순서가 있는 항목의 모음

  + `List` : 읽기 전용 List로, 만든 후 수정할 수 없다.

  + `MutableList` : 변경 가능한 List로, 만든 후 수정할 수 있다. 즉, 요소를 추가, 삭제, 업데이트할 수 있다.

  + ```kotlin
    val numbers: List<Int> = listOf(1, 2, 3, 4, 5, 6)
    ```

  + 변수 유형을 할당 연산자(=) 오른쪽에 있는 값에 기반하여 추측하거나 추론할 수 있으면 **변수의 데이터 유형을 생략할 수 있다.**  => `val numbers = listOf(1, 2, 3, 4, 5, 6)`

  + ```kotlin
    println("List: $numbers")   		// List: [1, 2, 3, 4, 5, 6]
    println("Size: ${numbers.size}") 	// Size: 6
    ```

  + List의 요소 접근 => `numbers[0]` or `numbers.get(0)`

    ```kotlin
    println("First element: ${numbers[0]}") // First element: 1
    println("First: ${numbers.first()}")	// First: 1
    println("Last: ${numbers.last()}")	   	// Last: 6
    ```

  + `contains()` : List에 특정 item이 있는지 확인

  + `reversed()` : 요소가 역순으로 있는 새 목록을 반환

  + `sorted()` : 요소가 오름차순으로 정렬된 새 목록을 반환    

<br>

+ Mutable List : 변경가능한 List

  + `mutableListOf()`를 호출하여 생성 => `val entrees = mutableListOf<dayatype>()`

    ```kotlin
    val entrees = mutableListOf()
    // Error => Not enough information to infer type variable T
    // 목록에 어떤 유형(datatype)의 itme이 올지를 추론할 수 없기 때문에
    
    val entrees = mutableListOf<String>() // 변경가능한 String 유형의 목록을 만든다.
    val entrees: MutableList<String> = mutableListOf()
    ```

    > **You can use `val`** for a mutable list because the **`entrees` variable contains a *reference* to the list**, and that **reference doesn't change** even if the contents of the list do.

  + `add()` : 요소 추가, List에 요소가 성공적으로 추가되면 `true`를 반환하고 추가되지 않으면 `false`를 반환합니다. => `entrees.add("noodles")`

  + `addAll()` : List에 요소 여러개 추가 => `entrees.addAll(moreItems)`

  + `entrees.remove("rice")` : List에서 해당 요소 삭제, 삭제에 성공하면 `true`를 반환

  + `entrees.removeAt(0)` : 1번째 요소를 삭제

  + `entrees.clear()` : 전체 List 삭제

  + `entrees.isEmpty()`

  + `entrees.size()` 

<br>

### List 반복

+ `while`문

  ```kotlin
  val guestsPerFamily = listOf(2, 4, 1, 3)
  var totalGuests = 0
  var index = 0
  while (index < guestsPerFamily.size) { // index = 0, 1, 2, 3
      totalGuests += guestsPerFamily[index]
      index++
  }
  println("Total Guest Count: $totalGuests")
  ```

<br>

+ `for`문

  ```kotlin
  for (number in numberList) {
     // For each element in the list, execute this code block
  }
  ```

  `number` 변수는 `numberList`의 첫 번째 요소와 같게 설정되고 코드 블록이 실행됩니다. 그러면 `number` 변수가 자동으로 `numberList`의 다음 요소가 되도록 업데이트되고 코드 블록이 다시 실행됩니다. 이 작업은 `numberList`가 끝날 때까지 목록의 각 요소에 반복됩니다. 


<br>




# lemonade App

## 리소스 접근하는 법

+ drawble resource
  `lemonImage?.setImageResource(R.drawable.lemon_tree)``

+ string resource

  `textAction.setText(R.string.lemon_select)



## 문자열 서식 지정

문자열의 서식을 지정해야 할 경우, 다음 예시와 같이 문자열 리소스에 서식 인수를 추가하여 지정할 수 있습니다.

```kotlin
<string name="welcome_messages">Hello, %1$s! You have %2$d new messages.</string>
```

이 예시는 서식 문자열에 두 개의 인수가 있습니다. `%1$s`는 문자열이고 `%2$d`는 10진수입니다. `getString(int, Object...)`을 호출하여 문자열의 서식을 지정해보겠습니다. 예를 들면 다음과 같습니다.

```kotlin
var text = getString(R.string.welcome_messages, username, mailCount)
```





## View를 클릭했을 때, 동작 실행하기

```kotlin
private var lemonImage: ImageView? = null

lemonImage = findViewById(R.id.image_lemon_state)

lemonImage!!.setOnClickListener {
            // TODO: call the method that handles the state when the image is clicked
            clickLemonImage()
        }

lemonImage!!.setOnLongClickListener {
            // TODO: replace 'false' with a call to the function that shows the squeeze count
            // 길게 눌렀을 때 얼마나 레몬을 짰는지 알려줌
            showSnackbar()
        }
```





## onSaveInstanceState 

+ `onSaveInstanceState()` 메소드를 이용하면 Activity가 종료될 때 데이터를 저장할 수 있습니다. 일반적으로 사용자가 정상적인 행동으로 Activity를 종료할 때는 해당 이벤트를 미리 감지하고 그에 맞는 대처를 해줄 수가 있지만, 실제로는 다양한 상황에서 Activity가 종료되는 현상이 발생할 수 있습니다. 그리고 다시 액티비티가 실행될 때는 `onCreate(savedInstanceState: Bundle?)`에서 Bundle안의 data를 받아서 이용할 수 있다.



+ Activity가 종료되는 경우
  + 사용자가 ‘뒤로 가기(Back)’ 버튼을 눌러 Activity를 종료한 경우
  + Activity가 백그라운드에 있을 때 시스템 메모리가 부족해진 경우(OS가 강제 종료시킴)
  + 언어 설정을 변경할 때
  + 화면을 가로/세로 회전할 때
  + 폰트 크기나 폰트를 변경했을 때



+ 사용 예시

  ```kotlin
  override fun onSaveInstanceState(outState: Bundle) {
      outState.putString(LEMONADE_STATE, lemonadeState)
      outState.putInt(LEMON_SIZE, lemonSize)
      outState.putInt(SQUEEZE_COUNT, squeezeCount)
      super.onSaveInstanceState(outState)
  }
  
  override fun onCreate(savedInstanceState: Bundle?) {
          super.onCreate(savedInstanceState)
          setContentView(R.layout.activity_main)
  
          // === DO NOT ALTER THE CODE IN THE FOLLOWING IF STATEMENT ===
          if (savedInstanceState != null) {
              lemonadeState = savedInstanceState.getString(LEMONADE_STATE, "select")
              lemonSize = savedInstanceState.getInt(LEMON_SIZE, -1)
              squeezeCount = savedInstanceState.getInt(SQUEEZE_COUNT, -1)
          }
  ```



+ 전체코드

  `MainActivity.kt`

  ```kotlin
  /*
   * Copyright (C) 2021 The Android Open Source Project.
   *
   * Licensed under the Apache License, Version 2.0 (the "License");
   * you may not use this file except in compliance with the License.
   * You may obtain a copy of the License at
   *
   *     http://www.apache.org/licenses/LICENSE-2.0
   *
   * Unless required by applicable law or agreed to in writing, software
   * distributed under the License is distributed on an "AS IS" BASIS,
   * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   * See the License for the specific language governing permissions and
   * limitations under the License.
   */
  package com.example.lemonade
  
  import androidx.appcompat.app.AppCompatActivity
  import android.os.Bundle
  import android.widget.ImageView
  import android.widget.TextView
  import com.google.android.material.snackbar.Snackbar
  
  class MainActivity : AppCompatActivity() {
  
      /**
       * DO NOT ALTER ANY VARIABLE OR VALUE NAMES OR THEIR INITIAL VALUES.
       *
       * Anything labeled var instead of val is expected to be changed in the functions but DO NOT
       * alter their initial values declared here, this could cause the app to not function properly.
       */
      private val LEMONADE_STATE = "LEMONADE_STATE"
      private val LEMON_SIZE = "LEMON_SIZE"
      private val SQUEEZE_COUNT = "SQUEEZE_COUNT"
  
      // SELECT represents the "pick lemon" state
      private val SELECT = "select"
  
      // SQUEEZE represents the "squeeze lemon" state
      private val SQUEEZE = "squeeze"
  
      // DRINK represents the "drink lemonade" state
      private val DRINK = "drink"
  
      // RESTART represents the state where the lemonade has be drunk and the glass is empty
      private val RESTART = "restart"
  
      // Default the state to select
      private var lemonadeState = "select"
  
      // lemonSize : 얼마나 tab 해야 레모네이드를 만들 수 있는지
      // Default lemonSize to -1
      private var lemonSize = -1
  
      // Default the squeezeCount to -1
      private var squeezeCount = -1
  
      private var lemonTree = LemonTree() // to use pick() method
      private var lemonImage: ImageView? = null
  
  
      override fun onCreate(savedInstanceState: Bundle?) {
          super.onCreate(savedInstanceState)
          setContentView(R.layout.activity_main)
  
          // === DO NOT ALTER THE CODE IN THE FOLLOWING IF STATEMENT ===
          if (savedInstanceState != null) {
              lemonadeState = savedInstanceState.getString(LEMONADE_STATE, "select")
              lemonSize = savedInstanceState.getInt(LEMON_SIZE, -1)
              squeezeCount = savedInstanceState.getInt(SQUEEZE_COUNT, -1)
          }
          // === END IF STATEMENT ===
  
          lemonImage = findViewById(R.id.image_lemon_state)
          setViewElements() // 처음 imageView => lemon_tree
          lemonImage!!.setOnClickListener {
              // TODO: call the method that handles the state when the image is clicked
              clickLemonImage()
          }
  
          lemonImage!!.setOnLongClickListener {
              // TODO: replace 'false' with a call to the function that shows the squeeze count
              // 길게 눌렀을 때 얼마나 레몬을 짰는지 알려줌
              showSnackbar()
          }
      }
  
      /**
       * === DO NOT ALTER THIS METHOD ===
       *
       * This method saves the state of the app if it is put in the background.
       */
      override fun onSaveInstanceState(outState: Bundle) {
          outState.putString(LEMONADE_STATE, lemonadeState)
          outState.putInt(LEMON_SIZE, lemonSize)
          outState.putInt(SQUEEZE_COUNT, squeezeCount)
          super.onSaveInstanceState(outState)
      }
  
      /**
       * Clicking will elicit a different response depending on the state.
       * This method determines the state and proceeds with the correct action.
       */
      private fun clickLemonImage() {
          // TODO: use a conditional statement like 'if' or 'when' to track the lemonadeState
          //  when the the image is clicked we may need to change state to the next step in the
          //  lemonade making progression (or at least make some changes to the current state in the
          //  case of squeezing the lemon). That should be done in this conditional statement
  
          when (lemonadeState) {
              SELECT -> {
                  lemonadeState = SQUEEZE
                  lemonSize = lemonTree.pick() // 랜덤하게 lemonSize 설정
                  squeezeCount = 0
              }
  
              SQUEEZE -> {
                  squeezeCount++
                  lemonSize--
                  if (lemonSize == 0) {
                      lemonadeState = DRINK
                      lemonSize = -1
                  }
              }
              DRINK -> lemonadeState = RESTART
  
              RESTART -> lemonadeState = SELECT
  
              else -> {
  
              }
          }
          setViewElements()
  
          // TODO: When the image is clicked in the SELECT state, the state should become SQUEEZE
          //  - The lemonSize variable needs to be set using the 'pick()' method in the LemonTree class
          //  - The squeezeCount should be 0 since we haven't squeezed any lemons just yet.
  
          // TODO: When the image is clicked in the SQUEEZE state the squeezeCount needs to be
          //  INCREASED by 1 and lemonSize needs to be DECREASED by 1.
          //  - If the lemonSize has reached 0, it has been juiced and the state should become DRINK
          //  - Additionally, lemonSize is no longer relevant and should be set to -1
  
          // TODO: When the image is clicked in the DRINK state the state should become RESTART
  
          // TODO: When the image is clicked in the RESTART state the state sholud become SELECT
  
          // TODO: lastly, before the function terminates we need to set the view elements so that the
          //  UI can reflect the correct state
  
          // moving the app from the current state to the next and updating any variables as needed.
      }
  
      /**
       * Set up the view elements according to the state.
       */
      private fun setViewElements() {
          val textAction: TextView = findViewById(R.id.text_action)
          // lemonImage
  
          lemonImage?.setImageResource(
              when (lemonadeState) {
                  SELECT -> R.drawable.lemon_tree
                  SQUEEZE -> R.drawable.lemon_squeeze
                  DRINK -> R.drawable.lemon_drink
                  RESTART -> R.drawable.lemon_restart
                  else -> R.drawable.lemon_tree
              }
          )
  
          textAction.setText(
              when (lemonadeState) {
                  SELECT -> R.string.lemon_select
                  SQUEEZE -> R.string.lemon_squeeze
                  DRINK -> R.string.lemon_drink
                  RESTART -> R.string.lemon_empty_glass
                  else -> R.string.lemon_select
              }
          )
  
          /* 이렇게 정의했었지만, 상위 버전이 더 깔끔한것 같아서 교체
          when(lemonadeState){
              SELECT->{
                  lemonImage?.setImageResource(R.drawable.lemon_tree)
                  textAction.setText(R.string.lemon_select)
              }
              SQUEEZE->{
                  lemonImage?.setImageResource(R.drawable.lemon_squeeze)
                  textAction.setText(R.string.lemon_squeeze)
              }
              DRINK->{
                  lemonImage?.setImageResource(R.drawable.lemon_drink)
                  textAction.setText(R.string.lemon_drink)
              }
              RESTART->{
                  lemonImage?.setImageResource(R.drawable.lemon_restart)
                  textAction.setText(R.string.lemon_empty_glass)
              }
              else->{
  
              }
          }
          */
          // TODO: set up a conditional that tracks the lemonadeState
  
          // TODO: for each state, the textAction TextView should be set to the corresponding string from
          //  the string resources file. The strings are named to match the state
  
          // TODO: Additionally, for each state, the lemonImage should be set to the corresponding
          //  drawable from the drawable resources. The drawables have the same names as the strings
          //  but remember that they are drawables, not strings.
      }
  
      /**
       * === DO NOT ALTER THIS METHOD ===
       *
       * Long clicking the lemon image will show how many times the lemon has been squeezed.
       */
      private fun showSnackbar(): Boolean {
          if (lemonadeState != SQUEEZE) {
              return false // 그럼 squeeze 상태가 아니면 길게 눌렀을 때, 아무일도 발생 x?
          }
          val squeezeText = getString(R.string.squeeze_count, squeezeCount, lemonSize)
          // Snackbar message가 직관적이지 않아 R.string.squeeze_count을 수정하고 getString()에 lemonSize도
          // argument로 전달해 출력되는 메세지를 변경
  
          Snackbar.make(
              findViewById(R.id.constraint_Layout),
              squeezeText,
              Snackbar.LENGTH_SHORT
          ).show()
          return true
      }
  }
  
  /**
   * A Lemon tree class with a method to "pick" a lemon. The "size" of the lemon is randomized
   * and determines how many times a lemon needs to be squeezed before you get lemonade.
   */
  class LemonTree {
      fun pick(): Int {
          return (2..4).random()
      }
  }
  ```

  
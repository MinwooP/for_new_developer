# View

-----

## 🎖 setContentView

```kotlin
public class MainActivity extends Activity{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}
```

+ 프로젝트를 생성하면 액티비티를 상속받는 클래스가 default로 제공됩니다. 개발자 편의를 위해 자동으로 지원되는 기능으로 Activity 클래스를 상속받으면 **반드시 onCreate() 함수를 오버 라이딩**합니다. 해당 함수는 **액티비티(Activity)가 실행될 때 가장 먼저 실행**되는 함수로 마치 자바에서 프로그램 시 가장 먼저 실행되는 **main() 함수와 비슷**합니다. 

+ `setContentView()` => 즉, View들을 화면에 띄우는 것
  setContentView() 함수는 첫 번째 인자로 넘겨주는 **XML 레이아웃 리소스 ID에 해당하는 파일**을 **파싱** 하여 **뷰(View)를 생성하고 뷰(View)의 속성(xml파일의 각 뷰 imageview, textView의 속성) 을 지정하고 뷰(View) 간의 상하관계에 맞춰 배치**를 합니다. 이러한 일련의 과정을 **전개(Inflate)**라 부릅니다. setContentView() 함수는 xml 문서를 전개하기 위해 내부적으로 LayoutInflater 클래스를 참조합니다. 

  즉, xml파일의 내용을 activity에 띄우는 것?
  
  ```kotlin
  setContentView(R.layout.activity_main);
  ```

  R은 res 폴더를 의미하고, layout은 R의 내부 클래스를 의미한다. 즉, `R.layout.activity_main`은 activity_main.xml을 가리키는 ID가 된다. 

  
  
+ 전개자(Inflater)

  XML문서를 전개(inflate)하기 위해서 시스템상으로 제공하는 클래스가 있습니다. 바로 `LayoutInflater` 클래스로 해당 클래스의 객체를 구하는 방법은 두 가지가 있습니다.

  1. `getSystemService()` 함수를 통해 가져오는 방법

     ```kotlin
     LayoutInflater inflater1 = (LayoutInflater)getSystemService(Context.LAYOUT_INFLATER_SERVICE);
     ```

  2. 액티비티 내에서 제공하는 `getLayoutInflater()` 함수를 통해 받아오는 방법

     ```kotlin
     LayoutInflater inflater2 = getLayoutInflater();
     ```

  inflater를 생성하였다면 `inflate()` 함수를 통해 전개된 뷰 객체를 반환받습니다. 첫 번째 인자로는 XML 레이아웃 리소스 ID를 넘기고 두 번째는 레이아웃의 최상위 Root ViewGruop으로 설정할 객체를 넘깁니다.

  ```kotlin
  View view  = getLayoutInflater().inflate(R.layout.activity_sub, null);
  ```




-----

## 🎖 findViewById

+ activity_main.xml에서 설정한 뷰들은 초기 설정만 해놓아서 이벤트를 받거나 할 수 없습니다. 그래서, 이벤트를 받거나 뷰에 영향을 주려면 MainActivity.kt에서 수정을 해줘야 한다. 그래서 **activity_main.xml 레이아웃에 설정된 뷰들을 가져오는** 메소드가 `findViewById`이다.

  ```kotlin
  class MainActivity : AppConpatActivity() {
      override fun onCreate(savedInstanceState: Bundle?){
          super.onCreate(savedInstanceState);
          setContentView(R.layout.activity_main)
              
          val myText : TextView = findViewById(R.id.myTextView)
          myText.text = "Hi~"
      }
  }
  ```

  

+ 이렇게 findViewById를 이용하면, activity_main.xml 에서 적용 시켰던 글자를 넣거나, 글자색을 변경하거나 등의 작업을 할 수 있는 메소드를 지원하게 된다. 특히, 가장 중요한 이벤트 처리가 가능한 메소드도 지원을 하게 된다. 





-----

## 🎖 View Binding

+ 모든 UI 요소에 액세스하여 사용자의 입력을 읽어야 한다. 코드가 `View`에서 메서드를 호출하거나 속성(ex) myButton.text)에 액세스하기 전에 먼저 `Button` 또는 `TextView`와 같은 `View`에 대한 참조를 찾아야 한다. `findViewById()` 메서드를 통해 ** `View`의 ID가 주어지면 이 뷰에 대한 참조를 반환**하는 작업을 실행하지만, 이는 앱에 뷰가 더 많아지고 UI가 복잡해짐에 따라 번거로워질 수 있다.



+ View Binding 사용

  1. 뷰 결합 사용 설정

     + `build.gradle`에 하위 코드 추가 => Sync Now

     ```kotlin
     buildFeatures {
         viewBinding = true
     }  
     ```

     모듈 Gradle 파일에서 뷰 바인딩을 활성화하면, 레이아웃 파일마다 바인딩 클래스가 생성됩니다.

     

  2. 결합 객체 초기화 

     +  앱의 각 `View`마다 `findViewById()`를 호출하는 대신, 결합 객체를 한 번 만들고 초기화

       <img src = "https://user-images.githubusercontent.com/31370590/125413956-9674fa02-f7ac-4de5-a4f0-bdcd9435ece9.PNG " width = "560" height = "400">

       

     + `MainActivity.kt`

       ```kotlin
       class MainActivity : AppCompatActivity() {
       
           lateinit var binding: ActivityMainBinding
       
           override fun onCreate(savedInstanceState: Bundle?) {
               super.onCreate(savedInstanceState)
               binding = ActivityMainBinding.inflate(layoutInflater)
               setContentView(binding.root)
           }
       }
       ```

       + `lateinit var binding: ActivityMainBinding`

         `lateinit` 키워드는 새로운 키워드로, **코드가 변수를 사용하기 전에 먼저 초기화할 것임을 확인**해 줍니다. 프로퍼티 초기화를 미루는 것. 변수를 초기화하지 않으면 앱이 비정상 종료됩니다.

       

       + `binding = ActivityMainBinding.inflate(layoutInflater)`

         `activity_main.xml` 레이아웃에서 `Views`에 액세스하는 데 사용할 `binding` 객체를 초기화합니다.

       

       + `setContentView(binding.root)`

         activity의 콘텐츠 뷰를 설정합니다(레이아웃 전개?). 레이아웃의 리소스 ID인 `R.layout.activity_main`을 전달하는 대신, 앱의 뷰 계층 구조 루트인 `binding.root`를 지정합니다. 

         <span style="color:red">그러면, `binding.root`가 `R.layout.activity_main`을 가리키는 것?</span>

     

  3. binding 사용

     + `binding` 객체는 **ID가 있는 앱의 모든 `View`를 위한 참조를 자동으로 정의**합니다. 뷰 결합을 사용하는 것이 훨씬 더 간결해서 `View`를 위한 참조를 유지할 변수를 만들 필요조차 없으며 결합 객체에서 직접 뷰 참조를 사용하기만 하면 됩니다.

       ```kotlin
       // Old way with findViewById()
       val myButton: Button = findViewById(R.id.my_button)
       myButton.text = "A button"
       
       // Better way with view binding
       val myButton: Button = binding.myButton
       myButton.text = "A button"
       
       // Best way with view binding and no extra variable
       binding.myButton.text = "A button"
       ```

       > 결합 클래스의 이름은 XML 파일의 이름을 카멜 표기법으로 변환하고 이름 끝에 'Binding'을 추가하여 생성됩니다. 마찬가지로 각 뷰를 위한 참조는 밑줄을 삭제하고 뷰 이름을 카멜 표기법으로 변환하여 생성됩니다. 예를 들어 `activity_main.xml`은 `ActivityMainBinding`이 되고 `binding.textView`로 `@id/text_view`에 액세스할 수 있습니다.






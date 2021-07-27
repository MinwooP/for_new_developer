# Navigation Component

-----

## 🎖 Jetpack Navigation Component

#### Andriod Jetpack에서 제공하는 *Navigation component*

- Navigation graph: 탐색 그래프는 앱에서 탐색을 시각적으로 보여주는 XML 파일입니다. 파일은 개별 activity 및 fragment에 상응하는 ***destination***과 한 destination에서 다른 destination으로 이동하려고 코드에서 사용할 수 있는 ***destination 사이의 action***으로 구성됩니다. 레이아웃 파일과 마찬가지로 Android 스튜디오는 탐색 그래프에 대상과 작업을 추가하는 시각적 편집기를 제공합니다.
- `Navhost`: `NavHost`는 **activity 내에서 탐색 그래프의 destination을 표시**하는 데 사용됩니다. 프래그먼트 간에 이동하면 `NavHost`에 표시되는 destination이 업데이트됩니다. `MainActivity`에서 `NavHostFragment`라는 기본 제공 구현을 사용합니다.
- `NavController`: `NavController` 객체를 사용하면 ** `NavHost`에 표시되는 destination 간 탐색을 제어**할 수 있습니다. 인텐트를 사용할 때는 `startActivity()`를 호출하여 새 화면으로 이동해야 했습니다. 탐색 구성요소를 사용하면 `NavController`의 `navigate()` 메서드를 호출하여 표시되는 프래그먼트를 교체할 수 있습니다. `NavController`를 사용하면 시스템 '위로' 버튼에 응답하여 이전에 표시된 프래그먼트로 다시 이동하는 것과 같은 일반적인 작업을 처리할 수도 있습니다.



#### Navigation Component 를 사용하기 위한 준비

1. Navigation Dependency

   + `build.gradle` 파일의 **buildscript > ext**에서 `material_version` 아래의 `nav_version`을 `2.3.1`로 설정

     ```kotlin
     buildscript {
         ext {
             nav_version = "2.3.1"
         }
     } 
     ```

   + 앱 수준 `build.gradle` 파일에서 종속 항목 그룹에 다음을 추가

     ```kotlin
     implementation "androidx.navigation:navigation-fragment-ktx:$nav_version"
     implementation "androidx.navigation:navigation-ui-ktx:$nav_version"
     ```

2. Safe Args Plug-in

   + **Words** 앱에 탐색 구성요소를 구현하기 전에 프래그먼트 간에 데이터를 전달할 때 유형 안전성을 지원하는 Gradle 플러그인인 **Safe Args**라는 항목도 추가해야 합니다.

     1. 최상위 `build.gradle` 파일의 **buildscript > dependencies**에서 다음 클래스 경로를 추가

        ```kotlin
        classpath "androidx.navigation:navigation-safe-args-gradle-plugin:$nav_version"
        ```

     2. 앱 수준 `build.gradle` 파일의 상단에 있는 `plugins` 내에서 `androidx.navigation.safeargs.kotlin`을 추가

        ```kotlin
        plugins {
            ~
             id 'androidx.navigation.safeargs.kotlin'
        }
        ```



#### Navigation Graph 사용

+ Navigation Graph : 프래그먼트 간 탐색을 구현하는데 도움이 되는 시각적 편집기
+ 탐색 그래프(또는 줄여서 NavGraph)는 앱 탐색의 가상 매핑입니다. 각 화면(또는 이 경우의 프래그먼트)는 이동할 수 있는 가능한 'destination'이 됩니다. `NavGraph`는 각 destination이 서로 관련되는 방식을 보여주는 XML 파일로 나타낼 수 있습니다. 
+ 탐색 그래프의 destination은 `FragmentContainerView`로 사용자에게 표시



#### MainActivtiy에서 FragmentContainerView 사용

1. MainActivity 수정

   `MainActivity`의 용도를 변경하여 프래그먼트의 `NavHost` 역할을 할 `FragmentContainerView`를 포함합니다. 이 시점부터 모든 앱의 탐색은 `FragmentContainerView` 내에서 실행됩니다. 

   ```kotlin
   <androidx.fragment.app.FragmentContainerView
      android:id="@+id/nav_host_fragment"
      android:name="androidx.navigation.fragment.NavHostFragment"
      android:layout_width="match_parent"
      android:layout_height="match_parent"
      app:defaultNavHost="true"
      app:navGraph="@navigation/nav_graph" 
      />
   ```

   + `activity_main.xml`에서 `FrameLayout`안에 원래 존재하던 `recyclerView`를 `FragmentContainerView`로 바꿉니다. 

   + `android:name="androidx.navigation.fragment.NavHostFragment"`

     이 속성의 특정 프래그먼트를 지정할 수 있지만 `NavHostFragment`로 설정하면 `FragmentContainerView`가 프래그먼트 간에 이동할 수 있습니다.

   + `app:defaultNavHost="true"`

     이렇게 하면 **프래그먼트 컨테이너가 탐색 계층 구조와 상호작용**할 수 있습니다. 예를 들어 시스템 뒤로 버튼을 누르면 컨테이너는 새 활동이 표시될 때와 마찬가지로 이전에 표시된 프래그먼트로 다시 이동합니다.

   + `app:navGraph="@navigation/nav_graph" `

     이는 앱의 프래그먼트가 서로 이동할 수 있는 방법을 정의하는 XML 파일을 가리킵니다.

     

2. 탐색 그래프 설정

   + `nav_graph.xml`이름의 새로운 Android Resource File 생성(Resource type: Navigation)하면 새 시각적 편집기가 표시됩니다. `FragmentContainerView`의 `navGraph` 속성에서 `nav_graph`를 이미 참조했으므로 새 destination을 추가하려면 화면 상단 왼쪽에서 새로 만들기 버튼을 클릭하여 각 프래그먼트의 destination을 만듭니다. 

   + Navigation Action 만들기

     `letterListFragment`에서 `wordListFragment` destination 간에 탐색 작업을 만들려면 `letterListFragment` destination 위로 마우스를 가져가서 오른쪽에 표시되는 원에서 `wordListFragment` destination으로 드래그합니다. 화살표로 표시되는 `action_letterListFragment_to_wordListFragment`이름의 action이 생성됩니다. 

   + `WordListFragment`의 인수 지정

     인텐트를 사용하여 활동 사이를 이동할 때 선택된 문자가 `wordListFragment`에 전달될 수 있도록 'extra'를 지정했습니다. Navigation은  destination 간에 매개변수 전달도 지원하면서 유형에 안전한 방식으로 이를 실행합니다.

     `wordListFragment` destination을 선택하고 속성 창의 **Arguments**에서 더하기 버튼을 클릭하여 새 인수를 만듭니다. 인수는 `letter`라고 하고 유형은 `String`이어야 합니다. 여기에서 이전에 추가한 Safe Args 플러그인이 필요합니다. 이 인수를 문자열로 지정하면 탐색 작업이 코드에서 실행될 때 `String`이 예상됩니다.



3. 탐색 작업 실행

   `LetterAdapter`.`kt`를 열어 탐색 작업을 실행

   + 버튼의 `onClickListener()` 콘텐츠를 삭제합니다. 대신 방금 만든 탐색 작업을 검색해야 합니다. `onClickListener()`에 다음을 추가합니다.

     ```kotlin
     val action = LetterListFragmentDirections.actionLetterListFragmentToWordListFragment(letter = holder.button.text.toString())
     ```

     `LetterListFragmentDirections`를 사용하면 `letterListFragment`부터 가능한 모든 탐색 경로를 참조할 수 있습니다. `actionLetterListFragmentToWordListFragment()` 함수는

     `wordListFragment.`로 이동할 특정 action입니다.

   + 탐색 작업 참조가 있으면 *NavController*(탐색 작업 실행을 허용하는 객체) 참조를 가져와서 작업을 전달하는 `navigate()`를 호출하면 됩니다.

     ```kotlin
     holder.view.findNavController().navigate(action)
     ```



4. MainActivity 구성

   + `navController` 속성을 만듭니다. `onCreate`에서 설정되므로 `lateinit`로 표시됩니다.

     ```kotlin
     private lateinit var navController: NavController
     ```

   + 그런 다음 `onCreate()`에서 `setContentView()`를 호출한 후 `nav_host_fragment`(`FragmentContainerView`의 ID임) 참조를 가져와서 `navController` 속성에 할당합니다.

     ```kotlin
     val navHostFragment = supportFragmentManager
         .findFragmentById(R.id.nav_host_fragment) as NavHostFragment
     navController = navHostFragment.navController
     ```

   + 그리고 `onCreate()`에서 `setupActionBarWithNavController()`를 호출하여 `navController`를 전달합니다. 이렇게 하면 작업 모음(앱 바) 버튼이 표시됩니다.

     ```kotlin
     setupActionBarWithNavController(navController)
     ```

   + 마지막으로 `onSupportNavigateUp()`을 구현합니다. XML에서 `defaultNavHost`를 `true`로 설정하는 것과 함께 이 메서드를 사용하면 **위로** 버튼을 처리할 수 있습니다. 그러나 activity가 구현을 제공해야 합니다.

     ```kotlin
     override fun onSupportNavigateUp(): Boolean {
        return navController.navigateUp() || super.onSupportNavigateUp()
     }
     ```

   + 이때 모든 구성요소는 탐색이 프래그먼트로 작동하도록 제자리에 있습니다. 그러나 이제 탐색이 인텐트 대신 프래그먼트를 사용하여 실행되므로 `WordListFragment`에서 사용하는 문자의 인텐트 extra가 더 이상 작동하지 않습니다. 다음 단계에서는 `WordListFragment`를 업데이트하여 `letter` 인수를 가져옵니다.





#### Navigation APIs

+ `NavHostFragment` : 탐색 구성요소가 교환되는 목적지 컨테이너 역할을 한다. 이는 activity를 통해  탐색할 때 대체되는 fragment를 담는 컨테이너이다.

+ `NavController` : 탐색 구성요소(navigate components)의 내부요소로 실제로 탐색 작업을 한다. 진행중인 작업을 보여주는 안내자와 같다.  

+ `NavigationView` : `NavHostFragment`안에 없고, 탐색 구성요소의 일부도 아님. 탐색 구성요소 전에 존재했으며, 탐색 창 내에 있는 메뉴와 관련이 있음. 메뉴 항목과 탐색 창을 선택하면 앱 내 다른 목적지로 이동한다. 하지만 탐색 구성요소의 일부가 아니며, 탐색 구성요소의 항목과 상호작용 하는 것이다.  

+ `NavigationUI` : `NavHostFragment` 외부 콘텐츠 업데이트를 책임집니다. ex) navigationView, BottomNavBar ? 

  => 이를 사용하면 훨씬 간편하게 앱 내 탐색을 만들고 수정할 수 있음.

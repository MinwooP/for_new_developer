# Fragment

### <div align = "center"> 목차 </div>

------

- [Fragment](#Fragment)
- [Fragment Life Cycle](#Fragment-Life-Cycle)
- [Fragment에서 메뉴 생성](#Fragment에서-메뉴-생성)

------

## 🎖 Fragment

+ 대다수 Android 앱에는 화면마다 별도의 Activity가 필요하지 않습니다. 실제로 여러 일반적인 UI 패턴(예: 탭)이 *Fragment*라는 섹션을 사용하는 단일 Activity 내에 존재합니다.  
+ 간단하게 말해 앱의 사용자 인터페이스에서 **재사용 가능한 부분**입니다. 활동과 마찬가지로 프래그먼트는 수명 주기가 있고 사용자 입력에 응답할 수 있습니다. 프래그먼트는 활동이 화면에 표시될 때 활동의 뷰 계층 구조 내에 항상 포함됩니다. 재사용성과 모듈성을 강조하므로 **단일 활동에서 여러 프래그먼트를 동시에 호스팅**할 수도 있습니다. 각 프래그먼트는 별도의 자체 수명 주기를 관리합니다.



-------

## 🎖 Fragment Life Cycle

+ *Lifecycle.State* 열거형으로 표현되는 다섯 가지 상태

  + INITIALIZED: 프래그먼트의 새 인스턴스가 인스턴스화되었습니다.
  + CREATED: 첫 번째 프래그먼트 수명 주기 메서드가 호출됩니다. 이 상태에서 프래그먼트와 연결된 뷰도 만들어집니다.
  + STARTED: 프래그먼트가 화면에 표시되지만 '포커스'가 없으므로 사용자 입력에 응답할 수 없습니다.
  + RESUMED: 프래그먼트가 표시되고 포커스가 있습니다.
  + DESTROYED: 프래그먼트 객체의 인스턴스화가 취소되었습니다.

+ `Fragment` 클래스는 수명 주기 이벤트에 응답하기 위해 재정의할 수 있는 여러 메서드를 제공한다. 

  - `onCreate()`: 프래그먼트가 인스턴스화되었고 `CREATED` 상태입니다. 그러나 이에 상응하는 뷰가 아직 만들어지지 않았습니다.
  - `onCreateView()`: **이 메서드에서 레이아웃을 확장**합니다. 프래그먼트가 `CREATED` 상태로 전환되었습니다.
  - `onViewCreated()`: 뷰가 만들어진 후 호출됩니다. 이 메서드에서 일반적으로 `findViewById()`를 호출하여 **특정 뷰를 속성에 바인딩**합니다.
  - `onStart()`: 프래그먼트가 `STARTED` 상태로 전환되었습니다.
  - `onResume()`: 프래그먼트가 `RESUMED` 상태로 전환되었고 이제 포커스를 보유합니다(사용자 입력에 응답할 수 있음).
  - `onPause()`: 프래그먼트가 `STARTED` 상태로 다시 전환되었습니다. UI가 사용자에게 표시됩니다.
  - `onStop()`: 프래그먼트가 `CREATED` 상태로 다시 전환되었습니다. 객체가 인스턴스화되었지만 더 이상 화면에 표시되지 않습니다.
  - `onDestroyView()`: 프래그먼트가 `DESTROYED` 상태로 전환되기 직전에 호출됩니다. 뷰는 메모리에서 이미 삭제되었지만 프래그먼트 객체는 여전히 있습니다.
  - `onDestroy()`: 프래그먼트가 `DESTROYED` 상태로 전환됩니다.

  <img src = "https://user-images.githubusercontent.com/31370590/126290914-05546013-f2da-4dd0-b899-c93592aadd1f.PNG" width = "350" height = "500"> 

  + activity : 
    + `onCreate`에서 레이아웃 inflate,  view 바인딩
  + fragment :
    + `onCreate()`는 뷰 만들어지기 전에 호출
    + `onCreateView()`에서 레이아웃 확장
    + `onViewCreated()`에서 뷰 바인딩








-----

## 🎖 Fragment에서 메뉴 생성 

Fragment에 맞추어 메뉴가 변하도록 하려면

1. 메뉴가 있음을 알림

   ```java
   @Override
   public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
       setHasOptionsMenu(true);
       return inflater.inflate(R.layout.fragment_interest, container, false);
   }
   ```

   `onCreateVIew`에서 `setHasOptionsMenu(true)`를 써줘야 한다. 이 명령이 있어야 액티비티보다 프래그먼트의 메뉴가 우선된다. 

2. 메뉴 생성

   ```java
   @Override
   public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
       super.onCreateOptionsMenu(menu, inflater);
       inflater.inflate(R.menu.menu_main_interest, menu);
   }
   ```

   `onCreateOptionMenu()` 메서드를 구현해, `inflater.inflate(R.menu.menu_ID, menu)`를 사용한다. 적절히 만들어둔 메뉴의 ID를 사용하자. 또한 프래그먼트와 함께 사용되는 `onCreateOptionsMenu()` 메서드에는 return 문이 필요하지 않다.

3. 메뉴 이벤트 설정

   ```java
   @Override
   public boolean onOptionsItemSelected(MenuItem item) {
       switch (item.getItemId()) {
           case R.id.menu_main_interest_clip:
               System.out.println("Clip clicked!");
               break;
       }
       return super.onOptionsItemSelected(item);
   }
   ```

   적절히 `switch-case`문을 사용해 메뉴 이벤트를 설정한다. 



#### 참고

+ [CheatSheet](https://makerj.tistory.com/177)




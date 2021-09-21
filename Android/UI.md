# Android - UI

## 적응형 아이콘(adaptive icon)

+ 이는 **어떤 기기나 밀도에서든 획일화된 아이콘 스타일을 가질 수 있도록** 해주는 아이콘 스타일이다. 간단하게 말하자면 마스킹 처리해서 아이콘을 보여주는 형태입니다. 배경 레이어(Background-Layer)와 포그라운드 레이어(Foreground-Layer)를 합한 레이어를 마스크 레이어(Mask-Layer)를 적용해서 보여주는 방식으로 구현되어 있습니다. 

+ Foreground and bachground layer

  개발자는 앱 아이콘을 두 레이어, 즉 **포그라운드 레이어**와 **백그라운드 레이어**로 구성할 수 있습니다. 위 예에서 흰색 Android 아이콘은 포그라운드 레이어에 있지만 파란색과 흰색 그리드는 백그라운드 레이어에 있습니다. 포그라운드 레이어는 백그라운드 레이어 위에 쌓입니다. 그런 다음 마스크(이 경우에는 원형 마스크)가 맨 위에 적용되어 원형 모양의 앱 아이콘이 생성됩니다.

+ **vector drawble**(res->drawable->ic_launcher_background)과 **bitmap image**(res->mipmap-~dpi->ic_launcher)는 모두 그래픽을 설명하지만 중요한 차이점이 있습니다.

  **비트맵 이미지**는 각 픽셀의 색상 정보를 제외하고 보유한 이미지에 관해 잘 알지 못합니다. 반면에 벡터 그래픽은 이미지를 정의하는 모양을 그리는 방법을 알고 있습니다. 이러한 지침은 색상 정보와 함께 일련의 점과 선, 곡선으로 구성됩니다. 벡터 그래픽은 **화질 저하 없이 모든 화면 밀도의 어떤 캔버스 크기로도 조정할 수 있다**는 것이 장점입니다.

  **벡터 드로어블**은 Android의 벡터 그래픽 구현으로, 휴대기기에서 충분히 유연하도록 만들어졌습니다. 이러한 가능한 요소를 사용하여 **XML로 정의**할 수 있습니다. 모든 밀도 버킷에 비트맵 애셋 버전을 제공하는 대신 이미지를 한 번만 정의하면 됩니다. 따라서 앱의 크기가 줄어 유지하기가 쉬워집니다.

+ 어댑티브 아이콘에 사용하는 백그라운드 레이어와 포그라운드 레이어는 모두 **108x108dp**로 설정해야하며, 마스킹 되는 화면 영역은 최대 **72x72dp**, 최소 **66x66dp**로 설정합니다 

+ 이제 적응형 아이콘이 잘 작동하므로 모든 앱 아이콘 비트맵 이미지를 제거할 수 없는 이유가 궁금할 수 있습니다. 이전 버전의 Android에서 앱 아이콘이 고화질로 표시되기 위해(이전 버전과의 호환성이라고 함) 이러한 파일이 여전히 필요합니다.

<br>

#### Q)

+ drawable->**ic_launcher_background.xml**과  **drawable-v24->ic_launcher_foreground.xml** 모두 **vector drawble file**입니다. 픽셀 단위의 고정된 크기는 없다. 코드를 보면 `<vector>`요소를 사용해 벡터 드로어블의 XML선언을 확인할 수 있다. 

+ 이 두개의 벡터 드로어블 파일을 이용해 res > mipmap-anydpi-v26->**ic_launcher.xml** 같은 **적응형 아이콘**을 만드는 것

+ res->mipmap-~dpi->ic_launcher.**png**는 비트맵 이미지 파일(사진 같은 것은 일련의 모양으로 설명하기 어렵기 때문에 벡터 드로어블보다 비트랩 에셋을 사용하는 것이 더 효율적이다.)

  > **참고**: 적응형 아이콘은 플랫폼의 API 수준 26에서 추가되었으므로 `-v26` 리소스 한정자가 있는 `mipmap` 리소스 디렉터리에서 적응형 아이콘을 선언해야 합니다. 즉, 이 디렉터리의 리소스는 API 26(Android 8.0) 이상을 실행하는 기기에만 적용됩니다. 이 디렉터리의 리소스 파일은 이전 버전의 플랫폼을 실행하는 기기에서는 무시됩니다.

<br>

<br>

-------

## DP(Dip), PX, DPI의 개념

#### PX

+ 화면을 구성하는 최소 단위로, 동일한 이미지라고 하더라도 픽셀의 수가 많은 것이 해상도가 더 높다. 아래에서 오른쪽 그림이 왼쪽그림보다 1인치당 픽셀수가 더 많으므로 해상도가 높다고 볼 수 있다. 

+ **ppi** : 1인치당 픽셀 수를 의미한다. 혹은 **dpi**라고 하는데 약간 다른 개념이다. 

  <img src = "https://user-images.githubusercontent.com/31370590/126763702-3c93d704-4f3b-49f7-a8af-52dea32ce88d.PNG">

+ Pixel은 일반적인 물리적인 크기로 나타낼 수 업다. 간혹 가다 가로세로 100 pixel 짜리의 아이콘을 만들었는데, ''그래서 그게 몇 cm, mm인데'' 라고 물어보는 사람이 있는데 **픽셀은 논리적인 크기**로. 1 Pixel의 정확한 크기는 **PPI를 어떻게 지정했는지에 따라 달라진다**. 

+ 따라서, 픽셀 단위로 이미지를 넣으면 스마트폰마다 화면의 크기가 다 다르기 때문에, 같은 픽셀 단위의 이미지(ex) 5x5 pixel 단위)라고 하더라도, 화면의 크기에 따라서 이미지가 크게 보일수도, 작게 보일수도 있다. 

  <img src = "https://user-images.githubusercontent.com/31370590/126764458-aab74438-3961-4424-81a7-9127a0135e20.PNG">

  => B가 A보다 픽셀의 수가 많고 촘촘하므로 A에 비해 해상도가 더 높다. 동일한 이미지임에도 불구하고, A와 b의 해상도가 다르기 때문에 이미지의 크기가 다르게 나타난다.

<br>

<br>

#### DP & dpi

+ Density-Independent-Pixel 의 약자로, 직역하면 "밀도에 독립적인 픽셀"이라는 뜻이다.

+ 픽셀은 촘촘한 경우와 그렇지 않은 경우에 이미지의 크기가 다르기 때문에 밀도에 독립적이라고 말할 수 없지만, dp는 **해상도에 관계 없이 이미지를 같은 *비율*로 표현**하기 때문에 밀도에 독립적이라고 말한다.

+ 보통 dp는 **160dpi**를 갖는 화면에서 하나의 픽셀과 대응한다. 160dpi는 보통 320x480 크기의 해상도를 가지는 3.6인치 스크린을 말하는데, 1인치당 160개의 픽셀을 가지고 있다는 뜻이다.

+ 이 160dpi 해상도에서 1dp는 1pixel이다. 그리고 160dpi 해상도를 기준으로, 화면의 해상도에 따라 **1dp이 나타내는 픽셀의 수는 달라진다.**

+ 160dpi 해상도를 갖는 화면에서 1dp = 1pixel 이다.

  240dpi 해상도를 갖는 화면에서는 1dp = 1.5pixel 이다. -> 160dpi : 240dpi = 1pixel : **1.5pixel** 

  320dpi 해상도를 갖는 화면에서는 1dp = 2pixel 이다. -> 160dpi : 320dpi = 1pixel : **2pixel** 

  480dpi 해상도를 갖는 화면에서 1dp = 3pixel이다. -> 160dpi : 480dpi = 1pixel : **3pixel** 

  <img src = "https://user-images.githubusercontent.com/31370590/126765557-28a97189-4e1d-4a90-8154-45202a8b2173.PNG">

  => 이미지를 dp단위로 표현하여 `layout_width = "3dp", layout_height = "3dp"`로 설정했다고 하자. A의 해상도는 160dpi, B의 해상도는 640dpi로, B가 A보다 4배 더 촘촘하다. A에서는 1dp = 1px이므로 가로 3px, 세로 3px로 표현된다. **화면에서 이미지가 차지하는 비율이 해상도가 달라져도 동일하게 유지되길 원하므로** 비율을 유지하려면, B가 A보다 더 촘촘하므로 B에서는 A보다 더 많은 pixel을 차지해야 한다. 따라서, 1dp = 4 pixel이 된다. 

  => 해상도가 높을수록(더 촘촘할수록) 1dp가 나타내는 pixel의 수는 더 커진다. 

+ **dp = px \* (160dpi / 단말dpi)**

  **px = dp \* (단말dpi / 160dpi)**

<br>

#### 참고

+ [SY Devlog](https://lotuslee.tistory.com/m/120)

<br>

--------

## App icon

+ 런처 아이콘 말고 **앱에서 사용하는 아이콘**

+ 다양한 화면 밀도에 맞는 여러 버전의 비트맵 이미지를 제공하는 대신 **벡터 드로어블**을 사용하는 것이 좋습니다. 벡터 드로어블은 이미지를 구성하는 실제 픽셀을 저장하는 대신 **이미지를 만드는 방법에 관한 지침을 저장하는 XML 파일로 표현**됩니다. 벡터 드로어블은 시각적 품질 손실이나 파일 크기 증가 없이 확장하거나 축소할 수 있습니다.

+ [Material design->resource->~](https://fonts.google.com/icons)에서 5개 테마 중 하나를 사용하여 그릴 수 있음(vector drawble 파일과 bitmap 이미지 파일 5개 다 제공)

+ vector drawble asset 추가하기

  Resource Manager => Vector asset => Clip Art에서 아이콘 선택 or Local에서 SVG, PSD 파일 선택

+ 이를 사용하려면 xml파일에서 imageView를 추가하고, image view의 속성에 `app:srcCompat="@drawable/[vector_asset_id]"`를 추가한다.

<br>

 Q) 

+ 앱 자체의 아이콘은 `image asset`, 앱 내의 여러 아이콘은 `vector asset` ? 둘다 vector drawble? 앱 아이콘은 적응형 아이콘? 

<br>

<br>

-----

## Recycler View

- item, Adapter, ViewHolders, RecyclerView 사이의 관계

+ RecyclerView 구성

  + FrameLayout에 recycler view 배치

  +  항목을 세로 목록으로 표시하므로 `LinearLayoutManager`를 사용

    ```kotlin
    app:layoutManager="LinearLayoutManager"
    ```

  + 화면보다 긴 항목의 세로 목록을 스크롤하려면 **세로 스크롤바** 추가 => `android:scrollbars`

    ```kotlin
    android:scrollbars="vertical"
    ```

+ Adapter 구현
  + Adapter는 데이터를 `RecyclerView`에서 사용할 수 있는 형식으로 조정한다. 
  + 앱을 실행하면 `RecyclerView`가 어댑터를 사용하여 화면에 데이터를 표시하는 방법을 파악한다. 

+ ViewHolder

  `RecyclerView`는 item view(RecyclerView에 표시되는 데이터 항목 하나하나)와 직접 상호작용 하지 않고, `ViewHolders`와 한다. `ViewHolder`는 `RecyclerView`의 list item layout 안의 individual views 를 나타내며 가능한 경우 재사용할 수 있다. 

<br>

#### 전체적인 Recycler View 구성

+ `DataSource` class의 `loadAffirmations()` 함수를 통해 데이터를 가져옴

+ `activity_main.xml`에 `FrameLayout` 안에 `RecyclerView`

+ `list_item.xml`에 `TextView` 정의 => 나중에 확장되어 상위 `RecyclerView`에 하위 요소로 추가됨

  ```kotlin
  <TextView xmlns:android="http://schemas.android.com/apk/res/android"
      android:id="@+id/item_title"
      android:layout_width="wrap_content"
      android:layout_height="wrap_content" />
  ```

  

+ `ItemAdapter` class를 만들고 `RecyclerView`에 전달할 데이터 목록을 `Adapter`에 전달할 수 있도록 생성자에 매개변수를 추가(문자열 리소스를 확인하기 위해서 `Context` 유형의 매개변수도 추가)

+ `ItemAdapter` class 안에 `ItemViewHolder` class도 생성(`ItemAdapter`만 `ItemViewHolder`를 사용하므로)

  ```kotlin
  class ItemAdapter(private val context: Context, private val dataset: List<Affirmation>) {
  
      class ItemViewHolder(private val view: View) : RecyclerView.ViewHolder(view) {
          val textView: TextView = view.findViewById(R.id.item_title)
      }
  }
  ```

+ 추상 클래스 `RecyclerView.Adapter`에서 `ItemAdapter`를 확장 =>  `RecyclerView.Adapter`에서 Adapter의 추상 메서드 override

  ```kotlin
  class ItemAdapter(
      private val context: Context,
      private val dataset: List<Affirmation>
  ) : RecyclerView.Adapter<ItemAdapter.ItemViewHolder>(){
      // ~
  }
  ```

  + `getItemCount()` => 데이터 세트의 크기를 반환

  + `onCreateViewHolder()` => `RecyclerView`의 ViewHolder를 만들기 위해 레이아웃 관리자가 호출합니다(재사용할 수 있는 기존 뷰 홀더가 없는 경우)

  + `onBindViewHolder()` =>  list item view의 콘텐츠를 바꾸기 위해 레이아웃 관리자가 호출

    

+ RecyclerView를 사용하도록 MainActivity 수정

  `MainActivity`에서 `Datasource` 클래스와 `ItemAdapter` 클래스를 사용하여 `RecyclerView`에 항목을 만들고 표시

  `MainActivity.kt`에 `onCreate()` 함수 안에 아래 코드 추가

  ```kotlin
  val myDataset = Datasource().loadAffirmations()
  val recyclerView = findViewById<RecyclerView>(R.id.recycler_view)
  recyclerView.adapter = ItemAdapter(this, myDataset)
  recyclerView.setHasFixedSize(true)
  ```

=>  **Adapter**가 핵심적인 기능 ?

<br>

#### `list_item`에 `textview`말고 `imageView`같은 다른 뷰도 추가하고 싶으면

+ `Affirmation` 데이터 클래스에서 이미지 리소스 ID의 값을 보유하는 속성을 추가

  ```kotlin
  data class Affirmation(
     @StringRes val stringResourceId: Int,
     @DrawableRes val imageResourceId: Int
  )
  ```

+ `Datasource` class에서도 `loadAffirmations` 함수 수정

  ```kotlin
  fun loadAffirmations(): List<Affirmation> {
          return listOf<Affirmation>(
              Affirmation(R.string.affirmation1, R.drawable.image1),
              // ~
          )
  ```

+ `list_item.xml`에도 `imageview` 추가(`LinearLayout`으로 변경)

+ `ItemViewHolder`에도  `ImageView`에 대한 참조를 보유하도록

  ```kotlin
  class ItemViewHolder(private val view: View): RecyclerView.ViewHolder(view) {
      val textView: TextView = view.findViewById(R.id.item_title)
      val imageView: ImageView = view.findViewById(R.id.item_image)
  }
  ```

+ `ItemAdapter`에서 `OnBindViewHolder()` 함수도 변경

  ```kotlin
  override fun onBindViewHolder(holder: ItemViewHolder, position: Int) {
      val item = dataset[position]
      holder.textView.text = context.resources.getString(item.stringResourceId)
      holder.imageView.setImageResource(item.imageResourceId)
  }
  ```

<br>

<br>


-----

## 인텐트

<br>

+ Intent란 안드로이드 4대 컴포넌트가 서로 데이터를 주고받기 위한 메시지 객체이다 .

  명시적 인텐트 : 액티비티 이름을 명확하게 지정할 때 사용하는 방법
  암시적 인텐트 : 약속된 액션을 지정하여 안드로이드에서 제공하는 기종의 응용 프로그램을 실행하는 것

  + 명시적 인텐트 설정

    ```kotlin
    val intent = Intent(this, DetailActivity::class.kotlin)
    intent.putExtra("letter", "hello bundle")
    intent.putExtra("letter2", 2020)
    
    startActivity(intent)
    ```

  + `DetailActivity`에서 intent로 넘겨진 정보를 받으려면

    ```kotlin
    val letterId = intent?.extras?.getString("letter").toString()
    
    // val letterId = intent.getStringExtra("letter") 
    ```

    + 여기서 intent는 `DetailActivity`의 property라기 보다는, property of any Activity 이다. 해당 액티비티를 launch하는데 사용된 intent에 대한 reference를 유지한다.
    + extras 속성은 `Bundle` 유형이고 짐작했겠지만 인텐트에 전달된 모든 extras에 액세스하는 방법을 제공합니다.
    + 실제 문자가 `getString`으로 검색되어 `String?`를 반환하므로 `toString()`을 호출하여 `null`이 아닌 `String`인지 확인한다. 

<br>

<br>

-----

## Layout에 대해

+ 레이아웃에 단일 하위 뷰 `RecyclerView`만 있으므로, 단일 하위 뷰를 보유하는 데 사용해야 하는 더 간단한 `ViewGroup`인 `FrameLayout`으로 전환할 수 있습니다.
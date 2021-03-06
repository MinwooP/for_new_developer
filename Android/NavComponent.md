# Navigation Component

-----

## π Jetpack Navigation Component

#### Andriod Jetpackμμ μ κ³΅νλ *Navigation component*

- Navigation graph: νμ κ·Έλνλ μ±μμ νμμ μκ°μ μΌλ‘ λ³΄μ¬μ£Όλ XML νμΌμλλ€. νμΌμ κ°λ³ activity λ° fragmentμ μμνλ ***destination***κ³Ό ν destinationμμ λ€λ₯Έ destinationμΌλ‘ μ΄λνλ €κ³  μ½λμμ μ¬μ©ν  μ μλ ***destination μ¬μ΄μ action***μΌλ‘ κ΅¬μ±λ©λλ€. λ μ΄μμ νμΌκ³Ό λ§μ°¬κ°μ§λ‘ Android μ€νλμ€λ νμ κ·Έλνμ λμκ³Ό μμμ μΆκ°νλ μκ°μ  νΈμ§κΈ°λ₯Ό μ κ³΅ν©λλ€.
- `Navhost`: `NavHost`λ **activity λ΄μμ νμ κ·Έλνμ destinationμ νμ**νλ λ° μ¬μ©λ©λλ€. νλκ·Έλ¨ΌνΈ κ°μ μ΄λνλ©΄ `NavHost`μ νμλλ destinationμ΄ μλ°μ΄νΈλ©λλ€. `MainActivity`μμ `NavHostFragment`λΌλ κΈ°λ³Έ μ κ³΅ κ΅¬νμ μ¬μ©ν©λλ€.
- `NavController`: `NavController` κ°μ²΄λ₯Ό μ¬μ©νλ©΄ ** `NavHost`μ νμλλ destination κ° νμμ μ μ΄**ν  μ μμ΅λλ€. μΈννΈλ₯Ό μ¬μ©ν  λλ `startActivity()`λ₯Ό νΈμΆνμ¬ μ νλ©΄μΌλ‘ μ΄λν΄μΌ νμ΅λλ€. νμ κ΅¬μ±μμλ₯Ό μ¬μ©νλ©΄ `NavController`μ `navigate()` λ©μλλ₯Ό νΈμΆνμ¬ νμλλ νλκ·Έλ¨ΌνΈλ₯Ό κ΅μ²΄ν  μ μμ΅λλ€. `NavController`λ₯Ό μ¬μ©νλ©΄ μμ€ν 'μλ‘' λ²νΌμ μλ΅νμ¬ μ΄μ μ νμλ νλκ·Έλ¨ΌνΈλ‘ λ€μ μ΄λνλ κ²κ³Ό κ°μ μΌλ°μ μΈ μμμ μ²λ¦¬ν  μλ μμ΅λλ€.



#### Navigation Component λ₯Ό μ¬μ©νκΈ° μν μ€λΉ

1. Navigation Dependency

   + `build.gradle` νμΌμ **buildscript > ext**μμ `material_version` μλμ `nav_version`μ `2.3.1`λ‘ μ€μ 

     ```kotlin
     buildscript {
         ext {
             nav_version = "2.3.1"
         }
     } 
     ```

   + μ± μμ€ `build.gradle` νμΌμμ μ’μ ν­λͺ© κ·Έλ£Ήμ λ€μμ μΆκ°

     ```kotlin
     implementation "androidx.navigation:navigation-fragment-ktx:$nav_version"
     implementation "androidx.navigation:navigation-ui-ktx:$nav_version"
     ```

2. Safe Args Plug-in

   + **Words** μ±μ νμ κ΅¬μ±μμλ₯Ό κ΅¬ννκΈ° μ μ νλκ·Έλ¨ΌνΈ κ°μ λ°μ΄ν°λ₯Ό μ λ¬ν  λ μ ν μμ μ±μ μ§μνλ Gradle νλ¬κ·ΈμΈμΈ **Safe Args**λΌλ ν­λͺ©λ μΆκ°ν΄μΌ ν©λλ€.

     1. μ΅μμ `build.gradle` νμΌμ **buildscript > dependencies**μμ λ€μ ν΄λμ€ κ²½λ‘λ₯Ό μΆκ°

        ```kotlin
        classpath "androidx.navigation:navigation-safe-args-gradle-plugin:$nav_version"
        ```

     2. μ± μμ€ `build.gradle` νμΌμ μλ¨μ μλ `plugins` λ΄μμ `androidx.navigation.safeargs.kotlin`μ μΆκ°

        ```kotlin
        plugins {
            ~
             id 'androidx.navigation.safeargs.kotlin'
        }
        ```



#### Navigation Graph μ¬μ©

+ Navigation Graph : νλκ·Έλ¨ΌνΈ κ° νμμ κ΅¬ννλλ° λμμ΄ λλ μκ°μ  νΈμ§κΈ°
+ νμ κ·Έλν(λλ μ€μ¬μ NavGraph)λ μ± νμμ κ°μ λ§€νμλλ€. κ° νλ©΄(λλ μ΄ κ²½μ°μ νλκ·Έλ¨ΌνΈ)λ μ΄λν  μ μλ κ°λ₯ν 'destination'μ΄ λ©λλ€. `NavGraph`λ κ° destinationμ΄ μλ‘ κ΄λ ¨λλ λ°©μμ λ³΄μ¬μ£Όλ XML νμΌλ‘ λνλΌ μ μμ΅λλ€. 
+ νμ κ·Έλνμ destinationμ `FragmentContainerView`λ‘ μ¬μ©μμκ² νμ



#### MainActivtiyμμ FragmentContainerView μ¬μ©

1. MainActivity μμ 

   `MainActivity`μ μ©λλ₯Ό λ³κ²½νμ¬ νλκ·Έλ¨ΌνΈμ `NavHost` μ­ν μ ν  `FragmentContainerView`λ₯Ό ν¬ν¨ν©λλ€. μ΄ μμ λΆν° λͺ¨λ  μ±μ νμμ `FragmentContainerView` λ΄μμ μ€νλ©λλ€. 

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

   + `activity_main.xml`μμ `FrameLayout`μμ μλ μ‘΄μ¬νλ `recyclerView`λ₯Ό `FragmentContainerView`λ‘ λ°κΏλλ€. 

   + `android:name="androidx.navigation.fragment.NavHostFragment"`

     μ΄ μμ±μ νΉμ  νλκ·Έλ¨ΌνΈλ₯Ό μ§μ ν  μ μμ§λ§ `NavHostFragment`λ‘ μ€μ νλ©΄ `FragmentContainerView`κ° νλκ·Έλ¨ΌνΈ κ°μ μ΄λν  μ μμ΅λλ€.

   + `app:defaultNavHost="true"`

     μ΄λ κ² νλ©΄ **νλκ·Έλ¨ΌνΈ μ»¨νμ΄λκ° νμ κ³μΈ΅ κ΅¬μ‘°μ μνΈμμ©**ν  μ μμ΅λλ€. μλ₯Ό λ€μ΄ μμ€ν λ€λ‘ λ²νΌμ λλ₯΄λ©΄ μ»¨νμ΄λλ μ νλμ΄ νμλ  λμ λ§μ°¬κ°μ§λ‘ μ΄μ μ νμλ νλκ·Έλ¨ΌνΈλ‘ λ€μ μ΄λν©λλ€.

   + `app:navGraph="@navigation/nav_graph" `

     μ΄λ μ±μ νλκ·Έλ¨ΌνΈκ° μλ‘ μ΄λν  μ μλ λ°©λ²μ μ μνλ XML νμΌμ κ°λ¦¬ν΅λλ€.

     

2. νμ κ·Έλν μ€μ 

   + `nav_graph.xml`μ΄λ¦μ μλ‘μ΄ Android Resource File μμ±(Resource type: Navigation)νλ©΄ μ μκ°μ  νΈμ§κΈ°κ° νμλ©λλ€. `FragmentContainerView`μ `navGraph` μμ±μμ `nav_graph`λ₯Ό μ΄λ―Έ μ°Έμ‘°νμΌλ―λ‘ μ destinationμ μΆκ°νλ €λ©΄ νλ©΄ μλ¨ μΌμͺ½μμ μλ‘ λ§λ€κΈ° λ²νΌμ ν΄λ¦­νμ¬ κ° νλκ·Έλ¨ΌνΈμ destinationμ λ§λ­λλ€. 

   + Navigation Action λ§λ€κΈ°

     `letterListFragment`μμ `wordListFragment` destination κ°μ νμ μμμ λ§λ€λ €λ©΄ `letterListFragment` destination μλ‘ λ§μ°μ€λ₯Ό κ°μ Έκ°μ μ€λ₯Έμͺ½μ νμλλ μμμ `wordListFragment` destinationμΌλ‘ λλκ·Έν©λλ€. νμ΄νλ‘ νμλλ `action_letterListFragment_to_wordListFragment`μ΄λ¦μ actionμ΄ μμ±λ©λλ€. 

   + `WordListFragment`μ μΈμ μ§μ 

     μΈννΈλ₯Ό μ¬μ©νμ¬ νλ μ¬μ΄λ₯Ό μ΄λν  λ μ νλ λ¬Έμκ° `wordListFragment`μ μ λ¬λ  μ μλλ‘ 'extra'λ₯Ό μ§μ νμ΅λλ€. Navigationμ  destination κ°μ λ§€κ°λ³μ μ λ¬λ μ§μνλ©΄μ μ νμ μμ ν λ°©μμΌλ‘ μ΄λ₯Ό μ€νν©λλ€.

     `wordListFragment` destinationμ μ ννκ³  μμ± μ°½μ **Arguments**μμ λνκΈ° λ²νΌμ ν΄λ¦­νμ¬ μ μΈμλ₯Ό λ§λ­λλ€. μΈμλ `letter`λΌκ³  νκ³  μ νμ `String`μ΄μ΄μΌ ν©λλ€. μ¬κΈ°μμ μ΄μ μ μΆκ°ν Safe Args νλ¬κ·ΈμΈμ΄ νμν©λλ€. μ΄ μΈμλ₯Ό λ¬Έμμ΄λ‘ μ§μ νλ©΄ νμ μμμ΄ μ½λμμ μ€νλ  λ `String`μ΄ μμλ©λλ€.



3. νμ μμ μ€ν

   `LetterAdapter`.`kt`λ₯Ό μ΄μ΄ νμ μμμ μ€ν

   + λ²νΌμ `onClickListener()` μ½νμΈ λ₯Ό μ­μ ν©λλ€. λμ  λ°©κΈ λ§λ  νμ μμμ κ²μν΄μΌ ν©λλ€. `onClickListener()`μ λ€μμ μΆκ°ν©λλ€.

     ```kotlin
     val action = LetterListFragmentDirections.actionLetterListFragmentToWordListFragment(letter = holder.button.text.toString())
     ```

     `LetterListFragmentDirections`λ₯Ό μ¬μ©νλ©΄ `letterListFragment`λΆν° κ°λ₯ν λͺ¨λ  νμ κ²½λ‘λ₯Ό μ°Έμ‘°ν  μ μμ΅λλ€. `actionLetterListFragmentToWordListFragment()` ν¨μλ

     `wordListFragment.`λ‘ μ΄λν  νΉμ  actionμλλ€.

   + νμ μμ μ°Έμ‘°κ° μμΌλ©΄ *NavController*(νμ μμ μ€νμ νμ©νλ κ°μ²΄) μ°Έμ‘°λ₯Ό κ°μ Έμμ μμμ μ λ¬νλ `navigate()`λ₯Ό νΈμΆνλ©΄ λ©λλ€.

     ```kotlin
     holder.view.findNavController().navigate(action)
     ```



4. MainActivity κ΅¬μ±

   + `navController` μμ±μ λ§λ­λλ€. `onCreate`μμ μ€μ λλ―λ‘ `lateinit`λ‘ νμλ©λλ€.

     ```kotlin
     private lateinit var navController: NavController
     ```

   + κ·Έλ° λ€μ `onCreate()`μμ `setContentView()`λ₯Ό νΈμΆν ν `nav_host_fragment`(`FragmentContainerView`μ IDμ) μ°Έμ‘°λ₯Ό κ°μ Έμμ `navController` μμ±μ ν λΉν©λλ€.

     ```kotlin
     val navHostFragment = supportFragmentManager
         .findFragmentById(R.id.nav_host_fragment) as NavHostFragment
     navController = navHostFragment.navController
     ```

   + κ·Έλ¦¬κ³  `onCreate()`μμ `setupActionBarWithNavController()`λ₯Ό νΈμΆνμ¬ `navController`λ₯Ό μ λ¬ν©λλ€. μ΄λ κ² νλ©΄ μμ λͺ¨μ(μ± λ°) λ²νΌμ΄ νμλ©λλ€.

     ```kotlin
     setupActionBarWithNavController(navController)
     ```

   + λ§μ§λ§μΌλ‘ `onSupportNavigateUp()`μ κ΅¬νν©λλ€. XMLμμ `defaultNavHost`λ₯Ό `true`λ‘ μ€μ νλ κ²κ³Ό ν¨κ» μ΄ λ©μλλ₯Ό μ¬μ©νλ©΄ **μλ‘** λ²νΌμ μ²λ¦¬ν  μ μμ΅λλ€. κ·Έλ¬λ activityκ° κ΅¬νμ μ κ³΅ν΄μΌ ν©λλ€.

     ```kotlin
     override fun onSupportNavigateUp(): Boolean {
        return navController.navigateUp() || super.onSupportNavigateUp()
     }
     ```

   + μ΄λ λͺ¨λ  κ΅¬μ±μμλ νμμ΄ νλκ·Έλ¨ΌνΈλ‘ μλνλλ‘ μ μλ¦¬μ μμ΅λλ€. κ·Έλ¬λ μ΄μ  νμμ΄ μΈννΈ λμ  νλκ·Έλ¨ΌνΈλ₯Ό μ¬μ©νμ¬ μ€νλλ―λ‘ `WordListFragment`μμ μ¬μ©νλ λ¬Έμμ μΈννΈ extraκ° λ μ΄μ μλνμ§ μμ΅λλ€. λ€μ λ¨κ³μμλ `WordListFragment`λ₯Ό μλ°μ΄νΈνμ¬ `letter` μΈμλ₯Ό κ°μ Έμ΅λλ€.





#### Navigation APIs

+ `NavHostFragment` : νμ κ΅¬μ±μμκ° κ΅νλλ λͺ©μ μ§ μ»¨νμ΄λ μ­ν μ νλ€. μ΄λ activityλ₯Ό ν΅ν΄  νμν  λ λμ²΄λλ fragmentλ₯Ό λ΄λ μ»¨νμ΄λμ΄λ€.

+ `NavController` : νμ κ΅¬μ±μμ(navigate components)μ λ΄λΆμμλ‘ μ€μ λ‘ νμ μμμ νλ€. μ§νμ€μΈ μμμ λ³΄μ¬μ£Όλ μλ΄μμ κ°λ€.  

+ `NavigationView` : `NavHostFragment`μμ μκ³ , νμ κ΅¬μ±μμμ μΌλΆλ μλ. νμ κ΅¬μ±μμ μ μ μ‘΄μ¬νμΌλ©°, νμ μ°½ λ΄μ μλ λ©λ΄μ κ΄λ ¨μ΄ μμ. λ©λ΄ ν­λͺ©κ³Ό νμ μ°½μ μ ννλ©΄ μ± λ΄ λ€λ₯Έ λͺ©μ μ§λ‘ μ΄λνλ€. νμ§λ§ νμ κ΅¬μ±μμμ μΌλΆκ° μλλ©°, νμ κ΅¬μ±μμμ ν­λͺ©κ³Ό μνΈμμ© νλ κ²μ΄λ€.  

+ `NavigationUI` : `NavHostFragment` μΈλΆ μ½νμΈ  μλ°μ΄νΈλ₯Ό μ±μμ§λλ€. ex) navigationView, BottomNavBar ? 

  => μ΄λ₯Ό μ¬μ©νλ©΄ ν¨μ¬ κ°νΈνκ² μ± λ΄ νμμ λ§λ€κ³  μμ ν  μ μμ.

# Array

Operation

1. __Reading__
   
   배열에서 읽는 건 굉장히 빠르다. 컴퓨터가 배열이 어디서 시작하는지를 알고 있기 때문에 많은 자료를 읽어야 한다면, 배열이 좋다. Random access 덕분에. 배열이 얼마나 긴지랑은 상관 없다. 배열의 요소가 5개이든, 100개이든, 인덱스에서 요소를 읽어내는 속도는 동일하기 때문에 
   
2. __Searhing__ 
   
   Linear search
   시간이 좀 걸린다. 검색과는 다름. 
   search하려는 값이 배열에 존재하는지, 어디에 있는지 모르는 상태. 
   불행하게도, 하나하나 다 뒤져야 함. 주소가 있어서 접근은 할 수 있지만, 그 안의 값은 모르는 상황
   
3. __Insert__
   
   배열을 만들 때에는, 메모리 공간을 미리 확보해야 한다. 즉 배열의 크기를 미리 지정해줘야 함
   배열의 끝, 중간, 처음 중 어디에 insert 할 지에 따라 달라짐. 배열의 크기보다 큰 자료를 insert 하는지에 따라 달라짐
   
4. __Delete__
   
   insert와 비슷
   
   

* [x] Reading은 굉장히 빠르지만, search, insert, delete는 느림.  배열에서 무엇인가를 추가하거나 삭제하고 싶다면, 배열의 맨 끝에서 작업하는 것이 최선. 



> _시간복잡도_ 
> 데이터 구조의 오퍼레이션 혹은 알고리즘이 얼마나 빠르고 느린지 측정하는 방법
> 이건 실제 시간을 1초, 1분 단위로 계산하는 것이 아니라 얼마나 많은 '단계'가 있는
> 지를 고려


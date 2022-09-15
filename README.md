# Algorithm_Assignment
2022-2학기 알고리즘 과제

- [x] 01_Test([test.cpp](https://github.com/meanjoo/Algorithm_Assignment/blob/master/Algorithm/test.cpp))

- [x] 02_Spin & Slide([spinslide.cpp](https://github.com/meanjoo/Algorithm_Assignment/blob/master/Algorithm/spinslide.cpp))

- [x] 03_계단 오르기([stairs.cpp](https://github.com/meanjoo/Algorithm_Assignment/blob/master/Algorithm/stairs.cpp))

- [x] 04_Interesting Gain([gain.cpp](https://github.com/meanjoo/Algorithm_Assignment/blob/master/Algorithm/gain.cpp))

- [x] 05_달팽이([snail.cpp](https://github.com/meanjoo/Algorithm_Assignment/blob/master/Algorithm/snail.cpp))

- [ ] 06_격자 색칠

<hr>

#### 05_달팽이
이렇게 푸는 게 맞는지도 모르겠지만 나중에 무슨 함수인지 모를 거 같아서 쓰는 내가 작성한 함수에 대한 설명이다.  
푸는 방법은 숫자가 몇 번째 껍질에 존재하는지 구해서 이를 기반으로 숫자의 좌표를 알아내는 것이라고 생각했다.

`int getLevel(ll n, ll x)` := x가 n * n에서 얼마나 안쪽 사각형에 포함되는 수인지 리턴하는 함수. 가장 바깥 사각형을 level 0이라고 한다.  
s는 해당 level 사각형에 포함되는 가장 작은 숫자, e는 해당 level 사각형에 포함되는 가장 큰 숫자이다.  
즉 level l에 포함되는 숫자는 [s, e]이다.  
한 변이 n인 정사각형의 가장 바깥 사각형(정사각형의 껍질)에 있는 수의 개수는 4n-4 = 4(n-1)이다.  
4n-4인 이유는 사각형이므로 한 변이 n인 변이 4개 존재하고 이렇게 더하면서 4개의 꼭짓점에 있는 숫자가 중복으로 카운팅되었기 때문에 4를 빼준다.  
가장 바깥에서 하나 안쪽에 있는 사각형에 있는 수의 개수는 4(n-2)-4 = 4(n-3)이다. 그 다음은 4(n-5), 4(n-7), ... 이런 식이다.  
(안으로 한 껍질 들어갈 때마다 양옆이 하나씩 없어지기 때문에 -2씩 감소한다.)  
정리하면 가장 바깥 껍질을 1로 볼 때, k(k>=1)번째 껍질에 있는 숫자의 개수는 4(n-(2k-1))이다.  
위 식에 따르면 껍질의 시작이 1인데, 리턴하고자 하는 껍질의 시작은 0이므로 초기 level의 값을 -1로 설정했다.  
(main에서 getLevel을 호출할 때, 파라미터 n의 값으로 n-1을 줬기 때문에 4 * (n-1)이 아닌 4 * n으로 계산하고 있다.)  

ex. N=5  
level 0; s = 1, e = 16 (= 1 + 4 * 4 - 1)  
level 1; s = 17, e = 24 (= 17 + 4 * 2 - 1)  
level 2; s = 25, e = 24 (= 25 + 4 * 0 - 1) // e가 정확하지는 않지만 level 값을 구하는 데에는 영향을 주지 않는다.
<img src="https://github.com/meanjoo/LinkPicture/blob/main/getLevel.jpg" width="600" height=auto/>

`Point getPoint(ll n, ll level, ll num)` := level을 기반으로 해서 n * n 달팽이 배열에서 num의 좌표를 리턴하는 함수

`bool isSqure(Point& p1, Point& p2)` := 두 점을 꼭짓점으로 하는 사각형이 정사각형인지를 리턴하는 함수

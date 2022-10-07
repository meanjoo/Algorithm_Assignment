# Algorithm_Assignment_Code
2022-2학기 알고리즘 과제

- [x] 01_Test ([test.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/test.cpp))

- [x] 02_Spin & Slide ([spinslide.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/spinslide.cpp))

- [x] 03_계단 오르기 ([stairs.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/stairs.cpp))

- [x] 04_Interesting Gain ([gain.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/gain.cpp))

- [x] 05_[달팽이](https://github.com/meanjoo/Algorithm_Assignment_Code#05_%EB%8B%AC%ED%8C%BD%EC%9D%B4) ([snail.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/snail.cpp))

- [x] 06_[격자 색칠](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/README.md#06_%EA%B2%A9%EC%9E%90-%EC%83%89%EC%B9%A0) ([grid.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/grid.cpp))

== Divide & Conquer ==

- [x] 07_순열을 이진트리로 ([permutation.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/permutation.cpp))

- [x] 08_Bitmap ([bitmap.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/bitmap.cpp)) - [같은 문제](https://www.acmicpc.net/problem/6397)

== Dynamic Programming ==

- [x] 09_[격자 경로](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/README.md#09_%EA%B2%A9%EC%9E%90-%EA%B2%BD%EB%A1%9C) ([gridpath.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/gridpath.cpp))

- [x] 10_[Coin Game](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/README.md#10_coin-game) ([coin.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/coin.cpp))

- [x] 11_[Coin Move Game](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/README.md#11_coin-move-game) ([coinmove.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/coinmove.cpp))

- [x] 12_[정육면체 자르기](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/README.md#12_%EC%A0%95%EC%9C%A1%EB%A9%B4%EC%B2%B4-%EC%9E%90%EB%A5%B4%EA%B8%B0) ([cube.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/cube.cpp)) - [같은 문제](https://www.acmicpc.net/problem/9029)

- [x] 13_[카드 선택](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/README.md#13_%EC%B9%B4%EB%93%9C-%EC%84%A0%ED%83%9D) ([card.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/card.cpp))

- [x] 14_[격자경로(또 다른)](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/README.md#14_%EA%B2%A9%EC%9E%90%EA%B2%BD%EB%A1%9C%EB%98%90-%EB%8B%A4%EB%A5%B8) ([path.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/path.cpp))

<hr>

### 05_달팽이
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code)

(2022.09.15) 이렇게 푸는 게 맞는지도 모르겠지만 나중에 어떤 생각으로 짰는지 모를 거 같아서 쓰는 내가 작성한 함수에 대한 설명이다.  
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
해당 레벨의 시작 숫자 = 이전 레벨 시작 숫자 + 이전 레벨에 존재하는 숫자의 개수  
level 0; 1  
level 1; 1 + 4(n-1)  
level 2; 1 + 4(n-1) + 4(n-3) = 1 + 4((n-1) + (n-3))  
level 3; 1 + 4(n-1) + 4(n-3) + 4(n-5) = 1 + 4((n-1) + (n-3) + (n-5))  
...  
level k; 1 + 4(n-1) + 4(n-3) + 4(n-5) + 4(n-7) + ... + 4(n-(2k-1)) = 1 + 4((n-1)+(n-3)+(n-5)+(n-7)+...+(n-(2k-1)))  
따라서 level k의 시작 숫자는 1 + 4((n-1)+(n-3)+(n-5)+(n-7)+...+(n-(2k-1)))임을 알 수 있다.  
식을 정리하면 1 + 4*(nk - 1부터 총 k개의 홀수의 합)이다. 1부터 k까지의 홀수의 합은 n<sup>2</sup>이다.  
(&Sigma;(n=1~k)(2n-1)을 정리해보면 k<sup>2</sup>이다.)  
즉 해당 레벨의 시작 숫자는 1+(n * k - k<sup>2</sup>)이다.
step과 나머지 코드들은 나중에 봐도 다시 읽어보면 알 것이라고 생각한다.  
(4가지 진행방향을 나누어서 좌표를 구한 후 반환하는 과정)  

`bool isSqure(Point& p1, Point& p2)` := 두 점을 꼭짓점으로 하는 사각형이 정사각형인지를 리턴하는 함수  

### 06_격자 색칠
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code)

아름답게 칠한다는 것은 결국 사각형은 세로 방향으로만으로 색칠되든지 가로 방향으로만 색칠되어야 한다.  
세로로 또는 가로로 최소 2줄 이상의 줄을 하나의 색깔로 칠하면서 사각형을 가득 채울 수 있는지 판별하는 문제이다. 사용하지 않는 물감이 있어도 된다.  
물감으로 칠할 수 있는 칸이 2줄 이상이라면 최대 그 물감으로 몇 줄을 칠할 수 있는지 카운팅한다.  
모든 물감에 대해서 이렇게 카운팅된 수가 사각형의 변보다 크다면 아름답게 칠할 수 있는 것이다.  
***하나 주의해야 할 점은 변이 홀수일 때이다. 변이 홀수이면 적어도 한 색깔은 3줄 이상을 칠할 수 있어야 한다.  
1줄만 어떤 색깔로 칠해지면 아름답게 칠해진 게 아니다.***  
(N * M)  
1. 세로 방향으로 색칠하는 경우  
1줄의 크기는 N이다.  
물감의 용량을 N으로 나눈 몫이 2 이상이면 cnt에 그 몫을 더해준다.  
모든 물감에 대해 이를 반복한 후에 cnt가 M 이상이면 아름답게 칠할 수 있다는 것이다.
2. 가로 방향으로 색칠하는 경우  
1줄의 크기는 M이다.  
물감의 용량을 M으로 나눈 몫이 2 이상이면 cnt에 그 몫을 더해준다.  
모든 물감에 대해 이를 반복한 후에 cnt가 N 이상이면 아름답게 칠할 수 있다는 것이다.

### 09_격자 경로
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code)

전형적인 최소 경로 비용 합을 찾는 dp 문제 + 그 경로를 추적하면 되는 문제이다.  
만약 최소 경로 비용이 같으면 우측 우선 경로를 택한다.

**dp 배열의 각 칸은 int값과 string을 가진다. string은 우측 우선 경로를 판별할 때 사용한다.**

최소 경로 비용 합을 찾는 문제의 대부분은 dp 배열을 다음과 같이 채울 수 있다. 이는 모든 칸이 이동할 수 있는 칸일 때이다.
```
dp[0][0] = cost[0][0];
dp[0][j] = cost[0][j] + dp[0][j-1]; (1<=j<m)
dp[i][0] = cost[i][0] + dp[i-1][0]; (1<=i<n)
dp[i][j] = cost[i][j] + min(dp[i-1][j], dp[i][j-1]); (1<=i<n, 1<=j<m)
```

그런데 이 문제에서는 이동할 수 없는 칸(-1)도 있기 때문에 일단 dp 배열을 -1로 초기화해둔다.  
`dp[0][0] = cost[0][0];`  
dp[0][0]을 제외한 0열과 0행을 채워야하는데 이동할 수 없는 칸이 있다고 했다.  
0행과 0열을 각각 앞서 말한 방법처럼 채우다가  
```
dp[0][j] = cost[0][j] + dp[0][j-1]; (1<=j<m)
dp[0][j] = cost[0][j] + dp[0][j-1]; (1<=j<m)
```
cost 값이 -1인 순간 dp 값의 갱신을 멈추면 된다.  
그리고 경로도 저장해줘야 하는데 dp[0][j]의 string에는 dp[0][j-1]의 string에 'R'을 붙인 값을,  
dp[i][0]의 string에는 dp[i-1][0]의 string에 'D'를 붙인 값을 저장해준다.  
**string이 의미하는 것은 (0, 0)에서 어떻게 이동해서 (i, j)에 도달한지를 나타내는 것이다.**  
ex) (4, 3)에 있는 string이 RRDDDDR이면 (0, 0) (0, 1) (0, 2) (1, 2) (2, 2) (3, 2) (4, 2) (4, 3)의 경로로 (4, 3)에 온 것을 의미한다.

그리고 나머지 dp[i][j]에 대해서는 조건에 따라 값을 갱신해주면 되는데 그 전제가 cost[i][j]가 -1이 아닐 때이다.  
왜냐하면 cost[i][j]가 -1이면 (i, j)는 이동할 수 없는 곳인데 dp 배열의 초기값은 -1로 되어 있어 값을 갱신할 필요가 없다.  
cost[i][j]가 양수 값을 가지면 (i, j)의 왼쪽과 위를 보면 된다.  
1. 왼쪽과 위쪽이 전부 이동할 수 없는 곳이면 (i, j)로는 올 방법이 없으므로 dp[i][j]는 값의 변화 없이 초기값인 -1이다.
2. 왼쪽에서만 (i, j)로 올 수 있다면 `dp[i][j] = cost[i][j] + dp[i][j-1]; dp[i][j]의 string = dp[i][j-1]의 string + 'R';`
3. 위쪽에서만 (i, j)로 올 수 있다면 `dp[i][j] = cost[i][j] + dp[i-1][j]; dp[i][j]의 string = dp[i-1][j]의 string + 'D';`
4. 왼쪽과 위쪽 모두에서 (i, j)로 올 수 있다면 1차로는 최소 비용, 2차로는 우측 우선 경로를 택하면 된다.  
`dp[i][j-1] < dp[i-1][j]`이면 `dp[i][j] = cost[i][j] + dp[i][j-1]; dp[i][j]의 string = dp[i][j-1]의 string + 'R';`  
`dp[i][j-1] > dp[i-1][j]`이면 `dp[i][j] = cost[i][j] + dp[i-1][j]; dp[i][j]의 string = dp[i-1][j]의 string + 'D';`  
`dp[i][j-1] == dp[i-1][j]`인 경우 때문에 string이 필요한 것이다.  
이때는 dp[i][j-1]의 string과 dp[i-1][j]의 string의 처음부터 봤을 때 R이 먼저 나오는 곳을 택하면 된다.

이렇게 dp 배열이 완성되고 났을 때 dp[n-1][m-1]의 cost가 -1이면 (n-1, m-1)에 도달할 수 없는 것이다.  
그렇지 않다면 (n-1, m-1)에 도달할 수 있는 것이고 그때의 경로는 dp[n-1][m-1]에 저장된 string에 따라 결정된다.

ps) 문제가 어렵다기보다 처음에 우측 우선 경로라는 것을 이해를 잘못했었다.  
우측 우선이라는 게 예를 들어 (2, 3)에서 봤을 때 (2, 2)까지 오는 비용과 (1, 3)까지 오는 비용이 같다고 하자.  
그럼 나는 우측 우선을 (2, 2)에서 (2, 3)으로 오는 게 우측으로 오는 거니까 (2, 2)에서 (2, 3)으로 오는 경로를 택하는 것이라고 생각을 했었다.  
근데 이게 아니라 (0, 0)에서부터 시작해야한다. 아래 그림을 보자.  
<img src="https://github.com/meanjoo/LinkPicture/blob/main/gridpath.JPG" width="400" height=auto/>  
(2, 3)까지 오는 빨간색 경로와 파란색 경로가 있으면 (2, 3)에서는 빨간색 경로를 택해야 한다는 것이다.  
빨간색 경로가 (0, 0)에서 우측으로 더 먼저 이동한 경로이기 때문이다.

### 10_Coin Game
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code)

Top-down 방식으로 짰다. memoization하기 위한 배열을 3차원 배열로 둔다. 코인은 항상 3더미이기 때문이다.  
**dp[i][j][k]는 내 차례때 코인이 (i j k)라면 그때의 승패여부이다.**  
각 코인 더미의 최대 코인 개수는 100개이므로 101 * 101 * 101 배열을 만들어주면 된다.  
메모리를 조금이라도 줄이려고 dp 배열을 int가 아닌 char로 선언했다. 게다가 승패만 알면 돼서 값도 int까지 필요없다.

**dp[i][j][k]의 값이 'W'이면 필승, 'L'이면 필패이다.  
base는 (0 0 0)='W', (0 0 1) = 'L', (0 1 0) = 'L', (1 0 0) = 'L', (1 1 0) = 'W', (1 0 1) = 'W', (0 1 1)='W', (1 1 1)='L'이다.**  
(사실 처음에는 base에 (0 0 0)이 있어야겠다는 생각을 하지 않았는데 재귀로 부르다 보면 (0 0 0)을 call하는 경우가 생기길래 초기값을 줬다. (0 0 0)인 경우가 필승인지 필패인지는 잘 모르겠어서 필승으로 두고 했다. 왜냐하면 마지막 걸 가져갈 때 이기는 게임에서 (0 0 0)인 경우가 필패이니까 얘는 그 반대라서 반대로 생각함 ㅎㅎ..; 틀리면 그때 다시 생각해보자는 생각이었는데 맞길래 냅둠)

코인의 더미는 순서가 없다. 예를 들면 (3 4 5)와 (5 3 4)는 같은 승패 여부를 가진다.  
따라서 함수에서 값을 갱신해줄 때 [i][j][k], [i][k][j], [j][i][k], [j][k][i], [k][i][j], [k][j][i]는 다 한 번에 갱신되도록 해야 한다.  
그래야 중복 계산을 하지 않는다. 중복이 어떻게 생기는지는 아래의 그림을 보면 이해할 수 있다.

dp[i][j][k]가 coin의 상태가 (i j k)일 때 나의 승패라고 했는데 이를 어떻게 구할 수 있는지 생각해보자.  
내 차례일 때 내가 할 수 있는 행동은 코인이 남아있는 더미를 하나 골라서 거기서 코인을 1개 또는 2개 또는 3개를 가져오는 것이다.
내가 할 수 있는 행동은 내가 코인을 가져왔을 때 그 더미에 코인이 0개 이상 존재하는 모든 경우이다.
내가 코인을 가져온 후의 코인 상태가 내 자식이다.

***결론을 말하자면 내 자식 중 필패(L)가 하나라도 있으면 나는 필승(W)이고,  
내 자식 중 필패(L)가 하나도 없다면, 즉 내 자식이 전부 필승(W)이면 나는 필패(L)이다.***

이렇게 되는 이유는 다음과 같다. 위에서 내 자식은 내가 코인을 가져온 후의 코인 상태라고 했다.  
내가 코인을 가져가고 나면 코인의 상태는 내 자식의 상태가 될 수 있고 이때는 상대방 차례이다.  
상대방 차례일 때 모든 경우가 필승이라면 항상 상대방이 이긴다.  
따라서 내 자식이 전부 W라면 나는 L이다.  
내 자식 중에 필패가 하나라도 있다면 나는 상대방을 필패로 만드는 코인 상태를 고르면 필승할 수 있다.  
따라서 내 자식 중 하나라도 L이 있으면 나는 W이다.

게임의 시작 coin 상태가 (1 1 2)인 경우와 (0 4 1)인 경우에 dp 배열이 어떻게 생성되는지 그림으로 보자.  
- (1 1 2)
<img src="https://github.com/meanjoo/LinkPicture/blob/main/coin112.JPG"/>

- (0 4 1)
<img src="https://github.com/meanjoo/LinkPicture/blob/main/coin041.JPG"/>

** 뭔가 Misere nim을 쓸 수 있을 거 같은데 이 이론을 잘 모르겠어서 어떻게 하는지를 모르겠고 적용이 가능한지도 모르겠다.

### 11_Coin Move Game
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code)

Bottom-up 방식으로 짰다. memoization을 하기 위한 배열을 2차원 배열로 둔다.  
**j는 내가 받았을 때의 coin 위치이고, i는 상대방이 몇 칸을 이동해서 j로 온지를 나타낸다.  
dp[i][j]는 상대방이 i만큼 coin을 이동해서 j에 도착한 상태의 판을 내가 받은 것이고, 저장된 값은 내가 이 판을 받았을 때의 나의 승패여부이다.  
dp[i][j]의 값이 'W'이면 필승, 'L'이면 필패이다.**  
i가 있어야 하는 이유는 직전에 상대방이 이동한 거리로는 동전을 이동시킬 수 없기 때문이다.

우선 게임 시작 전 dp 배열의 값을 미리 채울 수 있는 곳들에 대해서 생각해보자.  
1. 내가 받은 판에 동전이 0번에 있으면 상대방이 얼마를 움직여서 나한테 넘기든 나는 필패이다.  
판을 받으면 동전을 무조건 1칸 이상 왼쪽으로 이동시켜야 하는데 0번에서 1칸 이상 왼쪽이면 음수 번째이고  
음수 번째에는 전부 x 표시가 되어있으므로 나는 무조건 x로 동전을 이동시키는 경우밖에 없다. 따라서 0번 열을 L로 채운다.  
2. 내가 받은 판에 동전이 음수 번째에 있으면 나는 필승이다.  
상대방이 음수 번째에 놓고 나한테 이 판이 넘어온 건데 이미 상대방이 음수 번째에 놓은 시점에서 상대방이 졌다.  
배열의 인덱스에는 음수가 허용되지 않으므로 만약 음수 번째에 놓은 판이 왔다면 바로 W라고 하면 된다.  
3. P의 배수에 x 표시가 되어 있다. 내가 받은 판이 P의 배수라면 나는 필승이다.  
이유는 동전이 음수 번째에 있을 때와 같다. 따라서 P의 배수번째 열을 W로 채운다.

1행에서 K행, 0열부터 S-1열 크기의 2차원 dp 배열에서 비어있는 곳의 값을 채우면 된다. dp 배열을 채우는 방법은 다음과 같다.  
(1.과 3.에서 0열과 P*n열은 이미 채웠으므로 얘네는 안 채워도 됨)  
**내가 이동함으로써 상대방을 필패(L)하게 만드는 경우가 하나 이상 존재하면 나는 필승(W)이다.  
상대방에게 필패하는 판을 넘겨주면 되기 때문이다.  
하지만 내가 이동하고 넘기는 판의 모든 경우가 상대방의 필승(W)이라면 나는 필패(L)이다.**

상대가 i만큼 coin을 옮겨서 j에 coin이 위치하는 판을 내가 받았을 때 내가 동전을 이동시킬 수 있는 거리는 i를 제외한 1~K의 값이다.  
for k ← 1 to K: i와 일치하는 k를 제외하고 dp[k][j-k]가 내가 이동하고 넘길 수 있는 모든 판이다.  
이 판들의 승패여부(넘긴 판) 중 하나 이상 L이 있으면 내 자리는 W이고, 아니면(=전부 W) L이다.

이러한 과정을 거쳐 dp 배열이 전부 구성되었다고 하자.  
우리가 봐야하는 값은 for k ← 1 to K: dp[k][S-k]이다.  
이게 뭐냐면 영희(항상 영희가 先)가 1부터 K까지 코인을 옮겨봤을 때 철수가 받을 수 있는 판의 승패여부이다.  
(영희가 항상 먼저 시작하니까 영희는 상대방이 이동한 거리가 없어 1~K까지 전부 옮겨볼 수 있다.)  
철수가 받은 판의 승패여부가 전부 W이면 영희는 필패이다. 철수가 받은 판 중에 하나라도 필패가 있으면 영희는 필승이다.

ex)  
* 6 3 15  
철수가 받은 판 중에 철수가 필패하는 경우가 있으므로 영희는 이길 수 있다.  
<img src="https://github.com/meanjoo/LinkPicture/blob/main/coinmove6315.jpg"/>  


* 7 4 5  
철수가 받은 판은 전부 철수가 필승이므로 영희는 이길 수 없다.  
<img src="https://github.com/meanjoo/LinkPicture/blob/main/coinmove745.jpg"/>  

+) 이 문제에서는 만약 L이 여러 개면 가장 큰 열 번호를 출력한다. i:1부터 K까지 돌다가 L이 나오면 바로 S-i를 출력하고 break

~~※ Top-down으로도 짜봤는데 왜 터지는지???~~ 6번 데이터에서 터져서 50점인 코드  
이 문제는 Top-down으로 짜면 안 된다.  
Top-down은 결국 재귀 호출로 짜게 돼있는데 Top-down dp 방식이라는 게 중복 계산만 없다뿐이지 함수를 호출하는 건 재귀와 다를 게 없다.  
즉 함수 호출을 많이 한다면 Top-down으로 짜는 건 좋은 선택이 아니다.  
이 문제에서 S가 커질수록 트리의 깊이가 평균적으로 매우매우매우 깊어진다. 그래서 아마 stack overflow로 터지는 거 같다.  
이걸로 깨달은 게 dp는 그냥 bottom-up으로 짜는 게 좋은 거 같다.  
```
//Top-down
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int P, K, S;
vector<char> dp[8];

char winlose(int x, int y) {
	if (y < 0)
		return 'W';
	if (dp[x][y] == 'L' || dp[x][y] == 'W')
		return dp[x][y];

	int cntL = 0;
	for (int i = 1; i <= K; i++) {
		if (i == x)
			continue;
		if (winlose(i, y - i) == 'L') {
			++cntL;
			break;
		}
	}

	char val = cntL > 0 ? 'W' : 'L';
	return dp[x][y] = val;
}

void solve() {
	cin >> P >> K >> S;
	for (int i = 1; i <= K; i++) {
		dp[i].clear();
		dp[i].resize(S, ' ');
		dp[i][0] = 'L';
	}
	for (int i = P; i < S; i += P) {
		for (int j = 1; j <= K; j++)
			dp[j][i] = 'W';
	}

	for (int i = 1; i <= K; i++)
		winlose(i, S - i);

	int gap = 0;
	for (int i = 1; i <= K; i++) {
		if (S - i >= 0 && dp[i][S - i] == 'L') {
			gap = i;
			break;
		}
	}

	gap == 0 ? cout << "-1" << endl : cout << S - gap << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("coinmove.inp", "r", stdin);
	freopen("coinmove.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}
```

### 12_정육면체 자르기
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code)



### 13_카드 선택
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code)

dp 배열의 크기를 최대 크기인 3 × 1000으로 잡아준다. 열의 max가 1000인 이유는 카드의 최대 장수가 1000이기 때문이다.  
0행은 i번째 카드를 선택하고 i-2번째 카드를 선택한 경우의 최대 합,  
1행은 i번째 카드를 선택하고 i-3번째 카드를 선택한 경우의 최대 합,  
2행은 i번째 카드를 선택하고 i-4번째 카드를 선택한 경우의 최대 합이다.  
i번째 카드를 선택하기 위해서는 i-2번째, i-3번째, i-4번째 중 정확히 단 하나가 선택되어야 한다.

1번째, 2번째, 3번째 중에서는 하나가 선택되어야 한다.  
1번째 카드를 선택했을 때의 최대 합은 1번째 카드에 적힌 숫자,  
2번째 카드를 선택했을 때의 최대 합은 2번째 카드에 적힌 숫자,  
3번째 카드를 선택했을 때의 최대 합은 3번째 카드에 적힌 숫자이다.  
즉 0, 1, 2열은 각각의 카드에 적힌 수로 채우면 된다.

j=0,1,2일 때는 위에서 채웠고,  
j>=3에 대해서 dp[i][j]를 어떤 값으로 채워야하는지 생각해보자.


### 14_격자경로(또 다른)
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code)

문제 자체는 이미 강의에서 교수님이 다루신 내용이라 어렵지 않았는데  
나의 제멋대로 해석하고 이해하기 때문에 몇 번을 의미없는 제출을 했는지 모르겠다.  
한글 파일에 친절히 경로 수의 마지막 5자리의 값이 0인 경우, 실제로는 경로가 존재하더라도 경로가 존재하지 않는 것처럼 처리한다고 굵은 글씨로 강조돼있었다.  
그런데 나는 '아 값이 0이어도 경로가 있으니까 출력을 하자. 이걸 판단하려면 최소 비용이 MAX가 아니면 일단 왔다는 거니까 이때 출력을 하자.'고 생각했다. ~~노답~~  
이렇게 하면 ESPA에서 70점이 나온다. 아마 채점 데이터 중에 마지막 다섯 자리가 0인 경로가 있는 게 있는 것 같다.  
나는 이걸 출력을 한 거고, 문제에서는 출력을 하지 말라고 했기 때문에 30점이 비는 것 같다. (채점 데이터가 공개되면 확인해보자. 4 5 10 아니면 3 4 10이 0점이었음)  
이걸 꽤나 뒤늦게 깨달아서 다른 엄한 데만 계속 고치고 있었다. 문제를 잘 해석합시다....

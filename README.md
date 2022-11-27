# Algorithm_Assignment_Code
2022-2학기 알고리즘 과제

== 구현 ==

- [x] 01. Test ([test.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/test.cpp))

- [x] 02. Spin & Slide ([spinslide.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/spinslide.cpp))

- [x] 03. 계단 오르기 ([stairs.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/stairs.cpp))

- [x] 04. Interesting Gain ([gain.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/gain.cpp))

- [x] 05. 달팽이 ([snail.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/snail.cpp))

- [x] 06. 격자 색칠 ([grid.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/grid.cpp))

- [x] 23. Block Compaction ([block.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/block.cpp))

== Divide & Conquer ==

- [x] 07. 순열을 이진트리로 ([permutation.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/permutation.cpp))

- [x] 08. Bitmap ([bitmap.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/bitmap.cpp)) - [같은 문제](https://www.acmicpc.net/problem/6397)

== Dynamic Programming ==

- [x] 09. 격자 경로 ([gridpath.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/gridpath.cpp))

- [x] 10. Coin Game ([coin.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/coin.cpp))

- [x] 11. Coin Move Game ([coinmove.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/coinmove.cpp))

- [x] 12. 정육면체 자르기 ([cube.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/cube.cpp)) - [같은 문제](https://www.acmicpc.net/problem/9029)

- [x] 13. 카드 선택 ([card.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/card13.cpp))

- [x] 14. 격자경로(또 다른) ([path.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/path.cpp))

- [x] 15. Card Game ([card.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/card.cpp)) - [같은 문제](https://www.acmicpc.net/problem/11062)

- [x] 16. Adding Ways ([addingways.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/addingways.cpp))

- [x] 17. Color Length ([color.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/color.cpp)) - [같은 문제](https://www.acmicpc.net/problem/8902)

- [x] 18. Recycling Bins ([bin.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/bin.cpp))

- [x] 20. Driving License ([drive.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/drive.cpp))

== Greedy ==

- [x] 19. MST ([mst.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/mst.cpp))

- [x] 21. 물탱크 ([water.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/water.cpp))

- [x] 24. 비밀접선 ([contact.cpp](https://github.com/meanjoo/Algorithm_Assignment_Code/blob/master/Algorithm/contact.cpp))

== ? ==

- [ ] 22. Freelancer

<hr>

# 05_달팽이
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

# 06_격자 색칠
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

# 09_격자 경로
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

# 10_Coin Game
[목차로 이동](https://github.com/meanjoo/Algorithm_Assignment_Code#algorithm_assignment_code)

Top-down 방식으로 짰다. memoization하기 위한 배열을 3차원 배열로 둔다. 코인은 항상 3더미이기 때문이다.  
**dp[i][j][k]는 내 차례때 코인이 (i j k)라면 그때의 승패여부이다.**  
각 코인 더미의 최대 코인 개수는 100개이므로 101 * 101 * 101 배열을 만들어주면 된다.  
메모리를 조금이라도 줄이려고 dp 배열을 int가 아닌 char로 선언했다. 게다가 승패만 알면 돼서 값도 int까지 필요없다.

**dp[i][j][k]의 값이 'W'이면 필승, 'L'이면 필패이다.  
base는 (0 0 0)='W', (0 0 1) = 'L', (0 1 0) = 'L', (1 0 0) = 'L', (1 1 0) = 'W', (1 0 1) = 'W', (0 1 1)='W', (1 1 1)='L'이다.**  
(사실 처음에는 base에 (0 0 0)이 있어야겠다는 생각을 하지 않았는데 재귀로 부르다 보면 (0 0 0)을 call하는 경우가 생기길래 초기값을 줬다. (0 0 0)인 경우가 필승인지 필패인지는 잘 모르겠어서 필승으로 두고 했다. 왜냐하면 마지막 걸 가져갈 때 이기는 게임에서 (0 0 0)인 경우가 필패이니까 얘는 그 반대라서 반대로 생각 ㅎㅎ..; 틀리면 그때 다시 생각해보자는 생각이었는데 맞길래 냅둠)

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
→ 가능

# 11_Coin Move Game
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

# 12_정육면체 자르기


# 13_카드 선택
dp 배열의 크기를 최대 크기인 3 × 1000으로 잡아준다.  
열의 max가 1000인 이유는 카드의 최대 장수가 1000이기 때문이다.  
0행은 i번째 카드를 선택하고 i-2번째 카드를 선택한 경우의 최대 합,  
1행은 i번째 카드를 선택하고 i-3번째 카드를 선택한 경우의 최대 합,  
2행은 i번째 카드를 선택하고 i-4번째 카드를 선택한 경우의 최대 합이다.  
i번째 카드를 선택하기 위해서는 i-2번째, i-3번째, i-4번째 중 정확히 단 하나가 선택되어야 한다.

1번째, 2번째, 3번째 중에서는 하나가 선택되어야 한다.  
1번째 카드를 선택했을 때의 최대 합은 1번째 카드에 적힌 숫자,  
2번째 카드를 선택했을 때의 최대 합은 2번째 카드에 적힌 숫자,  
3번째 카드를 선택했을 때의 최대 합은 3번째 카드에 적힌 숫자이다.  
즉 dp의 0, 1, 2열은 각각의 카드에 적힌 수로 채우면 된다.

j=0,1,2일 때는 위에서 채웠고,  
i=0,1,2, j>=3에 대해서 dp[i][j]를 어떤 값으로 채워야하는지 생각해보자.  
j번째 카드를 선택하기 위해서는 j-2번째, j-3번째, j-4번째 중 하나만 반드시 선택되어야 한다.

dp[0][j]는 j번째 카드를 선택하고 j-2번째 카드를 선택했을 때의 최대 합이다.  
조건에 의해 j번째 카드를 선택하고 j-2번째 카드를 선택했다면 j-4번째 카드는 선택될 수 없기 때문에,  
j-2(=k)번째 카드의 입장에서 dp[0][k-2]는 선택될 수 없다.  
즉 `dp[0][j] = card[j] + max(dp[1][j-2], dp[2][j-2])` 이다.  
하나 예외 사항이 있는데, 5번째 카드를 선택하는 경우이다. (카드는 0번째부터 있다고 생각할 것)  
dp[0][5]는 5번째 카드를 선택하고 3번째 카드를 선택한 경우이다. 위의 식에 따르면 dp[0][5]는 dp[1][3]과 dp[2][3]을 확인할 것이다.  
여기서 dp[2][3]이 문제가 된다. 밑의 설명에서 알 수 있겠지만 dp[2][3]은 (0번째, 3번째)를 선택하는 경우와 (1번째, 3번째)를 선택하는 경우 중 더 큰 값을 가지는 쪽의 값을 가지고 있다.  
만약 dp[2][3]이 (1번째, 3번째)를 선택하는 경우의 값을 가지고 있고, dp[2][3] > dp[1][3]이라면  
dp[0][5]는 5번째 카드를 선택하고 3번째 카드를 선택하고 1번째 카드를 선택하는 것이 되기 때문에 5번째 카드 입장에서 5-2번째와 5-4번째 카드를 선택하는 것이 되어버려 조건을 위배한다.  
따라서 5번째 카드를 선택하고 3번째 카드를 선택했다면 3번째 카드 입장에서는 무조건 0번째 카드를 선택해야 하므로  
`dp[0][5] = card[j] + dp[1][j-2]`이다.

dp[1][j]는 j번째 카드를 선택하고 j-3번째 카드를 선택했을 때의 최대 합이다.  
j-3(=k)번째 카드를 선택하는 경우에는 k-2, k-3, k-4번째 중 무엇을 선택해도 j번째 입장에서는 j-5, j-6, j-7번째이므로 문제의 조건을 위배하지 않는다.  
따라서 dp[1][j]일 때의 식은 아래와 같다.  
`dp[1][j] = card[j] + max(dp[0][j-3], dp[1][j-3], dp[2][j-3])`

dp[2][j]는 j번째 카드를 선택하고 j-4번째 카드를 선택했을 때의 최대 합이다.  
j-4(=k)번째 카드를 선택하는 경우에도 k-2, k-3, k-4번째 중 무엇을 선택해도 j번째 입장에서는 j-6, j-7, j-8번째이므로 문제의 조건을 위배하지 않는다.  
따라서 dp[2][j]일 때의 식은 아래와 같다.  
`dp[2][j] = card[j] + max(dp[0][j-4], dp[1][j-4], dp[2][j-4])`  
단, j==3일 때는 j-4번째 인덱스가 없기 때문에 (j번째, j-2번째)를 선택하는 경우와 (j번째, j-3번째)를 선택하는 경우 중 더 큰 값을 가지는 쪽을 선택하면 된다.  
이 값은 각각 dp[0][j]와 dp[1][j]에 대응되므로 `dp[2][3] = max(dp[0][3], dp[1][3])`이다. 

위 내용들을 정리하면 아래와 같은 식이 나온다.

<img src="https://github.com/meanjoo/LinkPicture/blob/main/formal13.jpg" width="800" height=auto/>

마지막 카드는 반드시 선택해야하므로 max(dp[0][n-1], dp[1][n-1], dp[2][n-1])이 정답이다.

- 카드가 (-3 -2 4 7 -5 -6 8 9 8 9 5)일 때 완성된 dp 배열  
<img src="https://github.com/meanjoo/LinkPicture/blob/main/13ex1.jpg" width="800" height=auto/>

- 카드가 (24 15 -56 -4 100 7)일 때 완성된 dp 배열  
<img src="https://github.com/meanjoo/LinkPicture/blob/main/13ex2.jpg" width="500" height=auto/>


# 14_격자경로(또 다른)
문제 자체는 이미 강의에서 교수님이 다루신 내용이라 어렵지 않았는데  
문제를 제대로 꼼꼼히 안 읽은 것 때문에 몇 번을 의미없는 제출을 했는지 모르겠다.  
한글 파일에 친절히 경로 수의 마지막 5자리의 값이 0인 경우, 실제로는 경로가 존재하더라도 경로가 존재하지 않는 것처럼 처리한다고 굵은 글씨로 강조돼있었다.  
그런데 나는 '아 값이 0이어도 경로가 있으니까 출력을 하자. 이걸 판단하려면 최소 비용이 MAX가 아니면 일단 왔다는 거니까 이때 출력을 하자.'고 생각했었다.  
이렇게 하면 ESPA에서 70점이 나온다. 아마 채점 데이터 중에 마지막 다섯 자리가 0인 경로가 있는 게 있는 것 같다.  
나는 이걸 출력을 한 거고, 문제에서는 출력을 하지 말라고 했기 때문에 30점이 비는 것 같다. (4 5 10 아니면 3 4 10이 0점이었다)  
이걸 꽤나 뒤늦게 깨달아서 다른 데만 계속 고치고 있었다..

경로 추적시 내가 표시된 곳이면 내가 몇 개의 표시된 곳(k)을 거쳐서 왔는지를 기억한 후 일단 내가 어디서부터 왔는지, 즉 부모로 이동한 후에 그 부모에서 k-1개의 표시된 곳을 거쳐서 도착한 데에서 경로를 다시 추적하면 된다. 경로를 역추적하는 것이기 때문에 내가 표시된 곳이면 부모로 갔을 때 표시된 곳이 하나 줄어든다.

다 끝나고 다시 보는데 뭔가 94번째 줄이 잘못된 것 같다? 마지막 칸은 k번 이상인 건데 이게 최솟값이 무조건 내 앞에거가 아니라 min(나, 내 앞)이어야 할 거 같은데 그래서 path도 이에 맞게 조정해야 하는 거 같다. 만약 k번 이상 지나가는 최소 구하는 거였으면 잘못된 답이 나올 거 같다.  

+ 추가) 교수님이 이 문제는 어딘가 잘못된 문제라고 하셨다. 코드 방식대로 풀면 espa에서는 100점이 나오는데 어떤 입력에 대해서 원하는 결과와 다른 결과를 내는 입력이 있다고 하셨다. 그치만 나는 뭐가 문젠지 모르겠다. ㅎ


# 15. Card Game
dp[i][j]가 의미하는 것은 카드가 [i, j]개에서 내가 선일 때 얻을 수 있는 점수의 최댓값이다.  
카드가 {1 2 5 2}가 있을 때 dp[1][3]은 {1 2 5}에서 내가 선일 때 얻을 수 있는 점수의 최댓값,  
dp[2][4]는 {2 5 2}에서 내가 선일 때 얻을 수 있는 점수의 최댓값이다.

그렇다면 [1][1], [2][2], ... , [n][n]인 경우는 카드가 1개 있을 때이므로 그냥 그 카드가 내가 선일 때 얻을 수 있는 점수의 최댓값이다.  
[1][2], [2][3], ... [n-1][n]인 경우는 카드가 2개 있을 때이다.  
왼쪽 카드와 오른쪽 카드 중에 더 큰 카드를 고르는 것이 내가 선일 때 얻을 수 있는 점수의 최댓값이다.

카드가 3개 이상일 때를 일반화해보자.  
카드는 맨 앞 아니면 맨 끝에서 가져오는 두 경우로 나눠볼 수 있다.  
맨 앞 카드의 인덱스를 left, 맨 끝 카드의 인덱스를 right라고 하자.  
만약 카드를 맨 앞에서 가져왔다면 맨 앞 카드의 값(=card[left]) + 맨 앞 카드를 빼고 나머지 구간 [left+1, right]에서 내가 얻을 수 있는 점수의 최댓값을 구하면 된다.  
우리는 dp 배열을 통해서 카드 개수가 현재보다 작을 때 자기가 선일 때 얻을 수 있는 점수의 최댓값을 알 수 있다.  
내가 맨 앞 카드를 가져왔기 때문에 [left+1, right]에서 얻을 수 있는 점수의 최댓값인 dp[left+1][right]는 상대방이 얻을 수 있는 점수의 최댓값이다.  
어떤 구간 [a, b]에서의 내 점수의 합과 상대방 점수의 합은 [a, b]에 있는 카드의 전체 합과 같다.  
따라서 [left+1, right]에서 내가 얻을 수 있는 점수의 최댓값은 [left+1, right]에 있는 카드의 합 - dp[left+1][right]이다.  
구간 합은 누적 합을 통해서 O(1) 시간에 구할 수 있다.  
즉 [left, right]에서 card[left]를 가져왔을 때 내가 얻을 수 있는 점수의 최댓값은 card[left] + ps[right] - ps[left] - dp[left+1][right]이다.  
같은 논리로 카드를 맨 끝에서 가져왔다면 내가 얻을 수 있는 점수의 최댓값은 card[right] + ps[right-1] - ps[left-1] - dp[left][right-1]이다.  
이 둘 중 더 큰 값이 [left, right]에서 내가 선일 때 얻을 수 있는 점수의 최댓값이다.

dp 배열은 ↘ 대각선 순서로 채워주면 된다.

<img src="https://github.com/meanjoo/LinkPicture/blob/main/15relation.jpg" />


ex. {1 2 5 2}  
초록색은 dp 값이고, 괄호 안의 값은 구간 합이다.

<img src="https://github.com/meanjoo/LinkPicture/blob/main/15card.jpg" />



# 16. Adding Ways
자연수의 분할 문제다.  
① P(n, 1) = P(n, n) = 1  
② P(n, k) = P(n-k, 1) + P(n-k, 2) + P(n-k, 3) + ... + P(n-k, k)  
③ P(n, k) = P(n-1, k-1) + P(n-k, k)

②: n을 k개의 자연수로 분할하는 것이기 때문에 항의 최솟값은 1이다.  
k개한테 전부 1을 나눠주면 n-k가 남는다.  
남은 n-k개는 1개로 나누어져도 되고, 2개로 나누어져도 되고, k개로 나누어져도 된다.

③: 1을 포함하는 항이 적어도 1개는 존재하는 경우 → P(n-1, k-1)  
1을 항 하나에 주고 나서 나머지 n-1을 k-1개로 분할하면 적어도 한 항은 1이다.  
모든 항이 2 이상인 경우(1이 하나도 없음) → P(n-k, k)  
n-k를 다 k개한테 나눠주고 나서 n-k를 k개로 나누는 P(n-k, k) 또한 자연수의 분할이기 때문에 P(n, k)의 최소 항은 2이다.

②와 ③은 식의 형태만 다르지 값은 (당연하게도) 같다.  
반복을 돌아야하는 ②와 달리 ③은 이전에 계산했던 결과만 보면 되기 때문에 ③이 더 빠르게 처리할 수 있다.  
①과 ③을 이용해서 bottom-up 방식으로 문제를 해결했다.


# 17. Color Length
생각하는 데 진짜진짜진짜 오래 걸렸다.  
1번부터 17번 중에 가장 오래 생각한 것 같다. 그래서 당연히 삽질도 많이 했다.

설명은 코드에 있는 주석을 참고하고,  
코드에 쓰인 변수가 뭔지에 대해서만 간단하게 써두자.

- string  
car1: 입력되는 두 문자열 중 첫 번째 문자열  
car2: 입력되는 두 문자열 중 두 번째 문자열  
- int  
dp[5001][5001]: car1의 i번째, car2의 j번째까지 봤을 때 결과값  
ps1[5001][26]: car1의 i번째(base: 1)까지 봤을 때 거기 존재하는 대문자 알파벳의 개수 - 누적합  
ps2[5001][26]: car2의 i번째(base: 1)까지 봤을 때 거기 존재하는 대문자 알파벳의 개수 - 누적합  
cnt[26]: car1과 car2를 통틀어서 존재하는 대문자 알파벳의 개수  
len1: 맨 앞 공백까지 추가 후 car1의 길이  
len2: 맨 앞 공백까지 추가 후 car2의 길이  

car1과 car2를 입력받고 맨 앞에 공백을 하나 넣어준 이유는  
아래 그림을 보면 알겠지만 dp 배열을 0번부터 사용하지만 실제 문자가 나타나는 곳은 1번부터이다.  
여기서 연산을 좀 편하게 하기 위해서 맨 앞에 공백을 넣어줬다.

아래는 문제에 있는 예제 입력 중 두 문자열이 GBBY, YRRGB일 때 완성된 dp 배열의 모습이다.  
<img src="https://github.com/meanjoo/LinkPicture/blob/main/ex17.jpg" />


# 18. Recycling Bins
m개의 수집통을 설치했을 때 가장 가까운 거리를 구하려면 m-1개의 수집통을 설치했을 때의 최소 거리 합을 알아야 한다.  
어디선가 문제를 풀어볼 때 합 최소화를 본 적이 있다. bin이 1개일 때는 이를 이용할 수 있다.  
* 합 최소화란?  
n개의 수가 있을 때 |a1-x|+|a2-x|+...+|an-x|를 최소화하는 x를 구하는 문제가 있다고 하자.  
이때 x의 최적해는 주어진 수들의 중앙값이 된다는 사실이다. 주어진 수들을 정렬한 후에 가운데 원소를 구하면 된다.  
만약 n이 짝수여서 중앙값이 2개라면, 두 개의 중앙값과 그 사이의 모든 값이 최적해이다.  

bin이 1개면 합 최소화에서의 x 값이 bin의 위치이다.  
m>1에 대해서는 최소 행렬 곱셈 방식과 비슷한 아이디어로 생각했다. (k값 쓰는 면에서)  
다시 생각해보니까 중앙값이 2개일 때 굳이 걔네 둘의 평균으로 안 하고 둘 중 아무거나 골라도 되는 게 어차피 그 사이의 모든 값이 최적해이다.

bin이 m개일 때의 최솟값은 모든 집에 대해서 bin을 1개 설치했을 때의 최솟값과 bin을 m-1개를 설치했을 때의 최솟값을 통해 구할 수 있다.  

dp[i][j][k]가 의미하는 것은 i번째 집부터 j번째 집 사이에 k개의 bin을 설치했을 때의 최소 거리 값이다.

<img src="https://github.com/meanjoo/LinkPicture/blob/main/18_1.jpg"/>

만약 k를 m까지 만들면 dp[0][n-1][m]이 바로 답일 텐데, m까지 안 만들고 m-1까지만 만들어서 반복을 한 번 더 돌렸다.  
왜 이렇게 짰는가에 대해서는 딱히 이유는 없고 그때 그렇게 짜고 싶었나보다.

근데 아무리 생각해도 4중 반복문은 좀 아닌 거 같은데 어디서 뭘 줄여야 할지 모르겠다.

+) 문득 든 생각인데 내 코드를 보면  
for(int k=i; k<j; k++) {  
  dp[i][j][cnt] = min(dp[i][j][cnt], dp[i][k][1]+dp[k+1][j][cnt-1])  
}  
이렇게만 갱신하도록 되어 있는데 for문 안에서 dp[i][j][cnt] = min(dp[i][j][cnt], dp[i][k][cnt-1]+dp[k+1][j][1])도 해줘야 하는 거 아닌가..?  
앞 쪽에서부터만 한 개씩 설치하게 해봤는데 뒤에서부터 하는 건 안 해도 되는 건감


# 19. MST
그냥 크루스칼 알고리즘이랑 프림 알고리즘 구현하면 되는 문제이다.  
간선 정보 저장할 때 처음 입력 순서, 즉 간선의 번호를 간선의 추가적인 정보로 넣어준다.  
최소 가중치가 여러 개면 간선의 번호가 먼저인 것을 선택하도록 하기 위함이다.  
출력하는 정보는 MST의 비용과 간선이 추가되는 순서대로 간선의 번호이다.  
크루스칼은 union-find(weighted union find를 사용했다.), 프림은 priority_queue로 구현하면 된다.

MST 만들 때 거의 100% 크루스칼로 짜서 프림으로 구현하는 게 좀 헷갈렸다. dijkstra랑 논리가 비슷하다고 생각하면 좀 편할 거 같다.  
채점 말고 예제 테케 넣었을 때 프림의 값이 이상하게 나왔었는데 그 이유가 무방향 그래픈데 한 방향만 간선을 추가해줬었기 때문이다.  
MST가 연결된 비방향성 그래프에서 만들어질 수 있는 건데 크루스칼에서 인접 그래프를 안 쓰니까 처음에 프림에서 뭐가 잘못된지 몰랐었다.


# 20. Driving License
dp - 회전을 얼마나 하는지를 관리하는 정보가 필요하다.


# 23. Block Compaction
블록을 아래로 밀 때와 왼쪽으로 밀 때 그 블록이 어디까지 밀릴 수 있는지를 알아야한다.  
블록을 아래로 밀 때는 블록의 가로 길이(너비)에 해당하는 최댓값까지 밀 수 있고, 왼쪽으로 밀 때는 블록의 세로 길이(높이)에 해당하는 최댓값까지 밀 수 있다.  
아래로 밀 때는 아래에 있는 것부터 밀어야 하므로 왼쪽 아래 꼭짓점의 y좌표를 기준으로 오름차순 정렬을 한다.  
왼쪽으로 밀 때는 왼쪽에 있는 것부터 밀어야 하므로 왼쪽 아래 꼭짓점의 x좌표를 기준으로 오름차순 정렬을 한다.  
아래로 밀 때는 블록의 너비([llx, urx])에 해당하는 최댓값을, 왼쪽으로 밀 때는 블록의 높이([lly, ury])에 해당하는 최댓값을 찾아야한다.  
구간의 최댓값을 알아야하기 때문에 세그먼트 트리로 접근했다.  
그런데 값의 업데이트도 구간이라 기본 세그먼트 트리를 사용하니까 시간 초과가 났다.  
그래서 lazy propagation을 적용한 세그먼트 트리를 써서 해결했다.  
구간 값 가져오기, 값 업데이트 - 세그먼트 트리  
구간 값 가져오기, 구간 업데이트 - 세그먼트 트리 with lazy propagation

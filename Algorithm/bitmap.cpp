#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

char ch;
int n, m, strIdx;
string str, ans;
char bitmap[200][200];

void BtoD(int sx, int sy, int ex, int ey) {
	int cnt0 = 0, cnt1 = 0;
	for (int i = sx; i <= ex; i++) {
		for (int j = sy; j <= ey; j++) {
			bitmap[i][j] == '0' ? ++cnt0 : ++cnt1;
		}
	}

	int sz = (ex - sx + 1) * (ey - sy + 1); // (sx, sy) ~ (ex, ey)의 크기
	if (cnt0 == sz)
		ans.push_back('0');
	else if (cnt1 == sz)
		ans.push_back('1');
	else {
		ans.push_back('D');
		int row = (ex - sx + 1) / 2, col = (ey - sy + 1) / 2;
		if (row == 0) { // 행이 1개인 경우; 열만 쪼개면 됨. 이때 열은 항상 2 이상 (행 1개, 열 1개는 1*1인데 얘는 if 아니면 else if에서 무조건 처리됨). 그리고 위쪽 우선
			bool colOdd = (ey - sy + 1) % 2 != 0;
			BtoD(sx, sy, ex, ey - col);
			colOdd ? BtoD(sx, sy + col + 1, ex, ey) : BtoD(sx, sy + col, ex, ey);
		}
		else if (col == 0) { // 열이 1개인 경우. 왼쪽 우선
			bool rowOdd = (ex - sx + 1) % 2 != 0;
			BtoD(sx, sy, ex - row, ey);
			rowOdd ? BtoD(sx + row + 1, sy, ex, ey) : BtoD(sx + row, sy, ex, ey);
		}
		else { // 4분할 - 행과 열이 전부 2 이상일 때
			bool colOdd = (ey - sy + 1) % 2 != 0;
			bool rowOdd = (ex - sx + 1) % 2 != 0;
			if (!rowOdd && !colOdd) { // 행과 열 둘 다 짝수
				BtoD(sx, sy, ex - row, ey - col);
				BtoD(sx, sy + col, ex - row, ey);
				BtoD(sx + row, sy, ex, ey - col);
				BtoD(sx + row, sy + col, ex, ey);
			}
			else if (rowOdd && !colOdd) { // 행만 홀수
				BtoD(sx, sy, ex - row, ey - col);
				BtoD(sx, sy + col, ex - row, ey);
				BtoD(sx + row + 1, sy, ex, ey - col);
				BtoD(sx + row + 1, sy + col, ex, ey);
			}
			else if (!rowOdd && colOdd) { // 열만 홀수
				BtoD(sx, sy, ex - row, ey - col);
				BtoD(sx, sy + col + 1, ex - row, ey);
				BtoD(sx + row, sy, ex, ey - col);
				BtoD(sx + row, sy + col + 1, ex, ey);
			}
			else { // 행과 열 둘 다 홀수
				BtoD(sx, sy, ex - row, ey - col);
				BtoD(sx, sy + col + 1, ex - row, ey);
				BtoD(sx + row + 1, sy, ex, ey - col);
				BtoD(sx + row + 1, sy + col + 1, ex, ey);
			}
		}
	}
}

void DtoB(int sx, int sy, int ex, int ey) {
	if (str[strIdx++] == 'D') { // 분할하기
		int row = (ex - sx + 1) / 2, col = (ey - sy + 1) / 2;
		if (row == 0) { // 행이 1개인 경우; 열만 쪼개면 됨. 이때 열은 항상 2 이상 (행 1개, 열 1개는 1*1인데 얘는 if 아니면 else if에서 무조건 처리됨)
			bool colOdd = (ey - sy + 1) % 2 != 0;
			DtoB(sx, sy, ex, ey - col);
			colOdd ? DtoB(sx, sy + col + 1, ex, ey) : DtoB(sx, sy + col, ex, ey);
		}
		else if (col == 0) { // 열이 1개인 경우
			bool rowOdd = (ex - sx + 1) % 2 != 0;
			DtoB(sx, sy, ex - row, ey);
			rowOdd ? DtoB(sx + row + 1, sy, ex, ey) : DtoB(sx + row, sy, ex, ey);
		}
		else { // 4분할 - 행과 열이 전부 2 이상일 때
			bool colOdd = (ey - sy + 1) % 2 != 0;
			bool rowOdd = (ex - sx + 1) % 2 != 0;
			if (!rowOdd && !colOdd) { // 행과 열 둘 다 짝수
				DtoB(sx, sy, ex - row, ey - col);
				DtoB(sx, sy + col, ex - row, ey);
				DtoB(sx + row, sy, ex, ey - col);
				DtoB(sx + row, sy + col, ex, ey);
			}
			else if (rowOdd && !colOdd) { // 행만 홀수
				DtoB(sx, sy, ex - row, ey - col);
				DtoB(sx, sy + col, ex - row, ey);
				DtoB(sx + row + 1, sy, ex, ey - col);
				DtoB(sx + row + 1, sy + col, ex, ey);
			}
			else if (!rowOdd && colOdd) { // 열만 홀수
				DtoB(sx, sy, ex - row, ey - col);
				DtoB(sx, sy + col + 1, ex - row, ey);
				DtoB(sx + row, sy, ex, ey - col);
				DtoB(sx + row, sy + col + 1, ex, ey);
			}
			else { // 행과 열 둘 다 홀수
				DtoB(sx, sy, ex - row, ey - col);
				DtoB(sx, sy + col + 1, ex - row, ey);
				DtoB(sx + row + 1, sy, ex, ey - col);
				DtoB(sx + row + 1, sy + col + 1, ex, ey);
			}
		}
	}
	else {
		for (int i = sx; i <= ex; i++) {
			for (int j = sy; j <= ey; j++)
				bitmap[i][j] = str[strIdx - 1];
		}
	}
}

void printBtoD() {
	int cnt = 0;
	for (auto& c : ans) {
		cout << c;
		++cnt;
		if (cnt == 50) {
			cout << endl;
			cnt = 0;
		}
	}
	if (cnt != 0)
		cout << endl;
}

void printDtoB() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << bitmap[i][j];
			++cnt;
			if (cnt == 50) {
				cout << endl;
				cnt = 0;
			}
		}
	}
	if (cnt != 0)
		cout << endl;
}

void solve() {
	ans = "";

	if (ch == 'B') {
		int idx = 0;
		// make bitmap
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				bitmap[i][j] = str[idx++];
		}
		cout << 'D' << setw(4) << n << setw(4) << m << endl;
		BtoD(0, 0, n - 1, m - 1);
		printBtoD();
	}
	else {
		strIdx = 0;
		cout << 'B' << setw(4) << n << setw(4) << m << endl;
		DtoB(0, 0, n - 1, m - 1);
		printDtoB();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("bitmap.inp", "r", stdin);
	freopen("bitmap.out", "w", stdout);


	str = "";
	while (true) {
		string line;
		getline(cin, line);
		if (!line.compare("#")) {
			if (str.compare(""))
				solve();
			break;
		}

		int space = line.find(' ');
		if (space == string::npos) {
			str += line;
		}
		else {
			if (str.compare("")) {
				solve();
				str = "";
			}

			ch = line[0];
			string tmp = "";
			bool chk = false;
			for (int i = 2; i < line.length(); i++) {
				if (line[i] != ' ')
					tmp.push_back(line[i]);
				else {
					if (!chk && tmp.compare("")) {
						tmp.push_back(' ');
						chk = true;
					}
				}
			}
			space = tmp.find(' ');
			n = stoi(tmp.substr(0, space));
			m = stoi(tmp.substr((int)space + 1));
		}
	}
	return 0;
}
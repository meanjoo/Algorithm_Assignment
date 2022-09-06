#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

typedef struct person {
	string no, firstName, lastName;
}Person;

int N, maxFirst;
vector<Person> arr;
map<string, int> lastname;

bool comp(const Person& p1, const Person& p2) {
	return p1.no < p2.no;
}

void printBlank(int len) {
	for (int i = 0; i < maxFirst - len; i++)
		cout << ' ';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("test.inp", "r", stdin);
	freopen("test.out", "w", stdout);

	cin >> N;
	arr.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i].no >> arr[i].firstName >> arr[i].lastName;
		lastname[arr[i].lastName]++;
		maxFirst = (int)arr[i].firstName.length() > maxFirst ? (int)arr[i].firstName.length() : maxFirst;
	}
	sort(arr.begin(), arr.end(), comp);

	for (auto& a : arr) {
		cout << a.no << ' ' << a.firstName;
		printBlank((int)a.firstName.length());
		cout << ' ' << a.lastName << endl;
	}
	cout << endl;

	for (auto& ln : lastname) {
		if (ln.second > 1)
			cout << ln.first << ' ' << ln.second << endl;
	}

	return 0;
}
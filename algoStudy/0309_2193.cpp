#include <iostream>
#include <vector>

using namespace std;

int N;
int cnt = 0;
vector <int> num;

void solve(int index) {
	/*if (index == N) {
		return;
	}
	if (num[index - 1] == -1) return;
	num[index] = -1;
	cnt++;
	solve(index + 1);

	num[index] = 0;
	solve(index + 1);
	if (num[index - 1] != 1) {
		num[index] = 1;
		solve(index + 1);
	}
	*/
	//�Ǻ���ġ ����!! long long���� Ǯ��� ���� ����.
}
int main() {
	cin >> N;

	num.assign(N, 0);
	num[0] = 1;
	cnt++;
	if (N == 1) cout << cnt;
	
	else {
		solve(1);
		cout << cnt;
	}
}
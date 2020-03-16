#include <iostream>
#include <vector>

using namespace std;

int N;
int blk = 0;
int sum = 1;
vector <int> dp;
void solve() {
	for (int i = 2; i <= blk; i++) {
		dp[i] = dp[i - 1] * dp[1] + 2 * (sum);
		sum += dp[i - 1];
	}
}
int main() {
	cin >> N;
	if (N % 2 == 1) {
		cout << 0;
		return 0;
	}
	blk = N / 2;
	dp.assign(blk+1, 0);
	dp[1] = 3;
	solve();
	cout << dp[blk];

	return 0;
}
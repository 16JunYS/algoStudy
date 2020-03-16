#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N;

int main() {
	cin >> N;

	vector <int> v(N);
	vector <int> dp(N);
	for (int i = 0; i < N; i++) {
		cin >> v[i];
	}
	dp[0] = v[0];
	dp[1] = dp[0] + v[1];
	dp[2] = max(dp[0] + v[2], v[1] + v[2]);
	for (int i = 3; i < N; i++) {
		dp[i] = max(dp[i - 2] + v[i], dp[i - 3] + v[i - 1] + v[i]);
	}
	cout << dp[N - 1];
}
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;
int N, M;
int mi[100] = { 0, };
int ci[100] = { 0, };
int dp[10000];

int main() {
	cin >> N;
	cin >> M;

	for (int i = 0; i < N; i++)
		cin >> mi[i];
	for (int i = 0; i < N; i++)
		cin >> ci[i];
	memset(dp, -1, sizeof(int)*10000);
	dp[0] = 0;

	for (int i = 0; i < N; i++) {
		int cost = ci[i];
		dp[cost] = max(dp[cost], mi[i]);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			int cost = ci[i] + ci[j];
			dp[cost] = max(dp[cost], mi[i] + dp[ci[j]]);
		}
	}

	/*
	for (int i = 0; i < 10000; i++) {
		if (dp[i] == -1) continue;
		cout << "dp[" << i << "]=" << dp[i] << endl;
		if (dp[i] >= M) break;
	}
	*/
	for (int i = 0; i < 10000; i++) {
		if (dp[i] == -1) continue;
		if (dp[i] >= M) {
			cout << i;
			break;
		}
	}
}
//BFS//

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stdlib.h>

using namespace std;

int N, K;
int ans = 0;

void bfs() {
	queue< pair<int, int> > q;
	q.push(pair<int, int>(N, 0));
	bool check[100001] = { 0, };
	
	while (!q.empty()) {
		int n = q.front().first;
		int lv = q.front().second;
		q.pop();
		if (n == K) {
			ans = lv;
			break;
		}
		if (check[n]) continue;
		lv++;
		check[n] = true;
		if (n > K) {
			q.push(pair<int, int>(n - 1, lv));
		}
		else {
			if (n + 1 <= 100000) q.push(pair<int, int>(n + 1, lv));
			if (n * 2 <= 100000) q.push(pair<int, int>(n * 2, lv));
			if (n - 1 >= 0) q.push(pair<int, int>(n - 1, lv));
		}
	}
}
int main() {
	cin >> N >> K;
	if (K <= N) {
		cout << N - K;
		return 0;
	}
	
	bfs();
	cout << ans;
}
#include <iostream>
#include <vector>
#include <stdio.h>
#include <queue>

using namespace std;
int N, M;
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
vector < vector<bool> > v(N + 2, vector<bool>(M + 2, 0));
//vector < vector<bool> > v;
int bfs() {
	int x = 1;
	int y = 1;
	vector < vector<int> > a(N + 1, vector<int>(M + 1, 0));
	queue< pair<int, int>>q;
	
	q.push(pair<int, int>(y, x));
	a[1][1] = 1;

	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int yy = y + dy[i];
			int xx = x + dx[i];
			//cout << "(" << yy << ", " << xx << ")" << endl;

			if (xx > 0 && xx <= M && yy > 0 && yy <= N 
				&& a[yy][xx] == 0 && v[yy][xx]) {
				a[yy][xx] = a[y][x] + 1;
				q.push(make_pair(yy, xx));
			}
		}
	}

	return a[N][M];
}
int main() {
	cin >> N;
	cin >> M;

	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int temp;
			scanf_s("%1d", &temp);
			if (temp == 1) v[i][j] = true;
		}
	}

	cout << bfs();
}
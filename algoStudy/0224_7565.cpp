#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int M, N;
int tom;
//int **a;
queue <pair<int, int>> q;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
vector < vector<int> > a;


int bfs() {
	int ret = 0;
	int cnt = 0;
	int x, y;
	bool ripe = true;

	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		int yy = y;
		int xx = x;
		q.pop();

		cnt = a[y][x];
		for (int i = 0; i < 4; i++) {
			xx = x +dx[i];
			yy = y + dy[i];
			if (xx >= 0 && xx < M && yy>=0 && yy < N && a[yy][xx] == 0) {
				a[yy][xx] = cnt +1;
				cout << "(" << yy << ", " << xx << ")" << endl;
				q.push(make_pair(yy, xx));
				if (cnt > ret) ret = cnt;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (a[i][j] == 0) ripe = false;
		}
	}
	if (!ripe) ret = -1;
	
	return ret;
}
int main() {
	cin >> M;
	cin >> N;
	bool riped = true;
	
	for (int i = 0; i < N; i++) {
		vector <int> element(M);
		a.push_back(element);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> a[i][j];
			if (a[i][j] == 0) riped = false;
			if (a[i][j] == 1) q.push(make_pair(i, j));
		}
	}

	if (riped) cout << 0;
	else cout << bfs();
}
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stdlib.h>

#define MAX 100000000
using namespace std;

int N, M;
int wall = 0;
vector < pair<int, int> >v; //(y, x)
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 };
int loop = 0;
void fill(int board[][8], int dir, int x, int y) { //한방향 채우기
	int xx = x + dx[dir];
	int yy = y + dy[dir];

	while (yy >= 0 && xx >= 0 && yy < N && xx < M && board[yy][xx] != 6) {
		if (board[yy][xx] == 0) board[yy][xx] = -1;
		xx += dx[dir];
		yy += dy[dir];
	}
}
void fill2(int board[][8], int dir, int x, int y) { //양방향 채우기
	int x1, x2; x1 = x2 = x;
	int y1, y2; y1 = y2 = y;
	if (dir == 0) { //상하
		bool UP = true;
		bool DOWN = true;
		for (int i = 1; i <= max(y, N - 1 - y); i++) {
			y1 += dy[1];
			y2 += dy[3];
			if (y1 < 0 || y1 >= N || board[y1][x] == 6) UP = false;
			if (y2 < 0 || y2 >= N || board[y2][x] == 6) DOWN = false;
			if (UP && board[y1][x] == 0) board[y1][x] = -1;
			if (DOWN && board[y2][x] == 0) board[y2][x] = -1;
		}
	}
	else {//좌우
		bool RIGHT = true;
		bool LEFT = true;
		for (int i = 1; i <= max(x, M - 1 - x); i++) {
			x1 += dx[0];
			x2 += dx[2];
			if (x1 < 0 || x1 >= M || board[y][x1] == 6) RIGHT = false;
			if (x2 < 0 || x2 >= M || board[y][x2] == 6) LEFT = false;
			if (RIGHT && board[y][x1] == 0) board[y][x1] = -1;
			if (LEFT && board[y][x2] == 0) board[y][x2] = -1;
		}
	}

}
int rec(int l, int(*board)[8]) {
	int tmp[8][8] = { 0, };
	int res = MAX;
	int x = 0, y = 0;
	x = v[l].second;
	y = v[l].first;
	int cctv = board[y][x];
	//cout << "(" << y << "," << x << ")"<< "cctv" << board[y][x] << endl;
	if (cctv == 1) {
		for (int dir = 0; dir < 4; dir++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					tmp[i][j] = board[i][j];
				}
			}
			fill(tmp, dir, x, y);
			if ((l + 1) >= loop) {
				int cnt = 0;
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < M; j++) {
						if (tmp[i][j] == 0) cnt++;
					}
				}
				//debug
				/*
				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++) {
						cout << tmp[i][j];
					}
					cout << endl;
				}
				*/
				//debug
				res = min(res, cnt);
			}
			else {
				int cnt = rec(l + 1, tmp);
				res = min(res, cnt);
			}
		}
	}
	else if (cctv == 2) {
		for (int dir = 0; dir < 2; dir++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					tmp[i][j] = board[i][j];
				}
			}
			fill2(tmp, dir, x, y);
			if ((l + 1) >= loop) {
				int cnt = 0;
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < M; j++) {
						if (tmp[i][j] == 0) cnt++;
					}
				}
				res = min(res, cnt);
			}
			else res = min(res, rec(l + 1, tmp));
		}
	}
	else if (cctv == 3) {
		for (int dir = 0; dir < 4; dir++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					tmp[i][j] = board[i][j];
				}
			}
			fill(tmp, dir, x, y);
			fill(tmp, (dir + 1) % 4, x, y);
			if ((l + 1) == loop) {
				int cnt = 0;
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < M; j++) {
						if (tmp[i][j] == 0) cnt++;
					}
				}

				res = min(res, cnt);
			}
			else res = min(res, rec(l + 1, tmp));
		}
	}
	else if (cctv == 4) {
		for (int dir = 0; dir < 4; dir++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					tmp[i][j] = board[i][j];
				}
			}
			fill2(tmp, dir % 2, x, y);
			fill(tmp, dir, x, y);
			if ((l + 1) == loop) {
				int cnt = 0;
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < M; j++) {
						if (tmp[i][j] == 0) cnt++;
					}
				}
				res = min(res, cnt);
			}
			else res = min(res, rec(l + 1, tmp));
		}
	}
	return res;
}
void fill5(int(*board)[8], int x, int y) {
	bool LU = true;
	bool RD = true;
	for (int i = 1; i <= max(M - 1 - x, x); i++) { //가로 채우기
		int x1 = x + i;
		int x2 = x - i;
		if (x1 >= M || board[y][x1] == 6) RD = false;
		if (x2 < 0 || board[y][x2] == 6) LU = false;
		if (RD && board[y][x1] == 0)
			board[y][x1] = -1;
		if (LU && board[y][x2] == 0)
			board[y][x2] = -1;
	}
	LU = true;
	RD = true;
	for (int i = 1; i <= max(N - 1 - y, y); i++) { //세로 채우기
		int y1 = y + i;
		int y2 = y - i;
		if (y1 >= N || board[y1][x] == 6) RD = false;
		if (y2 < 0 || board[y2][x] == 6) LU = false;
		if (RD && board[y1][x] == 0)
			board[y1][x] = -1;
		if (LU && board[y2][x] == 0)
			board[y2][x] = -1;
	}
}
int main() {
	cin >> N >> M;
	bool nothing = true;
	int idx = 0;

	vector < pair<int, int> > cctv5;
	int board[8][8] = { 0, };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 6) wall++;
			else if (board[i][j] > 0) {
				if (board[i][j] == 5)
					cctv5.push_back(make_pair(i, j));
				else
					v.push_back(make_pair(i, j));
				nothing = false;
			}
		}
	}

	if (nothing) {
		int res = N * M - wall;
		cout << res;
		return 0;
	}

	while (!cctv5.empty()) { //5번 cctv는 항상 같은 방향
		int x, y;
		x = cctv5[idx].second;
		y = cctv5[idx].first;
		for (int i = 0; i < 4; i++) {
			fill5(board, x, y);
		}
		idx++;
		if (idx == cctv5.size()) break;
	}

	//debug
	/*
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	*/
	//debug
	loop = v.size();
	if (loop == 0) {
		/*
		런타임 에러 난 이유:
		cctv 5만 있고 나머지는 없는 경우 v 비어있음 -> vector out of range
		*/
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (board[i][j] == 0) cnt++;
			}
		}
		cout << cnt;
	}
	else cout << rec(0, board);
}
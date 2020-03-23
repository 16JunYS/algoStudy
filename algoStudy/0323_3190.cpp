#include <iostream>
#include <utility>
#include <queue>

/*
1. 머리 한칸 이동
2. 사과 있는 경우 꼬리 이동x (몸 길이 증가)
3. 사과 없는 경우 꼬리 이동 (몸 길이 변함없음)
4. 이동 후 방향 변환
*/
using namespace std;

int N, K, L;
/* 
	board[y][x][0] : 사과(1), 뱀(1) 몸 여부
	board[y][x][1] : 방향 전환 여부 (0: 동, 1: 남, 2: 서 3: 북)
*/
int board[101][101][2] = { 0, };
char dir[10001] = { 0, }; // dir[i]: i초 방향
pair<int, int> head; //(y, x)
pair<int, int> tail; //(y, x)
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int h_dir = 0;

void solve() {
	int cnt = 0;
	vector< pair<int, int> >v;

	while (1) {
		cnt++;
		//뱀 머리 이동
		int xx = head.second;
		int yy = head.first;
		xx += dx[h_dir];
		yy += dy[h_dir];

		//debug
		//cout << "(" << head.first << "," << head.second << ")" << h_dir<<endl;
		//debug
		if (xx == 0 || yy == 0 || xx > N || yy > N || board[yy][xx][0] == 2) //부딪힌 경우
			break;
		if (board[yy][xx][0] == 1) { //사과 먹기. 꼬리 이동x
			if (tail.first == head.first && tail.second == head.second);
			else {
				v.push_back(make_pair(head.first, head.second)); //몸통 좌표 추가
			}
		}
		else { //꼬리(몸통) 이동o
			int t_xx = tail.second;
			int t_yy = tail.first;
			int t_dir = board[t_yy][t_xx][1];
			t_xx += dx[t_dir];
			t_yy += dy[t_dir];
			board[tail.first][tail.second][0] = 0;
			tail.first = t_yy;
			tail.second = t_xx;
			board[tail.first][tail.second][0] = 2;
			if (!v.empty()) {
				for (int i = 0; i < v.size(); i++) {
					int b_xx = v[i].second;
					int b_yy = v[i].first;
					int b_dir = board[b_yy][b_xx][1];
					b_xx += dx[b_dir];
					b_yy += dy[b_dir];
					v[i].first = b_yy;
					v[i].second = b_xx;
				}
			}
		}
		//머리 이동
		head.first = yy;
		head.second = xx;
		board[head.first][head.second][0] = 2;
		board[head.first][head.second][1] = h_dir;

		//방향 전환 여부
		if (dir[cnt] != NULL) {
			//cout << cnt<<"들어가지냐" << endl;
			int next_d = 0;
			switch (dir[cnt]) {
				case 'D': //오
					next_d = (h_dir + 1) % 4;
					break;
				case 'L': //왼
					next_d = h_dir - 1;
					if (next_d == -1) next_d = 3;
					break;
			}
			h_dir = board[head.first][head.second][1] = next_d;
		}
	}

	cout << cnt;
}
int main() {
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> y >> x;
		board[y][x][0] = 1;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int sec;
		cin >> sec;
		cin >> dir[sec];
	}
	head.first = 1;
	head.second = 1;
	tail.first = 1;
	tail.second = 1;
	board[1][1][0] = 2;

	solve();
}
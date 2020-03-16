#include <iostream>
#include <vector>
using namespace std;

int N, M;
int x, y, K;
int dice[6] = { 0, };
vector < vector<int> >map;
vector <int> order;

void East() {
	int temp[6];
	for (int i = 0; i < 6; i++) {
		temp[i] = dice[i];
	}
	dice[0] = temp[3];
	dice[2] = temp[0];
	dice[3] = temp[5];
	dice[5] = temp[2];
}
void West() {
	int temp[6];
	for (int i = 0; i < 6; i++) {
		temp[i] = dice[i];
	}
	dice[0] = temp[2];
	dice[2] = temp[5];
	dice[3] = temp[0];
	dice[5] = temp[3];
}
void North() {
	int temp[6];
	for (int i = 0; i < 6; i++) {
		temp[i] = dice[i];
	}
	dice[0] = temp[4];
	dice[1] = temp[0];
	dice[4] = temp[5];
	dice[5] = temp[1];
}
void South() {
	int temp[6];
	for (int i = 0; i < 6; i++) {
		temp[i] = dice[i];
	}
	dice[0] = temp[1];
	dice[1] = temp[5];
	dice[4] = temp[0];
	dice[5] = temp[4];
}
void write(int x, int y) {
	//cout << "(" << y << "," << x << ") ";
	if (map[y][x] == 0) {
		map[y][x] = dice[5];
	}
	else {
		dice[5] = map[y][x];
		map[y][x] = 0;
	}
}
void solve(int cur_x, int cur_y) {
	//pair<int, int> curPos = make_pair(0, 0);
	for (int i = 0; i < K; i++) {
		bool ignore = false;
		switch (order[i]) {
			case 1: //east
				if (cur_x == M - 1) ignore = true;
				else {
					cur_x++;
					East();
				}
				break;
			case 2: //west
				if (cur_x == 0) ignore = true;
				else {
					cur_x--;
					West();
				}
				break;
			case 3: //north
				if (cur_y == 0) ignore = true;
				else {
					cur_y--;
					North();
				}
				break;
			case 4: //south
				if (cur_y == N - 1) ignore = true;
				else {
					cur_y++;
					South();
				}
				break;
		}
		if (!ignore) {
			write(cur_x, cur_y);
			cout << dice[0] << endl;
		}
	}
}
int main() {
	cin >> N >> M;
	cin >> x >> y >> K;
	map.assign(N, vector<int>(M, 0));
	order.assign(K, 0);

	int cur_x = 0;
	int cur_y = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		cin >> order[i];
	}
	solve(y, x);
}
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

#define MAX 100
using namespace std;

int N, M;
vector < pair<int, int> > house;
vector < pair<int, int> > chicken;
vector <int> open;
int h_size, c_size;
int ans=0;

void calculate() {
	int ret = 0;
	int distance = 0;
	vector <int> dist(h_size, MAX);

	for (int i = 0; i < h_size; i++) {
		int h_y = house[i].first;
		int h_x = house[i].second;
		for (int j = 0; j < c_size; j++) {
			if (open[j] == 0) 
				continue;
			int c_y = chicken[j].first;
			int c_x = chicken[j].second;
			dist[i] = min(dist[i], abs(h_y - c_y) + abs(h_x - c_x));
		}
	}

	for (int i = 0; i < h_size; i++) {
		distance += dist[i];
	}
	//ans = min(ans, distance);
	if (ans == 0) ans = distance;
	else ans = min(ans, distance);
}
void dfs(int store, int cnt) {
	if (cnt == M) {
		calculate();
		return;
	}
	
	if (store == c_size) return;

	open[store]++;
	dfs(store + 1, cnt + 1);

	open[store]--;
	dfs(store + 1, cnt);
}
int main() {
	cin >> N;
	cin >> M;
	int m = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int temp;
			cin >> temp;
			if (temp == 1) {
				house.push_back(make_pair(i, j));
			}
			if (temp == 2) {
				chicken.push_back(make_pair(i, j));
				open.push_back(false);
			}
		}
	}
	c_size = (int)chicken.size();
	h_size = (int)house.size();
	dfs(0, 0);
	cout << ans;
}
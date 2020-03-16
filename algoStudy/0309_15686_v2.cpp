#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
//#define DEBUG 1
using namespace std;

int N;
int M;
int erase;
vector < pair<int, int> > house;
vector < pair<int, int> > chicken;
// adj[i][j] : distance bet. chicken store[i] and house[j]
vector < vector<int> >adj;

int calculate() {
	int ret = 0;
	for (int j = 0; j < house.size(); j++) {
		int dist = MAX;
		for (int i = 0; i < chicken.size(); i++) {
			if (adj[i][j] == -1) continue;
			dist = min(dist, adj[i][j]);
		}
		ret += dist;
	}
	return ret;
}
int dfs(int store, bool *check, int cnt) {
	int ret = 0;
	int dist = 0;
	int *temp = (int *)malloc(sizeof(int) * house.size());
	
	cnt++;
	check[store] = true;
	for (int i = 0; i < house.size(); i++) {
		temp[i] = adj[store][i];
		adj[store][i] = -1;
	}

	if (cnt == erase) {
		ret = calculate();
		for (int i = 0; i < house.size(); i++) {
			adj[store][i] = temp[i];
		}
		//check[store] = false;
		free(temp);
#ifdef DEBUG
		cout << store << " " << ret << endl;
#endif
		return ret;
	}
	else {
		dist = MAX;
		for (int i = store+1; i < chicken.size(); i++) {
			if (i < chicken.size() && !check[i]) {
#ifdef DEBUG
				cout << store;
#endif
				dist = min(dist, dfs(i, check, cnt));
				check[i] = false;
			}
		}
		for (int i = 0; i < house.size(); i++) {
			adj[store][i] = temp[i];
		}
		//check[store] = false;
		free(temp);
		ret = dist;
	}
	return ret;
}
int solve(int m) {
	int ret = 0;
	vector <int> chDist(m, 0);

	adj.assign(chicken.size(), vector<int>(house.size(), 0));
	for (int i = 0; i < chicken.size(); i++) {
		int c_y = chicken[i].first;
		int c_x = chicken[i].second;
		for (int j = 0; j < house.size(); j++) {
			int dist = 0;
			int h_y = house[j].first;
			int h_x = house[j].second;

			if (h_y > c_y) dist += h_y - c_y;
			else dist += c_y - h_y;
			if (h_x > c_x) dist += h_x - c_x;
			else dist += c_x - h_x;

			adj[i][j] = dist;
		}
	}
	if (erase > 0) {
		bool *check = (bool *)malloc(sizeof(bool) * chicken.size());
		memset(check, 0, sizeof(bool)*chicken.size());
		int distance = MAX;
		for (int i = 0; i < chicken.size(); i++) {
			distance = min(distance, dfs(i, check, 0));
			memset(check, 0, sizeof(bool)*chicken.size());
#ifdef DEBUG
			cout << "-----------" << endl;
			cout << distance << endl;
#endif
		}
		ret = distance;
	}
	else ret = calculate();

	return ret;
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
				m++;
			}
		}
	}
	erase = m - M;
	cout << solve(m);
}
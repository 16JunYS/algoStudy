#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

#define MAX 10000;
//#define DEBUG;
using namespace std;
int N;
int M;

vector < pair<int, int> > house;
vector < pair<int, int> > chicken;
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
int solve(int m) {
	int ret = 0;
	// adj[i][j] : distance bet. chicken store[i] and house[j]
	vector <int> chDist(m, 0);
	int erase = m-M;

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
#ifdef DEBUG
			cout << adj[i][j];
#endif

			if (erase != 0) chDist[i] += dist;
		}
#ifdef DEBUG
		cout << "|" << chDist[i] << endl;
#endif
	}

	while (erase > 0) {
		queue <int> q;
		erase--;
		int dist = 0;
		int store = 0;
		for (int i = 0; i < chicken.size(); i++) {
			if (dist <= chDist[i]) {
				if (dist == chDist[i]) {
					if (q.empty()) {
#ifdef DEBUG 
						cout << "pushed : " << store << endl; 
#endif
						q.push(store);
					}
						q.push(i);
#ifdef DEBUG
						cout << "pushed : " << i<<endl;
#endif
				}
				else {
					while (!q.empty()) {
						q.pop();
					}
					store = i;
					dist = chDist[i];
				}
			}
		}
		dist = MAX;
		while (!q.empty()) {
			int st = q.front();
			q.pop();
			vector <int> temp = adj[st];

			adj[st].assign(house.size(), -1);
			int cal = calculate();
			if (dist >= cal) {
				store = st;
				dist = cal;
			}
			adj[st] = temp;

		}
		adj[store].assign(house.size(), -1);
		chDist[store] = -1;
	}

	return calculate();

}

int main() {
	cin >> N;
	cin >> M;
	int m=0;

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

	cout << solve(m);
}
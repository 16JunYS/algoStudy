#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
int N;
vector < vector<bool> >v;
vector <int> cnt;

int solve() {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		vector <bool> check(N, 0);
		for (int j = 0; j < N; j++) {
			if (v[i][j]) {
				for (int k = 0; k < N; k++) {
					if (v[j][k] && !v[i][k] && i!=k && !check[k]) {
						check[k] = true;
						cnt[i]++;
					}
				}
			}
		}
		check.clear();
	}
	
	for (int i = 0; i < N; i++) {
		ret = max(ret, cnt[i]);
	}

	return ret;
}
int main() {
	cin >> N;

	v.assign(N, vector<bool>(N, true));
	cnt.assign(N, 0);
	for (int i = 0; i < N; i++) {
		string tmp;
		cin >> tmp;
		for (int j = 0; j < N; j++) {
			if (tmp[j] == 'N') v[i][j] = false;
			else {
				v[i][j] = true;
				cnt[i]++;
			}
		}
	}

	cout << solve();
}
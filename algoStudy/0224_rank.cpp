#include <iostream>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) {
	int answer = 0;
	int cnt = 0;
	vector < vector<bool> > a(n + 1, vector<bool>(n + 1, false));
	for (auto p : results) {
		a[p[0]][p[1]] = true;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j]) {
				for (int k = 1; k <= n; k++) {
					if (a[j][k]) {
						a[i][k] = true;
						for (int p = 1; p <= n; p++) {
							if (a[p][i]) a[p][k] = true;
						}
					}
				}
			}
		}
	}

	//SIMPLE SOLUTION//
	/*
	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= n; i++) {
			for (int k = 1; k <= n; k++) {
				if (a[i][j] && a[j][k]) a[i][k] = true;
			}
		}
	}
	*/

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] || a[j][i])
				cnt++;
		}
		if (cnt == n - 1) answer++;
		cnt = 0;
	}
	return answer;
}

int main() {
	vector < vector<int> > a({
		vector<int>({4,3}),
		vector<int>({4,2}),
		vector<int>({3,2}),
		vector<int>({1,2}),
		vector<int>({2,5})
	});
	int N = 5;

	cout << solution(N, a);
}
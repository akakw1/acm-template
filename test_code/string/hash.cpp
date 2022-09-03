// test problem : https://codeforces.com/contest/1200/problem/E
#include<bits/stdc++.h>
using namespace std;
template<long long mod, long long base>
struct Hash {
	int n;
	long long pw[1000005];
	long long hs[1000005];
	Hash() { n = 0; pw[0] = 1, hs[0] = 0;}
	void add(char s[], int l, int r) {
		for(int i = l; i <= r; i ++) {
			n ++;
			pw[n] = pw[n - 1] * base % mod;
			hs[n] = (hs[n - 1] * base % mod + s[i]) % mod;
		}
	}
	long long get(int l, int r) {
		return (hs[r] - hs[l - 1] * pw[r - l + 1] % mod + mod) % mod;
	}
};
char s[1000005];
Hash<1000000007, 233> h1, t1;
Hash<998244353, 257> h2, t2;
string a[100001];
int ed[100001];
char ans[1000005];
int len = 0;
bool cmp(int l1, int r1, int l2, int r2) {
	return h1.get(l1, r1) == t1.get(l2, r2) && h2.get(l1, r1) == t2.get(l2, r2);
}
int main() {
	int m;
	cin >> m;
	int n = 0;
	for(int i = 1; i <= m; i ++) {
		cin >> a[i];
		for(int j = 0; j < a[i].size(); j ++) s[++ n] = a[i][j];
		ed[i] = n;
	}
	h1.add(s, 1, n);
	h2.add(s, 1, n);
	for(int i = 1; i <= m; i ++) {
		int t = min(len, ed[i] - ed[i - 1]);
		while(t && ! cmp(ed[i - 1] + 1, ed[i - 1] + t, len - t + 1, len)) t --;
		t1.add(s, ed[i - 1] + 1 + t, ed[i]);
		t2.add(s, ed[i - 1] + 1 + t, ed[i]);
		for(int j = ed[i - 1] + 1 + t; j <= ed[i]; j ++) ans[++ len] = s[j];
	}
	ans[len + 1] = '\0';
	cout << ans + 1 << endl;
	return 0;
}

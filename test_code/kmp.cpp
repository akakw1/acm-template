#include<bits/stdc++.h>
using namespace std;
int n;
char s[1000005];
int nxt[1000005] = {0};
void kmp() {
	int j = 0;
	for(int i = 2; i <= n; i ++) {
		while(j && s[j + 1] != s[i]) j = nxt[j];
		if(s[j + 1] == s[i]) j ++;
		nxt[i] = j;
	}
}
int m;
char a[1000005];
void solve() {
	int j = 0;
	for(int i = 1; i <= m; i ++) {
		while(j && s[j + 1] != a[i]) j = nxt[j];
		if(s[j + 1] == a[i]) j ++;
		if(j == n) printf("%d\n", i - j + 1), j = nxt[j];
	}
}
int main() {
	scanf("%s%s", a + 1, s + 1);
	n = strlen(s + 1);
	m = strlen(a + 1);
	kmp();
	solve();
	for(int i = 1; i <= n; i ++) printf("%d ", nxt[i]);
	return 0;
}

# KMP
## 构建模式串 border 数组
```cpp
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
```

## 字符串匹配
```cpp
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
```
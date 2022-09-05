# KMP
时间复杂度：均摊$O(n)$
空间复杂度：$O(n)$ 
## 构建模式串 border 数组
border数组，也称前缀函数，nxt[r]表示在r处结尾的字串中，是原串的前缀的，长度的最大值（不包含s[1,r]）
即一个最大的l（l>1），满足 s[l,r] == s[1,r-l+1]
```cpp
int n; // 模式串的长度
char s[1000005]; // 模式串
int nxt[1000005] = {0}; // border数组 这里取名为next数组
// 构建模式串border数组
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
int m; // 待匹配串的长度
char a[1000005]; // 待匹配串
// 匹配字符串与构建border数组过程几乎一样
void solve() {
	int j = 0;
	for(int i = 1; i <= m; i ++) {
		while(j && s[j + 1] != a[i]) j = nxt[j];
		if(s[j + 1] == a[i]) j ++;
		// j == n 说明找到了一个匹配，a[i-j+1,i] 与模式串相同
		// 在找到匹配后同样需要让 j = nxt[j]
		if(j == n) printf("%d\n", i - j + 1), j = nxt[j];
	}
}
```
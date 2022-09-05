# KMP 自动机
KMP自动机与KMP相似，用于处理字符串的匹配问题
KMP自动机在KMP的基础上处理了每个位置后接任意字符后会到达的位置
时间复杂度：预处理$O(|s|*m)$ (s为模式串，m为字符集大小) 匹配$O(|t|)$ (t为待匹配串)
## 构建KMP自动机
```cpp
int n; // 模式串的长度
const int m = 26; // 字符集大小
char s[1000001]; // 模式串
int nxt[1000001][26] = {0}; // nxt数组
void init() {
    for(int i = 1; i <= n; i ++) s[i] -= 'a'; // 将所有字符移到0-25内
    // 构建KMP自动机
    // fail表示当前失配一次到达的位置
    for(int i = 1, fail = 0; i <= n; i ++) {
    	fail = nxt[fail][s[i]]; // 注意此行不能与下一行交换位置，否则fail会一直指向i
    	nxt[i - 1][s[i]] = i; // i-1位置后接一个s[i]会到达i位置
    	for(int j = 0; j < m; j ++)
    		nxt[i][j] = nxt[fail][j];
            // 由于nxt[fail][j]是在fail位置后接一个j到达的位置
            // 而当前位置失配一次会到达fail位置
            // 所以当前位置后接一个j会到达nxt[fail][j]位置
            // j==s[i+1]的情况会在下一轮循环处理
    }
}
```

## 字符串匹配
由于已经处理了每个位置后接每个字符会到达的位置，所以匹配时一直沿着nxt走就行
```cpp
int len; // 待匹配串的长度
char a[1000001]; // 待匹配串
void solve() {
    for(int i = 1, j = 0; i <= len; i ++) {
        j = nxt[j][a[i]]; // 沿着nxt数组走
        if(j == n) printf("%d\n", i - n + 1);
        // j==n即找到了一个匹配
        // 由于我们处理了nxt[n]所以当j==n时不必像kmp一样跳一次nxt，而是可以继续沿着nxt走
    }
}
```
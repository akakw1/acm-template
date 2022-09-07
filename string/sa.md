# 后缀排序

## 后缀排序（倍增）
时间复杂度 : $O(nlogn)$
```cpp
int n; // 字符串的长度
int m; // 排名不同的后缀的个数
char s[1000005]; // 待排序串
int sa[1000001]; // 排名为i的后缀的序号
int rk[1000001]; // 第i个后缀的排名
int bot[1000001] = {0}; // 用于排序的桶
int id[1000001]; // 第二关键字排名为i的后缀的序号
void suffix_sort() {
    // 首先对每个字符进行一次桶排，第i个后缀排名直接设为s[i]
    m = 256;
    for(int i = 1; i <= n; i ++) bot[s[i]] ++, rk[i] = s[i];
    for(int i = 1; i < m; i ++) bot[i] += bot[i - 1];
    for(int i = n; i >= 1; i --) sa[bot[s[i]] --] = i;
    // 进行倍增，直到每个后缀排名均不同为止
    for(int pw = 1, cnt = 0; cnt < n; pw <<= 1, m = cnt) {
        cnt = 0; // 此处借用cnt处理第二关键字的顺序
        for(int i = n - pw + 1; i <= n; i ++) id[++ cnt] = i; // 没有第二关键字的后缀放到最前
        // 按照第二关键字的顺序放置后缀
        // 上一轮排序结果即为第二关键字顺序
        for(int i = 1; i <= n; i ++)
            if(sa[i] > pw) id[++ cnt] = sa[i] - pw;
        // 开始排序
        for(int i = 0; i <= m; i ++) bot[i] = 0;
        for(int i = 1; i <= n; i ++) bot[rk[i]] ++;
        for(int i = 1; i <= m; i ++) bot[i] += bot[i - 1];
        // 按照第二关键字从大到小的顺序从桶中取出后缀
        for(int i = n; i >= 1; i --) sa[bot[rk[id[i]]] --] = id[i];
        // 排序完成后id数组没用了，这里借用id数组来储存上一轮的rk用于判断是否相同
        for(int i = 1; i <= n; i ++) id[i] = rk[i];
        rk[sa[1]] = cnt = 1;
        // 如果排名为i的后缀与排名为i-1的后缀在当前情况下完全相同，则赋予相同的排名(rk)
        for(int i = 2; i <= n; i ++)
            if(id[sa[i - 1]] == id[sa[i]] && id[sa[i - 1] + pw] == id[sa[i] + pw]) rk[sa[i]] = cnt;
            else rk[sa[i]] = ++ cnt;
    }
}
```

## 求最长公共前缀 (LCP)
预处理出排名为i的后缀与排名为i-1的后缀的LCP(记为height)，就能根据这些LCP求出任意两个后缀的LCP
排名为i的后缀与排名为j(i < j)的后缀的LCP为 min(height[i+1],height[i+2],...,height[j])
由于后缀i为后缀i+1前面删去一个字符，所以有 `height[rk[i]] >= height[rk[i - 1]] - 1`
根据此性质即可快速求出height数组
时间复杂度 : 预处理$O(n)$ 查询由实现方法而定
```cpp
int h[1000001]; // h[i]为排名为i的后缀与排名为i-1的后缀的LCP
void init() {
    h[1] = 0; // h[1]不存在设为0
    for(int i = 1, p = 0; i <= n; i ++, p = max(0, p - 1)) {
	    if(rk[i] == 1) continue; // h[1]在前面设置过了
	    while(i + p <= n && sa[rk[i] - 1] + p <= n && s[i + p] == s[sa[rk[i] - 1] + p]) p ++;
	    h[rk[i]] = p;
    }
}
```
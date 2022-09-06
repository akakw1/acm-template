# 后缀排序

## 后缀排序（倍增）
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
        for(int i = n - pw + 1; i <= n; i ++) id[++ cnt] = i;
        for(int i = 1; i <= n; i ++)
            if(sa[i] > pw) id[++ cnt] = sa[i] - pw;
        for(int i = 0; i <= m; i ++) bot[i] = 0;
        for(int i = 1; i <= n; i ++) bot[rk[i]] ++;
        for(int i = 1; i <= m; i ++) bot[i] += bot[i - 1];
        for(int i = n; i >= 1; i --) sa[bot[rk[id[i]]] --] = id[i];
        for(int i = 1; i <= n; i ++) id[i] = rk[i];
        rk[sa[1]] = cnt = 1;
        for(int i = 2; i <= n; i ++)
            if(id[sa[i - 1]] == id[sa[i]] && id[sa[i - 1] + pw] == id[sa[i] + pw]) rk[sa[i]] = cnt;
            else rk[sa[i]] = ++ cnt;
    }
}
```
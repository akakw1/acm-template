// test problem : https://www.luogu.com.cn/problem/P3809
#include<bits/stdc++.h>
using namespace std;
int n;
int m;
char s[1000005];
int sa[1000001];
int rk[1000001];
int bot[1000001] = {0};
int id[1000001];
void suffix_sort() {
    m = 256;
    for(int i = 1; i <= n; i ++) bot[s[i]] ++, rk[i] = s[i];
    for(int i = 1; i < m; i ++) bot[i] += bot[i - 1];
    for(int i = n; i >= 1; i --) sa[bot[s[i]] --] = i;
    for(int pw = 1, cnt = 0; cnt < n; pw <<= 1, m = cnt) {
        cnt = 0;
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
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    suffix_sort();
    for(int i = 1; i <= n; i ++) printf("%d ", sa[i]);
    return 0;
}
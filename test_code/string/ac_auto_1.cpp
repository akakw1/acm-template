#include<bits/stdc++.h>
using namespace std;
int nxt[200005][26] = {0};
int fail[200005] = {0};
int vt[200005] = {0};
int cnt = 0;
int ed[200001];
void insert(char *s, int id) {
    int p = 0;
    while(*s) {
        if(! nxt[p][*s - 'a']) nxt[p][*s - 'a'] = ++ cnt;
        p = nxt[p][*s - 'a'];
        s ++;
    }
    ed[id] = p;
}
int q[200005];
void build() {
    int head = 1, tail = 0;
    for(int i = 0; i < 26; i ++)
        if(nxt[0][i]) fail[nxt[0][i]] = 0, q[++ tail] = nxt[0][i];
    while(head <= tail) {
        int p = q[head ++];
        for(int i = 0; i < 26; i ++)
            if(nxt[p][i]) {
                fail[nxt[p][i]] = nxt[fail[p]][i];
                q[++ tail] = nxt[p][i];
            }
            else nxt[p][i] = nxt[fail[p]][i];
    }
}
int n;
void query(char *s) {
    int p = 0;
    while(*s) {
        p = nxt[p][*s - 'a'];
        vt[p] ++;
        s ++;
    }
    for(int i = cnt; i > 0; i --)
        vt[fail[q[i]]] += vt[q[i]];
}
char a[200005];
char s[2000005];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%s", a + 1);
        insert(a + 1, i);
    }
    build();
    scanf("%s", s + 1);
    query(s + 1);
    for(int i = 1; i <= n; i ++) printf("%d\n", vt[ed[i]]);
    return 0;
}
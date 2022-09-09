#include<bits/stdc++.h>
using namespace std;
struct node {
    int nxt[26];
    int fail;
    int vt;
    node() { memset(nxt, 0, sizeof(nxt)); vt = 0;}
} t[200005];
int cnt = 0;
int ed[200001];
void insert(char *s, int id) {
    int p = 0;
    while(*s) {
        if(! t[p].nxt[*s - 'a']) t[p].nxt[*s - 'a'] = ++ cnt;
        p = t[p].nxt[*s - 'a'];
        s ++;
    }
    ed[id] = p;
}
int q[200005];
void build() {
    int head = 1, tail = 0;
    for(int i = 0; i < 26; i ++)
        if(t[0].nxt[i])
            t[t[0].nxt[i]].fail = 0, q[++ tail] = t[0].nxt[i];
    while(head <= tail) {
        int p = q[head ++];
        for(int i = 0; i < 26; i ++)
            if(t[p].nxt[i]) {
                t[t[p].nxt[i]].fail = t[t[p].fail].nxt[i];
                q[++ tail] = t[p].nxt[i];
            }
            else t[p].nxt[i] = t[t[p].fail].nxt[i];
    }
}
int n;
void query(char *s) {
    int p = 0;
    while(*s) {
        p = t[p].nxt[*s - 'a'];
        t[p].vt ++;
        s ++;
    }
    for(int i = cnt; i > 0; i --)
        t[t[q[i]].fail].vt += t[q[i]].vt;
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
    for(int i = 1; i <= n; i ++) printf("%d\n", t[ed[i]].vt);
    return 0;
}
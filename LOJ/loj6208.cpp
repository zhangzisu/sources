#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int s[MAXN], fa[MAXN], deep[MAXN], dfn[MAXN], top[MAXN], tim;
void $$(int x) {
    s[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        deep[to[i]] = deep[x] + 1;
        fa[to[i]] = x;
        $$(to[i]);
        s[x] += s[to[i]];
    }
}
void $$$(int x) {
    dfn[x] = ++tim;
    if (!top[x]) top[x] = x;
    int huge = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && s[to[i]] > s[huge]) huge = to[i];
    if (huge) {
        top[huge] = top[x];
        $$$(huge);
    }
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != huge) $$$(to[i]);
}
struct tag {
    int a, b, c;
    inline tag(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
    inline tag& operator+=(const tag& x) {
        c += x.c - x.a * b;
        a += x.a;
        b += x.b;
        return *this;
    }
    inline int operator()() { return a * b + c; }
} v[MAXN << 2];
inline void pushDown(int n) {
    if (v[n].a || v[n].b || v[n].c) {
        v[n << 1] += v[n];
        v[n << 1 | 1] += v[n];
        v[n] = tag();
    }
}
void Modify(int n, int l, int r, int L, int R, tag val) {
    if (l == L && r == R) {
        v[n] += val;
        return;
    }
    int mid = (l + r) >> 1;
    pushDown(n);
    if (R <= mid)
        Modify(n << 1, l, mid, L, R, val);
    else if (L > mid)
        Modify(n << 1 | 1, mid + 1, r, L, R, val);
    else
        Modify(n << 1, l, mid, L, mid, val), Modify(n << 1 | 1, mid + 1, r, mid + 1, R, val);
}
int Query(int n, int l, int r, int p) {
    if (l == r) return v[n]();
    int mid = (l + r) >> 1;
    pushDown(n);
    if (p <= mid)
        return Query(n << 1, l, mid, p);
    else
        return Query(n << 1 | 1, mid + 1, r, p);
}
int n;
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    $$(1), $$$(1);
    int m;
    scanf("%d", &m);
    while (m--) {
        int t, x, d;
        scanf("%d%d", &t, &x);
        if (t == 1 || t == 2) {
            scanf("%d", &d);
            tag add = t == 1 ? tag(d, 0, 0) : tag(0, d, 0);
            while (x) Modify(1, 1, n, dfn[top[x]], dfn[x], add), x = fa[top[x]];
        }
        if (t == 3) {
            printf("%d\n", Query(1, 1, n, dfn[x]));
        }
    }
    return 0;
}

//       $@      #@      @@           @@      @@      @.                 @@     ~              @@              @#
//       @@      @@      @           -@$     ,@.     $@          ~@=    ,@@    -@@             @@              @#
//      $@@@    ;@..... @@.....      @@@;    @@....  @#.....     @@     =@:     *@@;           @@      =       @#
//      @@;@@   @@@@@@; @@@@@@@     *@.@@,  .@@@@@@ $@@@@@@#     @@     @@       .@@@          @@     .@@!     @#
//     @@  #@= $@      @@           @@  @@. @@      @#          =@:     @@         @           @@      -@@@    @#
//    #@:   @@,@@ @-  ~@~ !@       @@    @@@@ .@   @@  @*       @@      @@                  @@@@@@@@     @@@.  @#
//   *@@      :@  @@.  ~   @@     @@-    - @#  @@   -  ~@!      @@@@@@@@@@@@@@@@@@@@@@@@    @@@@@@@@      #@   @#
//   -@@@@@@@      !  @,    $     @@@@@@@@        #@    *       @@@@@@@@@@@@@@@@@@@@@@@@       @@          -   @#
//     @@@@@@         @,           -@@@@@@        #@                   @@                      @@              @#
//       @@    @@@@@@@@@@@@@@@@       @.   ~@@@@@@@@@@@@@@@*          ,@@                      @@     @,       @#
//       @@    =======@$=======       @.   -======@@=======:          #@:                      @@    $@@#      @#
//       @@           @,              @.          #@                  @@!!!!!!!!!!!!!          @@      @@@     @#
//    @@@@@@@*        @,          ;@@@@@@@        #@                 ~@@@@@@@@@@@@@@@          @@ =@    @@@!   @#
//    @@@@@@@*  @@@@@@@@@@@@@@    ;@@@@@@@  #@@@@@@@@@@@@@@          @@@@..........@@         !@@@@@     *@    @#
//       @@     @@@@@@@@@@@@@@        @.    #@@@@@@@@@@@@@@          @@.@$        ~@@      @@@@@@@;            @#
//    !  @@ .*  @     @,    #@     $  @. #~ #@    #@     @@         @@- @@        @@       #@@#@@              @#
//    @  @@ =@  @     @-    #@    ,@  @. @  #@    #@     @@        ~@@  ,@@      @@@       :   @@            ,;@@@@@@
//    @= @@ @.  @    @@@    @@     @  @. @  #@    @@@    @$        @@,   @@$    =@@            @@    ~#@@@@@@@@@@@@@@
//    ,@ @@ @   @   =@@@@ @@@@     @; @.!@  #@   @@@@~ @@@.       @@@     @@!  ;@@             @@   @@@@@@@@@@=@#
//     @ @@!@   ;  ;@ @,@=         ~@ @.@.  :;  @@#@,@           :@@       @@$#@@.             @@   @#*.       @#
//       @@       *@: @, @#           @.       @@ #@ $@.         @@~        @@@@.              @@              @#
//       @@  :   @@=  @, :@@          @. .-   @@  #@  @@=       @@@        #@@@@=              @@              @#
//      =@@@@@ .@@#   @,  -@@=      .@@@@@, $@@   #@   @@@.    @@@       @@@@=#@@@@            @@              @#
//   ;@@@@@@~.@@@:    @,   .@@@   @@@@@@$-:@@@    #@    *@@@   @@     $@@@@$    @@@@@#,        @@              @#
//   ,#;      =@      @,     @=   @=-      @@     #@      @    $   @@@@@@!        @@@@@@    @@@@@              @#
//                    @,                          #@                @@@             -@@.    @@@@               @#
//                    -.                          --                ~                                          ;:
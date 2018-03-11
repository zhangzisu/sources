#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
int n, m, map[200][200];
inline char g(){
    char ch = getchar();
    while(ch != '.' && ch != '#')ch = getchar();
    return ch;
}
inline int trans(int i, int j){return (i - 1) * m + j;}
inline std::pair<int, int> decode(int x){ return std::make_pair((x - 1) / m + 1, (x - 1) % m + 1); }
int head[50000], to[80000], next[80000], tot = 0;
inline void $(int u, int v){
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int vis[50000], match[50000], tim;
int hg(int x){
    for(int i = head[x];~i;i = next[i]){
        if(vis[to[i]] == tim)continue;
        vis[to[i]] = tim;
        if(!match[to[i]] || hg(match[to[i]]))return  match[match[to[i]] = x] = to[i], 1;
    }
    return 0;
}
const int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
std::vector<int> D, T;
std::vector<std::pair<int, int>> ans;
int die[50000];
void DFS(int x){
    die[x] = 1;
    for(int i = head[x];~i;i = next[i]){
        if(match[to[i]] && !die[match[to[i]]])DFS(match[to[i]]);
    }
}
int main(){
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            map[i][j] = g() == '.';
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if((i + j) & 1 && map[i][j]){
                for(int k = 0;k < 4;k++){
                    if(i + d[k][0] >= 1 && j + d[k][1] >= 1 &&
                       i + d[k][0] <= n && j + d[k][1] <= m &&
                       map[i + d[k][0]][j + d[k][1]])$(trans(i, j), trans(i + d[k][0], j + d[k][1]));
                }
                D.push_back(trans(i, j));
            }else if(map[i][j]){
                T.push_back(trans(i, j));
            }
        }
    }
    int cnt = 0;
    for(auto i : D)tim++, cnt += hg(i);
    for(auto i : D)if(!match[i])DFS(i);
    for(auto i : T)if(!match[i])DFS(i);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(map[i][j] && die[trans(i, j)])ans.push_back(std::make_pair(i, j));
        }
    }
    printf("%lu\n", ans.size());
    for(auto i : ans)printf("%d %d\n", i.first, i.second);
    return 0;
}
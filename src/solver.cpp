#include <bits/stdc++.h>
#define ll long long 
using namespace std;

int di[]={0,0,1,-1},
    dj[]={1,-1,0,0};

bool vis[100][100];
int n,m,no_of_obs;
char GRID[100][100];
int path_GRID[100][100];
char obstacle='x';
char start_point='s';

#define invalid(i,j) i>=n || j>=m || i<0 || j<0 || vis[i][j] || GRID[i][j]==obstacle


bool dfs(int pi,int pj,int covered=1){
    static int cur = n*m - no_of_obs;
    if(covered==n*m-no_of_obs)
        return 1;

    vis[pi][pj]=1;

    for(int k=0;k<4;k++){
        int i=pi+di[k];
        int j=pj+dj[k];
        if(invalid(i,j)) continue;
        if(dfs(i,j,covered+1)){
            path_GRID[i][j]=cur--;
            return 1;
        }
    }
    vis[pi][pj]=0;
    return 0;
}


void solve(){
    no_of_obs=0;
    memset(vis,0,sizeof(vis));
    cin>>n>>m;
    char c;
    int sn,sm=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c; GRID[i][j]=c;
            if(c==obstacle) {
                no_of_obs++;
//                 path_GRID[i][j]=-1;
            }
            else if(c==start_point){
                sn=i,sm=j;
                path_GRID[i][j]=1;
            }
        }
    }
    dfs(sn,sm);
    for(int i=0;i<n;i++,cout<<'\n'){
        for(int j=0;j<m;j++){
            cout<<path_GRID[i][j]<<"\t";
        }
    }
}

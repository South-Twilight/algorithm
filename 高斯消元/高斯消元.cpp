#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1100;

int n;
int a[N][N];

int gauss()
{
    int r, c;
    for(r = 0, c = 0; c < n; c ++) {
        int t = r;
        for(int i = r; i < n; i ++) {
            if(a[i][c]) {
                t = i;
                break;
            }
        }
        if(!a[t][c]) continue;
        for(int i = c; i < n + n; i ++) swap(a[r][i], a[t][i]);
        for(int i = r + 1; i < n; i ++) {
            if(a[i][c]) {
                for(int j = 2*n; j >= c; j --) {
                    a[i][j] ^= a[r][j];
                }
            }
        }
        r ++;
    }
    if(r < n) {
        for(int i = r; i < n; i ++) {
            if(a[i][n]) {
      
				return 2;
            }
        }
        return 1;
    }
    for(int i = n - 1; i >= 0; i --) {
        for(int j = i + 1; j < n; j ++) {
        	for (int k=n;k<2*n;k++)
            a[i][k] ^= a[j][k] & a[i][j];
        }
    }
    return 0;
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n ; j ++) {
            scanf("%d", &a[j][i]);
        }
    }
    for (int i=0;i<n;i++)
     for (int j=n;j<2*n;j++)
      if (j-i==n)a[i][j]=1; else a[i][j]=0;
    int t = gauss();
    if(t==0||t==1) for(int i =n; i < 2*n; i ++) {for (int j=0;j<n;j++) if (a[j][i]==1) printf("%d ",j+1); puts("");}
    else puts("-1");
    return 0;
} 
#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const int maxn = 3e7;
int len;
char s[maxn], t[maxn];
int rds[maxn];

int Manacher(){
	int R = 0, pos, maxlen = 0;
	For(i, 1, len){
		if(i < R) rds[i] = min(rds[2 * pos - i], R - i + 1);
		else rds[i] = 1;
		while(s[i - rds[i]] == s[i + rds[i]]) ++rds[i];
		if(R < i + rds[i]) pos = i, R = i + rds[i] - 1;
		maxlen = max(maxlen, rds[i] - 1);
	}
	return maxlen;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> (t + 1);
	len = strlen(t + 1);
	int n = 0;
	s[n] = '@';
	s[++n] = '#';
	For(i, 1, len){
		s[++n] = t[i];
		s[++n] = '#';
	}
	s[++n] = '\0';
	len = n - 1;
	printf("%d\n", Manacher());
	return 0;
}

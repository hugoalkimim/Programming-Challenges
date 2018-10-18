/*******************************************
Hugo Danilo Santos Alkimim
18-10-2018
********************************************/

#include <bits/stdc++.h>

using namespace std;

#define INF 1222333444555
#define NMAX 1222

typedef long long int lli;

lli nxt[NMAX];
lli v[NMAX][NMAX];
lli dp[NMAX][NMAX];
vector < pair < pair < lli, lli >, pair < lli, lli >  > > shows;
lli T, all_visited;

lli f(lli pos, lli mask)
{
	if(pos == T)
	{
		if(mask == all_visited)
			return 0;
		return -INF;
	}

	if(v[pos][mask] == 1)
	{
		return dp[pos][mask];
	}
	v[pos][mask] = 1;

	lli opt1 = f(pos + 1, mask);
	lli opt2 = f(nxt[pos], mask | (1 << shows[pos].second.second)) + shows[pos].second.first;

	return dp[pos][mask] = max(opt1, opt2);
}

int main()
{
	lli N, M;

	scanf("%lld", &N);
	for(lli i = 0; i < N; i++)
	{
		scanf("%lld", &M);
		for(lli j = 0; j < M; j++)
		{
			lli a, b, c;
			scanf("%lld %lld %lld", &a, &b, &c);
			shows.push_back( make_pair( make_pair(a, b), make_pair(c, i) ) );
		}
	}

	sort(shows.begin(), shows.end());

	all_visited = (1 << N) - 1;
	T = shows.size();
	for(lli i = 0; i < T; i++)
	{
		nxt[i] = T;
		for(lli j = i + 1; j < T; j++)
		{
			if(shows[i].first.second <= shows[j].first.first)
			{
				nxt[i] = j;
				break;
			}
		}
	}

	printf("%lld\n", f(0, 0) > 0 ? f(0, 0) : -1);

    return 0;
}

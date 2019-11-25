/*******************************************
Hugo Danilo Santos Alkimim
********************************************/

#include <bits/stdc++.h>

#define NMAX 2111

using namespace std;

typedef long long int lli;

lli N, T, caso;
lli valor[NMAX], comprimento[NMAX];
lli visitado[NMAX];
lli dp[NMAX];

lli topDown(lli capacidade)
{
	if(capacidade == 0)
	{
		return 0;
	}

	if(visitado[capacidade] == caso)
	{
		return dp[capacidade];
	}
	visitado[capacidade] = caso;

	dp[capacidade] = 0;
	// Avalia todos os itens que podem ser utilizados
	for(lli i = 0; i < N; i++)
	{
		// Confere se tem capacidade suficiente
		if(capacidade >= comprimento[i])
		{
			dp[capacidade] = max(dp[capacidade], topDown(capacidade - comprimento[i]) + valor[i]);
		}	
	}
	
	return dp[capacidade];
}

void bottomUp()
{
	for(lli i = 0; i <= T; i++)
	{
		dp[i] = 0;
		for(lli j = 0; j < N; j++)
		{
			if(i >= comprimento[j])
			{
				dp[i] = max(dp[i], dp[i - comprimento[j]] + valor[j]);
			}
		}
	}
}

int main()
{
	while(scanf("%lld %lld", &N, &T) != EOF)
	{
		caso++;
		for(lli i = 0; i < N; i++)
		{
			scanf("%lld %lld", &comprimento[i], &valor[i]);
		}

		topDown(T);
		//bottomUp();
		printf("%lld\n", dp[T]);
	}
    
	return 0;
}


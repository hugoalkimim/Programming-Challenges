/*******************************************
Hugo Danilo Santos Alkimim
********************************************/

#include <bits/stdc++.h>

using namespace std;

#define NMAX 222111

typedef long long int lli;

lli N, C;
lli val[NMAX];
lli dp[NMAX][2];
lli dpO[2][2];
bool visitado[NMAX][2];

// DP na posi��o/dia atual e no estado
// Estado � 0 quando n�o tem nada comprado no momento e 1 quando tem
lli topDown(lli pos, lli estado)
{
    if(visitado[pos][estado] == true)
    {
        return dp[pos][estado];
    }
    visitado[pos][estado] = true;

    // Caso voc� tenha algo no ultimo dia sempre vai compensar vender
    if(pos == N - 1)
    {
        return dp[pos][estado] = (estado == 0 ? 0 : val[N - 1]);
    }

    // Verifica se � melhor comprar hoje ou n�o
    if(estado == 0)
    {
        return dp[pos][0] = max(-val[pos] - C + topDown(pos + 1, 1), topDown(pos + 1, 0));
    }

    // Verifica se � melhor vender hoje ou n�o
    return dp[pos][1] = max(val[pos] + dp[pos + 1][0], dp[pos + 1][1]);
}

void bottomUp()
{
    dp[N - 1][0] = 0;
	dp[N - 1][1] = val[N - 1];
	for(lli i = N - 2; i >= 0; i--)
	{
		dp[i][0] = max(-val[i] - C + dp[i + 1][1], dp[i + 1][0]);
		dp[i][1] = max(val[i] + dp[i + 1][0], dp[i + 1][1]);
	}
}

// Otimiza��o para reduzir gasto de mem�ria
void bottomUpOtimizado()
{
    dpO[(N - 1) % 2][0] = 0;
	dpO[(N - 1) % 2][1] = val[N - 1];
	for(lli i = N - 2; i >= 0; i--)
	{
		dpO[i % 2][0] = max(-val[i] - C + dpO[(i + 1) % 2][1], dpO[(i + 1) % 2][0]);
		dpO[i % 2][1] = max(val[i] + dpO[(i + 1) % 2][0], dpO[(i + 1) % 2][1]);
	}
}

int main()
{
	scanf("%lld %lld", &N, &C);

	for(lli i = 0; i < N; i++)
	{
		scanf("%lld", &val[i]);
	}

	//printf("%lld\n", topDown(0, 0));

    //bottomUp();
	//printf("%lld\n", dp[0][0]);

    bottomUpOtimizado();
    printf("%lld\n", dpO[0][0]);


    	return 0;
}

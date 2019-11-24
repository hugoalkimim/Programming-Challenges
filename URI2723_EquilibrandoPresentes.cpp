/*******************************************
Hugo Danilo Santos Alkimim
********************************************/

#include <bits/stdc++.h>

using namespace std;

#define NMAX 10111

typedef long long int lli;

lli T, N, w[NMAX], visitado[NMAX][11];
bool dp[NMAX][11];
bool dpO[2][11];

// DP no presente que est� sendo avaliado no momento e no "balanco", que � 5 caso o tren� esteja balanceado,
// 0 se ele estiver desbalanceado em 5 unidades para o lado A e 10 se ele estiver desbalanceado para o lado B
bool topDown(lli pos, lli balanco)
{
    // Caso chegue no final existe uma distribui��o de presentes que deixa o tren� equilibrado
    if(pos == N)
    {
        return true;
    }

    // Verifica se esta posi��o ja foi visitada neste caso de teste
    if(visitado[pos][balanco] == T)
    {
        return dp[pos][balanco];
    }
    visitado[pos][balanco] = T;

    bool opt1 = 0, opt2 = 0;

    // Verifica se adicionar o presente neste lado n�o vai desequilibrar o tren�
    if(balanco - w[pos] >= 0)
    {
        opt1 = topDown(pos + 1, balanco - w[pos]);
    }

    // Verifica se adicionar o presente neste lado n�o vai desequilibrar o tren�
    if(balanco + w[pos] <= 10)
    {
        opt2 = topDown(pos + 1, balanco + w[pos]);
    }

    return dp[pos][balanco] = max(opt1, opt2);
}

// Vers�o bottom-up da DP
void bottomUp()
{

    // Caso seja possivel chegar no final � possivel equilibrar os presentes
    for(lli i = 0; i <= 10; i++)
    {
        dp[N][i] = true;
    }

    for(lli i = N - 1; i >= 0; i--)
    {
        for(lli j = 0; j <= 10; j++)
        {
            lli opt1 = false, opt2 = false, pos = i, balanco = j;
            if(balanco - w[pos] >= 0)
            {
                opt1 = dp[i + 1][balanco - w[pos]];
            }

            if(balanco + w[pos] <= 10)
            {
                opt2 = dp[i + 1][balanco + w[pos]];
            }
            dp[i][balanco] = max(opt1, opt2);
        }
    }
}

// Otimiza��o no gasto de mem�ria do bottom-up
void bottomUpOtimizado()
{
    // Caso seja possivel chegar no final � possivel equilibrar os presentes
    for(lli i = 0; i <= 10; i++)
    {
        dpO[N % 2][i] = true;
    }

    for(lli i = N - 1; i >= 0; i--)
    {
        for(lli j = 0; j <= 10; j++)
        {
            lli opt1 = false, opt2 = false, pos = i, balanco = j;
            if(balanco - w[pos] >= 0)
            {
                opt1 = dpO[(i + 1) % 2][balanco - w[pos]];
            }

            if(balanco + w[pos] <= 10)
            {
                opt2 = dpO[(i + 1) % 2][balanco + w[pos]];
            }
            dpO[i % 2][balanco] = max(opt1, opt2);
        }
    }
}

int main()
{
    scanf("%lld", &T);

    while(T)
    {
        scanf("%lld", &N);
        for(lli i = 0; i < N; i++)
        {
            scanf("%lld", &w[i]);
        }

        // Come�a na posi��o {0, 5} que representa o primeiro item e um tren� balanceado
        //topDown(0, 5);
        //bottomUp();
        //printf("%s\n", dp[0][5] == 1 ? "Feliz Natal!" : "Ho Ho Ho!");

        bottomUpOtimizado();
        printf("%s\n", dpO[0][5] == 1 ? "Feliz Natal!" : "Ho Ho Ho!");

        T--;
    }

    return 0;
}

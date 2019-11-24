/*******************************************
Hugo Danilo Santos Alkimim
********************************************/

#include <bits/stdc++.h>

using namespace std;

#define NMAX 100

int valor[NMAX], peso[NMAX];
int dp[NMAX][NMAX];
int dpO[NMAX][NMAX];

// Problema da mochila com peso e valor
// DP no item atual e na capacidade da mochila
void bottomUp(int capacidade, int qnt_itens)
{
    // Zera os valores para o item vazio/nulo
    for(int i = 0; i <= capacidade; i++)
    {
        dp[0][i] = 0;
    }

    // Zera os valores para todas as mochilas com capacidade 0
    for(int i = 0; i <= qnt_itens; i++)
    {
        dp[i][0] = 0;
    }

    for(int i = 1; i <= qnt_itens; i++)
    {
        for(int j = 1; j <= capacidade; j++)
        {
            // Pega o resultado o item atual não é selecionado
            dp[i][j] = dp[i - 1][j];

            // Verifica se a mochila tem capacidade suficiente para selecionar o item atual
            if(peso[i] <= j)
            {
                // Verifica se compensa ou não pegar o item atual
                dp[i][j] = max(dp[i][j], valor[i] + dp[i - 1][j - peso[i]]);
            }
        }
    }
    printf("%d min.\n", dp[qnt_itens][capacidade]);
}

void bottomUpOtimizado(int capacidade, int qnt_itens)
{
    for(int i = 0; i <= capacidade; i++)
    {
        dpO[0][i] = 0;
    }

    for(int i = 0; i < 2; i++)
    {
        dpO[i][0] = 0;
    }

    for(int i = 1; i <= qnt_itens; i++)
    {
        for(int j = 1; j <= capacidade; j++)
        {
            dpO[i % 2][j] = dpO[(i - 1) % 2][j];
            if(peso[i] <= j)
            {
                dpO[i % 2][j] = max(dpO[i % 2][j], valor[i] + dpO[(i - 1) % 2][j - peso[i]]);
            }
        }
    }
    printf("%d min.\n", dpO[qnt_itens % 2][capacidade]);
}

int main()
{
    int N, P, i;
    while(scanf("%d", &N) == 1 && N != 0)
    {
        scanf("%d", &P);
        for(i = 1; i <= N; i++)
        {
            scanf("%d %d", &valor[i], &peso[i]);
        }

        //bottomUp(P, N);
        bottomUpOtimizado(P, N);
    }
    return 0;
}

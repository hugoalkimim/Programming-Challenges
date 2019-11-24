/*******************************************
Hugo Danilo Santos Alkimim
********************************************/

#include <bits/stdc++.h>

using namespace std;

#define NMAX 1111

typedef long long int lli;
typedef pair < lli, lli > par;

lli N, T;
lli w[NMAX];
par dp[NMAX][NMAX];
par dpO[2][NMAX];

// DP na posição inicial e final do vetor
// Verifico de quem é a vez e calculo se a opção otima para o jogador atual é retirar o primeiro elemento ou o segundo
void bottomUp()
{
    for(lli i = N - 1; i >= 0; i--)
    {
        for(lli j = i; j < N; j++)
        {
            lli player = ((j - i) + 1) % 2; // Calcula de quem é a vez
            par opt1 = i + 1 <= j ? dp[i + 1][j] : make_pair(0LL, 0LL);
            par opt2 = i <= j - 1 ? dp[i][j - 1] : make_pair(0LL, 0LL);

            // Verifica se ao retirar o primeiro elemento o jogador ganha pontos
            if(w[i] % 2 == 0)
            {
                player == 0 ? opt1.first++ : opt1.second++;
            }

            // Verifica se ao retirar o ultimo elemento o jogador ganha pontos
            if(w[j] % 2 == 0)
            {
                player == 0 ? opt2.first++ : opt2.second++;
            }

            if(player == 0)
            {
                dp[i][j] = opt1.first > opt2.first ? opt1 : opt2;
            }
            else
            {
                dp[i][j] = opt1.second > opt2.second ? opt1 : opt2;
            }
        }
    }
}

void bottomUpOtimizado()
{
    for(lli i = N - 1; i >= 0; i--)
    {
        for(lli j = i; j < N; j++)
        {
            lli player = ((j - i) + 1) % 2; // Calcula de quem é a vez
            par opt1 = i + 1 <= j ? dpO[(i + 1) % 2][j] : make_pair(0LL, 0LL);
            par opt2 = i <= j - 1 ? dpO[i % 2][j - 1] : make_pair(0LL, 0LL);

            // Verifica se ao retirar o primeiro elemento o jogador ganha pontos
            if(w[i] % 2 == 0)
            {
                player == 0 ? opt1.first++ : opt1.second++;
            }

            // Verifica se ao retirar o ultimo elemento o jogador ganha pontos
            if(w[j] % 2 == 0)
            {
                player == 0 ? opt2.first++ : opt2.second++;
            }

            if(player == 0)
            {
                dpO[i % 2][j] = opt1.first > opt2.first ? opt1 : opt2;
            }
            else
            {
                dpO[i % 2][j] = opt1.second > opt2.second ? opt1 : opt2;
            }
        }
    }
}

int main()
{
    while(scanf("%lld", &N) && N != 0)
    {
        T++;
        N *= 2;
        for(lli i = 0; i < N; i++)
        {
            scanf("%lld", &w[i]);
        }

        //bottomUp();
        //printf("%lld\n", dp[0][N - 1].first);

        bottomUpOtimizado();
        printf("%lld\n", dpO[0][N - 1].first);
    }

    return 0;
}

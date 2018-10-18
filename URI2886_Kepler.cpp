/*******************************************
Hugo Danilo Santos Alkimim
18-10-2018
********************************************/

#include <bits/stdc++.h>

using namespace std;

#define NMAX 150111

typedef long long int lli;

vector < pair < double, pair < double, double > > > circles;
vector < vector < lli > > children(NMAX);

double dist(lli c1, lli c2)
{
    double a = circles[c1].second.first;
    double b = circles[c1].second.second;
    double c = circles[c2].second.first;
    double d = circles[c2].second.second;
    return sqrt( (a - c) * (a - c) + (b - d) * (b - d) );
}

lli has_intersection(lli idxA, lli idxB)
{
    double d = dist(idxA, idxB);
    if(circles[idxA].first > d + circles[idxB].first ||
       circles[idxB].first > d + circles[idxA].first ||
       d > circles[idxA].first + circles[idxB].first)
    {
        return 0;
    }
    return 1;
}

int main()
{
    lli N;

    scanf("%lld", &N);
    for(lli i = 0; i < N; i++)
    {
        double a, b, c;
        scanf("%lf %lf %lf", &a, &b, &c);
        circles.push_back( make_pair(c, make_pair(a, b)) );
    }

    sort(circles.begin(), circles.end());

    lli ans = 0;
    for(lli i = 0; i < N && ans < N; i++)
    {
        for(lli j = i + 1; j < N; j++)
        {
            if(!has_intersection(i, j))
            {
                children[j].push_back(i);
                break;
            }
            else
            {
                queue < lli > Q;
                Q.push(i);
                while(!Q.empty())
                {
                    lli u = Q.front();
                    Q.pop();
                    if(has_intersection(u, j))
                    {
                        ans++;
                        lli t = children[u].size();
                        for(lli k = 0; k < t; k++)
                        {
                            Q.push(children[u][k]);
                        }
                    }
                }
            }
        }
    }

    if(ans >= N)
    {
        printf("greater\n");
    }
    else
    {
        printf("%lld\n", ans * 2);
    }

    return 0;
}

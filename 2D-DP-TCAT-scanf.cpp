#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

// Global variables

// n is time, m is interval, k is maximum allowed bus number
int n, m, k;

// input C[i] for i = 1 to n
vector<int> C;

// OPT[i][j] for i = 1 to n+m-1, j = 1 to k
vector<vector<long long> > OPT;

// M[i][j] for i = 1 to n+m-1, j = 1 to k
vector<vector<int> > M;

// flag
int flag = 0;

// Regular DP using our recurrence formula
void dp()
{
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= k; j++)
    {
      if (i == 1)
      {
        OPT[i][j] = 0;
        M[i][j] = -1;
      }
      else if (j == 1)
      {
        for (int l = 1; l <= i - 1; l++)
          OPT[i][j] += (long long)C[l] * (i - l);
        M[i][j] = -1;
      }
      else
      {
        if (i <= m)
        {
          OPT[i][j] = OPT[i][1];
          M[i][j] = -1;
        }
        else
        {
          long long temp = 0;
          for (int l = i - m + 1; l <= i - 1; l++)
            temp += (long long)C[l] * (i - l);
          M[i][j] = i - m;

          // Calculate OPT[i][j] without using LLONG_MAX
          OPT[i][j] = temp + OPT[i - m][j - 1];

          for (int iprime = i - m - 1; iprime >= 1; iprime--)
          {
            temp += (long long)C[iprime + 1] * (i - (iprime + 1));
            if (OPT[iprime][j - 1] + temp < OPT[i][j])
            {
              OPT[i][j] = OPT[iprime][j - 1] + temp;
              M[i][j] = iprime;
            }
          }
        }
        // Special treatment for the last bus
        if (i == n)
        {
          for (int iprime = n - 1; iprime >= max(1, n - m + 1); iprime--)
          {
            int temp = 0;
            for (int x = iprime + 1; x <= n; x++)
            {
              temp += (long long)C[x] * (iprime + m - x);
            }
            if (OPT[iprime][j - 1] + temp < OPT[n][j])
            {
              flag = 1;
              OPT[n][j] = OPT[iprime][j - 1] + temp;
              M[n][j] = iprime;
            }
          }
        }
      }
    }
  }
  printf("%lld\n", OPT[n][k]);
}

void backTrack()
{
  vector<int> A;
  if (flag == 1)
    A.push_back(M[n][k] + m);
  else
    A.push_back(n);
  int i = n, j = k;
  while (i > 0 && j > 0 && M[i][j] >= 1)
  {
    A.push_back(M[i][j]);
    i = M[i][j];
    j--;
  }
  for (int idx = A.size() - 1; idx >= 0; idx--)
  {
    printf("%d", A[idx]);
    if (idx > 0)
    {
      printf(" ");
    }
  }
  printf("\n");
}

int main()
{
  scanf("%d %d %d", &n, &m, &k);

  C.resize(n + 1);
  OPT.assign(n + 1, vector<long long>(k + 1));
  M.assign(n + 1, vector<int>(k + 1));

  for (int i = 1; i <= n; i++)
  {
    scanf("%d", &C[i]);
  }

  dp();
  backTrack();

  return 0;
}

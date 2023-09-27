#include <iostream>
// #include <fstream>: ifstream infile("input.txt");
#include <vector>
#include <limits.h>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

// Global variables

// n is time, m is interval, k is maximum allowed bus number
int n, m, k;

// input C[i] for i = 1 to n
vector<int> C;

// OPT[i][j] for i = 1 to n+m-1, j = 1 to k
vector<vector<long long>> OPT;

// M[i][j] for i = 1 to n+m-1, j = 1 to k
vector<vector<int>> M;

// flag
int flag = 0;

// ifstream infile("input.txt");

// Regular DP using our recurrence formula
void dp()
{
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= k; ++j)
    {
      if (i == 1)
      {
        OPT[i][j] = 0;
        M[i][j] = -1;
      }
      else if (j == 1)
      {
        for (int l = 1; l <= i - 1; ++l)
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
          for (int l = i - m + 2; l <= i - 1; ++l)
            temp += (long long)C[l] * (i - l);
          OPT[i][j] = LLONG_MAX;
          for (int iprime = min(n - 1, i - m); iprime >= 1; iprime--)
          {
            temp += (long long)C[iprime + 1] * (i - iprime);
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
          for (int iprime = n - 1; iprime >= n - m + 1; iprime--)
          {
            int temp = 0;
            for (int x = iprime + 1; x <= n; x++)
            {
              temp += C[x] * (iprime + m - x);
            }
            if (OPT[iprime][k - 1] + temp < OPT[n][k])
            {
              flag = 1;
              OPT[n][k] = OPT[iprime][k - 1] + temp;
              M[n][k] = iprime;
            }
          }
        }
      }
    }
  }
  cout << OPT[n][k] << endl;
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
    cout << A[idx];
    if (idx > 0)
    {
      cout << " ";
    }
  }
  cout << endl;
}

int main()
{
  std::ios::sync_with_stdio(false);
  string line;
  getline(cin, line);
  stringstream ss(line);
  ss >> n >> m >> k;

  C.resize(n + 1);
  OPT.resize(n + 1, vector<long long>(k + 1));
  M.resize(n + 1, vector<int>(k + 1));

  getline(cin, line);
  stringstream ss2(line);
  for (int i = 1; i <= n; ++i)
  {
    ss2 >> C[i];
  }

  dp();
  backTrack();

  return 0;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;



pair<int, int> Rabin_Karp_2d(const vector<string> &T, const vector<string> &S)
{
	int n = T.size();
	int m = S.size();

	vector<vector<long long> > hashes(n + 1, vector<long long>(n + 1, 0)); // with barrier elements
	long long s_hash = 0;
	long long p = 31; // code all ascii
	long long current_p = 1;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			hashes[i + 1][j + 1] = (long long)(T[i][j] - 'a') * current_p + hashes[i][j + 1] + hashes[i + 1][j] - hashes[i][j];
			current_p *= p;
		}
	}

	current_p = 1;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			s_hash += (long long)(S[i][j] - 'a') * current_p;
			current_p *= p;
		}
		for (int j = m; j < n; ++j)
		{
			current_p *= p;
		}
	}

	current_p = 1;
	for (int i = m - 1; i < n; ++i)
	{
		for (int j = m - 1; j < n; ++j)
		{

			if (hashes[i + 1][j + 1] - hashes[i + 1 - m][j + 1] - hashes[i + 1][j + 1 - m] + hashes[i + 1 - m][j + 1 - m] == s_hash * current_p)
			{
				return { i + 1 - m, j + 1 - m };
			}
			current_p *= p;
		}
		for (int j = 0; j < m-1; ++j)
		{
			current_p *= p;
		}
	}
	return { -1, -1 };
}


int main()
{
	int n, m;
	cin >> n >> m;
	vector<string> T(n), S(m);
	for (int i = 0; i < n; ++i)
	{
		cin >> T[i];
	}

	for (int j = 0; j < m; ++j)
	{
		cin >> S[j];
	}
	auto res = Rabin_Karp_2d(T, S);
	cout << res.first << ' ' << res.second << endl;
	system("pause");
}

/*
4 2
abcd
abcd
abcd
abcd
ab
ab


4 2
abcd
abcd
abcd
abcd
cd
cd


4 2
abcd
abcd
abcd
abcd
ab
cd


*/

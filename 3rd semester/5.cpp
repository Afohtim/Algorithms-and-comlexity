#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

vector<vector<int> > multiply(const vector<vector<int> > &a, const vector<vector<int> > &b)
{
	vector<vector<int> > res;
	for (int i = 0; i < a.size(); ++i)
	{
		res.push_back(vector<int>());
		for (int j = 0; j < b.front().size(); ++j)
		{
			int c = 0;
			for (int k = 0; k < a.front().size(); ++k)
			{
				c += a[i][k] * b[k][j];
			}
			res[i].push_back(c);
		}
	}
	return res;
}

vector<vector<int> > sum(const vector<vector<int> > &a, const vector<vector<int> > &b)
{
	int n = a.size();
	int m = a.front().size();
	vector<vector<int> > res(n, vector<int>(m, 0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			res[i][j] = a[i][j] + b[i][j];
		}
	}
	return res;
}

vector<vector<int> > subtract(const vector<vector<int> > &a, const vector<vector<int> > &b)
{
	int n = a.size();
	int m = a.front().size();
	vector<vector<int> > res(n, vector<int>(m, 0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			res[i][j] = a[i][j] - b[i][j];
		}
	}
	return res;
}



void prepare(vector<vector<int> > &a, vector<vector<int> > &b)
{
	int n = max(a.size(), b.size());
	int m = max(a.front().size(), b.front().size());
	if (n & 1) n++;
	if (m & 1) m++;

	a.resize(n);
	b.resize(n);

	for (int i = 0; i < n; ++i)
	{
		a[i].resize(m);
		b[i].resize(m);
	}
}

vector<vector<int> >  copy_arr(const vector<vector<int> > &a, int nmin, int nmax, int mmin, int mmax)
{
	vector<vector<int> > res;
	for (int i = nmin; i < nmax; ++i)
	{
		res.push_back(vector<int>());
		for (int j = mmin; j < mmax; ++j)
		{
			res.back().push_back(a[i][j]);
		}
	}
	return res;
}

vector<vector<int> > make_mtx(const vector<vector<int> > a1, const vector<vector<int> > a2, const vector<vector<int> > a3, const vector<vector<int> > a4, int n, int m)
{
	vector<vector<int> > res;
	for (int i = 0; i < (n+1) / 2; ++i)
	{
		res.push_back(vector<int>());
		for (int j = 0; j < (m+1) / 2; ++j)
		{
			res[i].push_back(a1[i][j]);
		}
		for (int j = 0; j < m - (m+1) / 2; ++j)
		{
			res[i].push_back(a2[i][j]);
		}
	}
	for (int i = 0; i < n - (n+1) / 2; ++i)
	{
		res.push_back(vector<int>());
		for (int j = 0; j < (m+1) / 2; ++j)
		{
			res.back().push_back(a3[i][j]);
		}
		for (int j = 0; j < m - (m+1) / 2; ++j)
		{
			res.back().push_back(a4[i][j]);
		}
	}
	return res;
}

void pr_mx(const vector<vector<int> > &A)
{
    for(auto a : A)
    {
        for(auto b : a)
        {
            cout << b << ' ';
        }
        cout << '\n';
    }
}

vector<vector<int> > strassen_multiply(const vector<vector<int> > &A, const vector<vector<int> > &B)
{
	if (A.size() == 0 && B.size() == 0)
	{
		return vector<vector<int> >(0);
	}
	vector < vector<int> > A1 = A, B1 = B;
	prepare(A1, B1);
	int n = A1.size();
	if (n < 100)
		return multiply(A, B);
	vector< vector <vector<int> >  > a(5), b(5);
	a[1] = copy_arr(A1, 0, n / 2, 0, n / 2);
	a[2] = copy_arr(A1, 0, n / 2, n / 2, n);
	a[3] = copy_arr(A1, n / 2, n, 0, n / 2);
	a[4] = copy_arr(A1, n / 2, n, n / 2, n);
	b[1] = copy_arr(B1, 0, n / 2, 0, n / 2);
	b[2] = copy_arr(B1, 0, n / 2, n / 2, n);
	b[3] = copy_arr(B1, n / 2, n, 0, n / 2);
	b[4] = copy_arr(B1, n / 2, n, n / 2, n);

	vector<vector<vector<int> > > m(8);
	m[1] = strassen_multiply(sum(a[1], a[4]), sum(b[1], b[4]));
	m[2] = strassen_multiply(sum(a[3], a[4]), b[1]);
	m[3] = strassen_multiply(a[1], subtract(b[2], b[4]));
	m[4] = strassen_multiply(a[4], subtract(b[3], b[1]));
	m[5] = strassen_multiply(sum(a[1], a[2]), b[4]);
	m[6] = strassen_multiply(subtract(a[3], a[1]), sum(b[1], b[2]));
	m[7] = strassen_multiply(subtract(a[2], a[4]), sum(b[3], b[4]));

	vector<vector<vector<int> > > c(5);
	c[1] = sum(m[1], sum(m[4], subtract(m[7], m[5])));
	c[2] = sum(m[3], m[5]);
	c[3] = sum(m[2], m[4]);
	c[4] = sum(m[1], sum(m[3], subtract(m[6], m[2])));

	vector<vector<int> > res = make_mtx(c[1], c[2], c[3], c[4], A.size(), B.front().size());
	return res;

}


int main()
{
	clock_t time;
	ofstream fout("log.out");
	for (int i = 20; i <= 2000; i += 20)
	{
		vector<vector<int> > a(i, vector<int>(i, 1)), b(i, vector<int>(i, 1)), c1, c2;
		cout << "matrix" << i << 'x' << i << ":\n";
		fout << "matrix" << i << 'x' << i << ":\n";
		time = clock();
		c1 = multiply(a, b);
		time = clock() - time;
		cout << "Standard multiply: " << double(time) / CLOCKS_PER_SEC << " seconds\n";
		fout << "Standard multiply: " << double(time) / CLOCKS_PER_SEC << " seconds\n";

		time = clock();
		c2 = strassen_multiply(a, b);
		time = clock() - time;
		cout << "Strassen multiply: " << double(time) / CLOCKS_PER_SEC << " seconds\n";
		fout << "Strassen multiply: " << double(time) / CLOCKS_PER_SEC << " seconds\n";

		bool same = true;

		for (int i = 0; i < c1.size(); ++i)
		{
			for (int j = 0; j < c1.size(); ++j)
			{
				if (c1[i][j] != c2[i][j])
					same = false;
			}
		}
		if (!same)
		{
			for (int i = 0; i < c2.size(); ++i)
			{
				for (int j = 0; j < c2.size(); ++j)
				{
					cout << c2[i][j] << ' ';
				}
				cout << '\n';
			}
			system("pause");
		}
		cout << "are same: " << same << '\n';

	}
	system("pause");
	return 0;
}

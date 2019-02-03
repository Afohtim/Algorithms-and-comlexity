#include <iostream>
#include <string>
#include <vector>
#include <string>

using namespace std;

int naive(string text, string pattern)
{
	unsigned n = text.size();
	unsigned m = pattern.size();

	for (int i = 0; i < n - m + 1; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (text[i + j] == pattern[j])
			{
				if (j == m - 1)
					return i;
			}
			else
			{
				break;
			}
		}
	}
	return -1;
}

int Rabin_Karp(string text, string pattern)
{
	unsigned n = text.size();
	unsigned m = pattern.size();
	vector<unsigned> hashes(n + 1, 0);

	const unsigned p = 257;
	unsigned current_p = 1;
	for (int i = 0; i < n; ++i)
	{
		hashes[i + 1] = text[i] * current_p + hashes[i];
		current_p *= p;
	}

	unsigned hash_s = 0;
	current_p = 1;
	for (int i = 0; i < m; ++i)
	{
		hash_s += pattern[i] * current_p;
		current_p *= p;
	}

	current_p = 1;
	for (int i = m - 1; i < n; ++i)
	{
		if (hashes[i + 1] - hashes[i + 1 - m] == hash_s * current_p)
			return i - m + 1;
		current_p *= p;
	}
	return -1;
}


int KMP(string text, string pattern)
{
    text = pattern + '#' + text;
	vector<int> prefix_func (text.size(), 0);

	for (int i = 1; i < text.size(); ++i)
    {
		int j = prefix_func[i-1];
		while (j > 0 && text[i] != text[j])
        {
			j = prefix_func[j-1];
        }
		if (text[i] == text[j])
		{
            ++j;
		}
		prefix_func[i] = j;
		if(prefix_func[i] == pattern.size())
        {
            return i - 2 * pattern.size();
        }
	}
	return -1;
}

int Horspool (string text, string pattern)
{
    vector<int> skip_table (256, pattern.size());
    for(int i = 0; i < pattern.size(); ++i)
    {
        skip_table[pattern[i]] = pattern.size() - 1 - i;
    }

    for(int i = 0; i <= text.size() - pattern.size(); i += skip_table[text[i + pattern.size() - 1]])
    {
        int j = pattern.size() - 1;
        while(text[i + j] == pattern[j])
        {
            if(j == 0)
                return i;
            j--;
        }
    }
    return -1;
}

int Boyer_Moore(string text, string pattern)
{
    int n = pattern.size();
	vector<int> skip_table(n + 1, n), z_func(n, 0);
	for (int i = 1, l = 0, r = 0; i < n; ++i)
	{
		if (i <= r)
			z_func[i] = min(r - i + 1, z_func[i - l]);
		while (i + z_func[i] < n && pattern[n - 1 - z_func[i]] == pattern[n - 1 - (i + z_func[i])])
			++z_func[i];
		if (i + z_func[i] - 1 > r)
		{
			l = i;
			r = i + z_func[i] - 1;
		}
	}

	for (int i = n - 1; i > 0; --i)
		skip_table[n - z_func[i]] = i;
	for (int i = 1, r = 0; i < n; ++i)
	{
		if (i + z_func[i] == n)
		{
			for (; r <= i; ++r)
				if (skip_table[r] == n)
					skip_table[r] = i;
		}
	}

	int ans = -1;
	for (int i = 0, j = 0; i <= text.size()-n && j >= 0; i += skip_table[j + 1])
    {
		for (j = n - 1; j >= 0 && pattern[j] == text[i + j]; j--);
		if (j < 0)
			ans = i;
		if (ans >= 0)
			break;
	}

    return ans;
}


int main()
{
	string t, s;
	//cin >> t >> s;
	t = "fnfuirpnveruivnapieneirnepuin";
	s = "pie";
	cout << naive(t, s) << ' ' << Rabin_Karp(t, s) << ' '  << KMP(t,s) << ' ' << Horspool(t, s) << ' ' << Boyer_Moore(t, s) << '\n';
	s = "api";
	cout << naive(t, s) << ' ' << Rabin_Karp(t, s) << ' '  << KMP(t,s) << ' ' << Horspool(t, s) << ' ' << Boyer_Moore(t, s) << '\n';
	s = "veruivnapi";
	cout << naive(t, s) << ' ' << Rabin_Karp(t, s) << ' '  << KMP(t,s) << ' ' << Horspool(t, s) << ' ' << Boyer_Moore(t, s) << '\n';
	s = '1';
	cout << naive(t, s) << ' ' << Rabin_Karp(t, s) << ' '  << KMP(t,s) << ' ' << Horspool(t, s) << ' ' << Boyer_Moore(t, s) << '\n';
}

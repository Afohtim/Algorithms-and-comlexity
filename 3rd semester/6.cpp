#include<iostream>
#include<vector>

using namespace std;


vector<int> z_function (string s)
{
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i)
    {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}

bool solve(string t, string t1)
{
    if(t.size() != t1.size())
        return false;
    string T = t + '#' + t1 + t1;
    vector<int> c = z_function(T);
    for(auto i : c)
        if(i == t.size())
            return true;
    return false;

}

int main()
{
    cout << solve("abc", "cba") << '\n';
    cout << solve("abc", "bca") << '\n';
    cout << solve("abc", "abcd") << '\n';


}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<int> &a)
{
	for (int i : a)
		cout << i << ' ';
	cout << '\n';
}

void print(vector<pair<bool, int> > &a)
{
	for (auto i : a)
	{
		cout << i.first << ':' << i.second << ' ';
	}
	cout << '\n';
}


void down(vector<int> &a, int n, int index)
{
	int largest = index;
	int l = 2 * index + 1;
	int r = 2 * index + 2;

	if (l < n && a[l] > a[largest])
		largest = l;

	if (r < n && a[r] > a[largest])
		largest = r;

	if (largest != index)
	{
		swap(a[index], a[largest]);
		down(a, n, largest);
	}
}

void build(vector<int> &a)
{
	for (int i = a.size() / 2 - 1; i >= 0; --i)
	{
		down(a, a.size(), i);
	}
}

void heap_sort(vector<int> &a)
{
	build(a);
	for (int i = 0; i < a.size(); ++i)
	{
		swap(a[0], a[a.size() - 1 - i]);
		down(a, a.size() - i - 1, 0);
	}
}

void index_sort(vector<int> &a)
{
	if (a.size() == 0)
		return;
	int mx = a[0], mn = a[0];
	for (int i = 1; i < a.size(); ++i)
	{
		mx = max(mx, a[i]);
		mn = min(mn, a[i]);
	}
	int dist = mx - mn + 1;
	vector<int> cnt(dist, 0);
	for (int i = 0; i < a.size(); ++i)
	{
		cnt[a[i] - mn]++;
	}
	int it = 0;
	for (int i = 0; i < dist; ++i)
	{
		while (cnt[i])
		{
			a[it] = i + mn;
			it++;
			cnt[i]--;
		}
	}
}

void block_sort(vector<int> &first, int discharge = 1000)
{
	vector<vector<int>> buckets(10);

	for (int i = 0; i < int(first.size()); ++i)
	{
		buckets[(first[i] % (discharge * 10)) / discharge].push_back(first[i]);
	}

	for (int i = 0; i < int(buckets.size()) && discharge != 1; ++i)
	{
		block_sort(buckets[i], discharge / 10);
	}

	vector<int> result;

	for (int i = 0; i < int(buckets.size()); ++i)
	{
		for (int j = 0; j < int(buckets[i].size()); ++j)
		{
			result.push_back(buckets[i][j]);
		}
	}

	first = result;
}

vector<int> convert_to_int(vector<pair<bool, int> > a, int dec = 30)
{
	vector<int> res;
	for (auto i : a)
	{
		res.push_back(i.second | ((int)i.first << dec));
	}

	return res;
}

vector<pair<bool, int> > convert_to_pair(vector<int> a, int dec = 30)
{
	vector<pair<bool, int> > res;
	for (auto i : a)
	{
		res.push_back({ (int)i&(1 << dec), i - (((i&((int)1 << dec)) != 0)*(1 << dec)) });
	}
	return res;
}


void heap_sort(vector<pair<bool, int> > &a)
{
	vector<int> arr = convert_to_int(a);
	heap_sort(arr);
	a = convert_to_pair(arr);

}

void index_sort(vector<pair<bool, int> > &a)
{
	vector<int> arr = convert_to_int(a,15);
	index_sort(arr);
	a = convert_to_pair(arr,15);
}

void block_sort(vector<pair<bool, int> > &a)
{
	vector<int> arr = convert_to_int(a, 15);
	heap_sort(arr);
	a = convert_to_pair(arr, 15);
}



int main()
{
	vector<int> a = { 12, 11, 13, 5, 6, 7, 7 };
	vector<pair<bool, int> > b = { { 0,12 },{ 1,11 },{ 0,13 },{ 0,5 },{ 1,6 },{ 1,7 },{ 0,7 } };
	heap_sort(b);
	print(b);

	random_shuffle(a.begin(), a.end());
	index_sort(b);
	print(b);

	random_shuffle(a.begin(), a.end());
	block_sort(b);
	print(b);

}

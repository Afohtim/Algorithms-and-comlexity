#include <iostream>
#include <vector>

using namespace std;

class D_heap
{
private:
	vector<int> data;
	int _d;
	void down(int index)
	{
		for (int i = 1; i <= _d; ++i)
		{
			int son_index = index * _d + i;
			if (son_index >= data.size())
				break;
			if (data[son_index] > data[index])
			{
				swap(data[son_index], data[index]);
				down(son_index);
			}
		}
	}

	void up(int index)
	{
		if (index == 0)
			return;
		int parent_index = (index - 1) / _d;
		if (data[parent_index] < data[index])
		{
			swap(data[parent_index], data[index]);
			up(parent_index);
		}
	}

public:
	D_heap(int d)
	{
		_d = d;
	}
	int extract_max()
	{
		if (data.size() == 0)
			return -1;
		swap(data.front(), data.back());
		int res = data.back();
		data.pop_back();
		down(0);
		return res;

	}
	void insert(int val)
	{
		data.push_back(val);
		up(data.size() - 1);
	}
	void increase_key(int key, int val)
	{
		data[key] += val;
		if (val > 0)
			up(key);
		else
			down(key);
	}

	int size()
	{
		return data.size();
	}
};



int main()
{
	int n, d;
	cin >> n >> d;
	D_heap heap(d);
	for (int i = 0; i < n; ++i)
		heap.insert(i);
	for (int i = 0; i < n; ++i)
	{
		heap.increase_key(0, n - i);
		cout << heap.extract_max() << ' ';
	}
	system("pause");


}

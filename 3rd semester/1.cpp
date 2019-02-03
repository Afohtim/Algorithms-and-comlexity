#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <fstream>


using std::ofstream;
using std::ifstream;
using std::string;

template <typename T>
class Limited_queue
{
private:
	std::vector<T> values;
	int max_len;
public:
	Limited_queue(int max_length)
	{
		max_len = max_length;
	}

	int size()
	{
		return values.size();
	}

	bool push(int value)
	{
		if (values.size() < max_len)
		{
			values.push_back(value);
			return true;
		}
		else
		{
			return false;
		}
	}

	T pop()
	{
		T val = values.front();
		values.erase(values.begin());
		return val;
	}

	bool empty()
	{
		return values.empty();
	}

	void sort()
	{
		std::sort(values.begin(), values.end());
	}

};


void merge(ifstream &arr1_in, ifstream &arr2_in, ofstream &fout, int block1_len, int block2_len = -1)
{
	if(block2_len == -1)
	{
		block2_len = block1_len;
	}
	int ind_1 = 0, ind_2 = 0;
	int val_1, val_2;
	arr1_in >> val_1;
	arr2_in >> val_2;

	while (ind_1 < block1_len && ind_2 < block2_len)
	{
		if (val_1 < val_2)
		{
			fout << val_1 << ' ';
			ind_1++;
			if (ind_1 < block1_len)
				arr1_in >> val_1;
		}
		else
		{
			fout << val_2 << ' ';
			ind_2++;
			if (ind_2 < block2_len)
				arr2_in >> val_2;
		}
	}

	while (ind_1 < block1_len)
	{
		fout << val_1 << ' ';
		ind_1++;
		if (ind_1 < block1_len)
			arr1_in >> val_1;
	}
	while (ind_2 < block2_len)
	{
		fout << val_2 << ' ';
		ind_2++;
		if (ind_2 < block2_len)
			arr2_in >> val_2;
	}
}

void merge_sort(string file_name, string result_file_name, int memory_limit)
{
	ofstream fout("B.arr");
	fout.close();
	fout.open("A.arr");
	ifstream fin(file_name);
	bool file_switch = 0; // 0 is A, 1 is B
	Limited_queue<int> limited_queue(memory_limit);
	int val;
	int blocks = 0;
	int n = 0;
	while (fin >> val)
	{
		n++;
		if (limited_queue.size() < memory_limit)
		{
			limited_queue.push(val);
		}
		else
		{
			limited_queue.sort();
			while (!limited_queue.empty())
			{
				fout << limited_queue.pop() << ' ';
			}
			file_switch ^= 1;
			fout.close();
			blocks++;
			if (file_switch)
			{
				fout.open("B.arr", std::ios_base::app);
			}
			else
			{
				fout.open("A.arr", std::ios_base::app);
			}

			limited_queue.push(val);

		}
	}
	int extra = 0;
	limited_queue.sort();
	while (!limited_queue.empty())
	{
		extra++;
		fout << limited_queue.pop() << ' ';
	}
	fout.close();

	int block_len = memory_limit;
	file_switch = 0;
	bool file_group_switch = 0;
	ifstream arr1_in("A.arr"), arr2_in("B.arr");
	fout.open("D.arr");
	fout.close();
	fout.open("C.arr");

	while (block_len < n)
	{
		for (int i = 0; i < blocks / 2; ++i)
		{
			merge(arr1_in, arr2_in, fout, block_len);
			fout.close();
			file_switch ^= 1;
			if (file_group_switch)
			{
				if (file_switch)
				{
					fout.open("B.arr", std::ios_base::app);
				}
				else
				{
					fout.open("A.arr", std::ios_base::app);
				}
			}
			else
			{
				if (file_switch)
				{
					fout.open("D.arr", std::ios_base::app);
				}
				else
				{
					fout.open("C.arr", std::ios_base::app);
				}
			}

		}
		if (blocks & 1)
		{
			merge(arr1_in, arr2_in, fout, block_len, extra);
			extra += block_len;
		}
		else
		{
			for (int i = 0; i < extra; ++i)
			{
				int val;
				arr1_in >> val;
				fout << val << ' ';
			}
		}

		file_group_switch ^= 1;
		arr1_in.close();
		arr2_in.close();
		fout.close();
		if (file_group_switch)
		{
			arr1_in.open("C.arr");
			arr2_in.open("D.arr");
			fout.open("B.arr");
			fout.close();
			fout.open("A.arr");
		}
		else
		{
			arr1_in.open("A.arr");
			arr2_in.open("B.arr");
			fout.open("D.arr");
			fout.close();
			fout.open("C.arr");
		}

		blocks = blocks / 2;
		block_len *= 2;
	}

	fout.close();
	fout.open(result_file_name);
	while (arr1_in >> val)
	{
		fout << val << ' ';
	}
}




int main()
{
	merge_sort("mas.txt", "sorted_mas.txt", 10);
	ifstream fin("mas.txt"), fin2("sorted_mas.txt");

	int val;
	while (fin >> val)
	{
		std::cout << val << ' ';
	}
	std::cout << "\n\n\n";

	while (fin2 >> val)
	{
		std::cout << val << ' ';
	}
	system("pause");

}

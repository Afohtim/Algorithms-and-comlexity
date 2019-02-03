#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

struct Bolt
{
    int size;
    Bolt(int bolt_size) : size(bolt_size) {};
};

struct Nut
{
    int size;
    Nut(int nut_size) : size(nut_size) {};
};

int compare(Bolt bolt, Nut nut)
{
    return (bolt.size >= nut.size) - (bolt.size <= nut.size);
}

void print_arr(vector<Bolt> &bolts, vector<Nut> &nuts)
{
    cout << "Bolts:\n";
    for(int i = 0; i < bolts.size(); ++i)
    {
        cout << bolts[i].size << ' ';
    }
    cout << "\nNuts:\n";
    for(int i = 0; i < nuts.size(); ++i)
    {
        cout << nuts[i].size << ' ';
    }
    cout << '\n';
}

void nb_sort(vector<Bolt> &bolts, vector<Nut> &nuts, int left, int right)
{
    if(right < left)
        return;
    Bolt bolt_pivot = bolts[left + rand()%(right - left + 1)];
    Nut nut_pivot(0);

    int number_of_smaller_nuts = 0;
    bool nut_pivot_found = false;
    for(int i = left; i <= right; ++i)
    {
        if(compare(bolt_pivot, nuts[i]) == 1)
        {
            swap(nuts[left + number_of_smaller_nuts], nuts[i]);
            number_of_smaller_nuts++;
            if(nut_pivot_found)
            {
                swap(nuts[left + number_of_smaller_nuts], nuts[i]);
            }
        }
        if(compare(bolt_pivot, nuts[i]) == 0)
        {
            nut_pivot = nuts[i];
            nut_pivot_found = true;
            swap(nuts[left + number_of_smaller_nuts], nuts[i]);
        }
    }

    int number_of_smaller_bolts = 0;
    bool bolt_pivot_found = false;
    for(int i = left; i <= right; ++i)
    {
        if(compare(bolts[i], nut_pivot) == -1)
        {
            swap(bolts[left + number_of_smaller_bolts], bolts[i]);
            number_of_smaller_bolts++;
            if(bolt_pivot_found)
            {
                swap(bolts[left + number_of_smaller_bolts], bolts[i]);
            }
        }
        if(compare(bolts[i], nut_pivot) == 0)
        {
            bolt_pivot_found = true;
            swap(bolts[left + number_of_smaller_bolts], bolts[i]);
        }
    }
    nb_sort(bolts, nuts, left, left + number_of_smaller_bolts - 1);
    nb_sort(bolts, nuts, left + number_of_smaller_bolts + 1, right);
}


int main()
{
    srand (time(NULL));
    int n = 10;
    vector<Nut> nuts;
    vector<Bolt> bolts;
    for(int i = 0; i < n; ++i)
    {
        nuts.push_back(Nut(i));
        bolts.push_back(Bolt(i));
    }
    random_shuffle(nuts.begin(), nuts.end());
    random_shuffle(bolts.begin(), bolts.end());

    print_arr(bolts, nuts);

    nb_sort(bolts, nuts, 0, n - 1);

    print_arr(bolts, nuts);



}

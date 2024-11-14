// generator.cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <random>

using namespace std;
struct Generator
{
    virtual vector<int> generateVec(const int count) const
    {
        vector<int> result(count);
        generate(result.begin(), result.end(),[&]() { return 1 + rand()%9; });
        return result;
    }
};

struct Splitter // splits the matrix into rows, columns and diagonals
{
    vector<vector<int>> split(vector<vector<int>> array) const
    {
    // implementation omitted
    }
};

struct Verifier
{
    bool verify(vector<vector<int>> array) const // matrix as input
    {
        if (array.empty()) return false;
        auto expected = accumulate(array[0].begin(),array[0].end(), 0);
        return all_of(array.begin(), array.end(), [=](auto& inner)
            {return accumulate(inner.begin(), inner.end(), 0) == expected;});
    }
};
struct MagicSquareGenerator // Façade
{
    vector<vector<int>> generate(int size)
    {
        Generator g;
        Splitter s;
        Verifier v;
        vector<vector<int>> square;
        do // generate square
        {
            square.clear();
            for (int i = 0; i < size; ++i)
                square.emplace_back(g.generateVec(size)); // generate individual rows
        } while (!v.verify(s.split(square))); // verify and split
        return square;
    }
};

main()
{
    Generator g;
    vector<int> v = g.generateVec(10);
    for (auto i : v)
        cout << i << " ";
    cout << endl;
}
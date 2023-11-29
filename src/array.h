#pragma once

#include <vector>

class Array
{
public:
    Array(int size);

    void swap(size_t i, size_t j);
    void shuffle();
    const std::vector<int> &getData();

private:
    std::vector<int> data;
};

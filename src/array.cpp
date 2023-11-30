#include "array.h"
#include <algorithm>
#include <numeric>
#include <random>

Array::Array(int size) {
    data.resize(size);
    shuffle();
}

void Array::shuffle() {
    std::iota(data.begin(), data.end(), 1); 
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);
}

void Array::swap(size_t i, size_t j) {
    std::swap(data[i], data[j]);
}

const std::vector<int>& Array::getData() {
    return data;
}
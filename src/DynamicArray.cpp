#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>

using namespace std;

bool DynamicArray::isValueInRange(int value) {
    return value >= MIN_VALUE && value <= MAX_VALUE;
}

bool DynamicArray::isIndexValid(int index) {
    return index >= 0 && index < size;
}

DynamicArray::DynamicArray(int size) {
    if (size < 0) {
        throw invalid_argument("size cannot be negative");
    }
    this->size = size;
    data = new int[this->size];
    for (int i = 0; i < this->size; ++i) {
        data[i] = 0;
    }
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::print() {
    cout << "[";
    for (int i = 0; i < size; ++i) {
        cout << data[i];
        if (i != size - 1) {
            cout << ", ";
        }
    }
    cout << "]\n";
}

void DynamicArray::set(int index, int value) {
    if (!isIndexValid(index)) {
        throw out_of_range("index " + to_string(index) + " is out of bounds");
    }
    if (!isValueInRange(value)) {
        throw invalid_argument("value " + to_string(value) + " is out of range [-100, 100]");
    }
    data[index] = value;
}

int DynamicArray::get(int index) {
    if (!isIndexValid(index)) {
        throw out_of_range("index " + to_string(index) + " is out of bounds");
    }
    return data[index];
}
 
DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

void DynamicArray::pushBack(int value) {
    if (!isValueInRange(value)) {
        throw invalid_argument("value " + to_string(value) + " is out of range [-100, 100]");
    }

    int* newData = new int[size + 1];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    newData[size] = value;
    delete[] data;

    data = newData;
    size = size + 1;
}

void DynamicArray::add(const DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        int otherValue = (i < other.size) ? other.data[i] : 0;
        data[i] = data[i] + otherValue;
    }
}

void DynamicArray::subtract(const DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        int otherValue = (i < other.size) ? other.data[i] : 0;
        data[i] = data[i] - otherValue;
    }
}
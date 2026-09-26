#pragma once

class DynamicArray {
private:
    int* data;
    int size;

    static const int MIN_VALUE = -100;
    static const int MAX_VALUE = 100;

    static bool isValueInRange(int value);
    bool isIndexValid(int index);
public:
    explicit DynamicArray (int size);
    ~DynamicArray();
    void print();
    void set(int index, int value);
    int get(int index);

    DynamicArray(const DynamicArray&);

    void pushBack(int value);

    void add(const DynamicArray& other);
    void subtract(const DynamicArray& other);
};
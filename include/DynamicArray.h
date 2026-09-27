#pragma once
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <cmath>
 
using namespace std;
 
template <class T>
class DynamicArray {
private:
    T* data;
    int size;
    static const int MIN_VALUE = -100;
    static const int MAX_VALUE = 100;
 
    static bool isValueInRange(const T& value) {
        if constexpr (is_integral_v<T>) {
            return value >= MIN_VALUE && value <= MAX_VALUE;
        } else {
            return true;
        }
    }
 
    bool isIndexValid(int index) const {
        return index >= 0 && index < size;
    }
 
public:
    explicit DynamicArray (int size) {
        if (size < 0) {
            throw invalid_argument("size cannot be negative");
        }
        this->size = size;
        data = new T[this->size]();
    }
 
    ~DynamicArray() {
        delete[] data;
    }
 
    void print() {
        cout << "[";
        for (int i = 0; i < size; ++i) {
            cout << data[i];
            if (i != size - 1) {
                cout << ", ";
            }
        }
        cout << "]\n";
    }
 
    void set(int index, const T& value) {
        if (!isIndexValid(index)) {
            throw out_of_range("index " + to_string(index) + " is out of bounds");
        }
        data[index] = value;
    }
 
 
    // Отдельный сеттер с проверкой
    void setChecked(int index, const T& value) {
        if constexpr (is_integral_v<T>) {
            if (!isIndexValid(index)) {
                throw out_of_range("index " + to_string(index) + " is out of bounds");
            }
            if (!isValueInRange(value)) {
                throw invalid_argument("value is out of range [-100, 100]");
            }
            data[index] = value;
        } else {
            static_assert(std::is_integral_v<T>, "setChecked() is only available for integral element types");
        }
    }
 
    T get(int index) const {
        if (!isIndexValid(index)) {
            throw out_of_range("index " + to_string(index) + " is out of bounds");
        }
        return data[index];
    }
 
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
 
    void pushBack(const T& value) {
        if (!isValueInRange(value)) {
            throw invalid_argument("value is out of range [-100, 100]");
        }
        T* newData = new T[size + 1];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        newData[size] = value;
        delete[] data;
        data = newData;
        size = size + 1;
    }
 
    void add(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T otherValue = (i < other.size) ? other.data[i] : T();
            data[i] = data[i] + otherValue;
        }
    }
    
    void sub(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T otherValue = (i < other.size) ? other.data[i] : T();
            data[i] = data[i] - otherValue;
        }
    }
 
    int getSize() const {
        return size;
    }
};
 
template <typename T>
ostream& operator<<(ostream& stream, const DynamicArray<T>& arr) {
    stream << "[";
    for (int i = 0; i < arr.getSize(); ++i) {
        stream << arr.get(i);
        if (i != arr.getSize() - 1) {
            stream << ", ";
        }
    }
    stream << "]";
    return stream;
}

template <typename T>
double distance(const DynamicArray<T>& a, const DynamicArray<T>& b) {
    if constexpr (!is_arithmetic_v<T>) {
        throw bad_typeid();
    } else {
        if (a.getSize() != b.getSize()) {
            throw invalid_argument("arrays must have the same size");
        }
        double sum = 0.0;
        for (int i = 0; i < a.getSize(); i++) {
            double diff = static_cast<double>(a.get(i)) - static_cast<double>(b.get(i));
            sum += diff * diff;
        }
        return sqrt(sum);
    }
}
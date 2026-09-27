#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

int main() {
    cout << "Part 1: basic operations (DynamicArray<int>)\n";
    int size = 5, sizeA = 4, sizeB = 6;
 
    cout << "Task 1\n";
    cout << "Let's take an array of size 5.\n";
    DynamicArray<int> arr(size);
    cout << "New array: " << arr << "\n";
 
    for (int i = 0; i < size; ++i) {
        arr.set(i, (i + 1) * 10);
    }
    cout << "After completion: " << arr << "\n";
    cout << "arr.get(2) = " << arr.get(2) << "\n";
 
    cout << "Task 2\n";
    DynamicArray<int> copyArr(arr);
    cout << "Copy of the array: " << copyArr << "\n";
    copyArr.set(0, 999 % 101); // меняем копию, чтобы показать независимость
    cout << "The original has not changed: " << arr << "\n";
    cout << "Modified copy: " << copyArr << "\n";
    cout << "\n";
 
    cout << "Task 3\n";
    cout << "Before pushBack: " << arr << "\n";
    arr.pushBack(77);
    cout << "After pushBack(77): " << arr << "\n";
    cout << "\n";
 
    cout << "Task 4\n";
    cout << "Let's take 2 arrays of sizes 4 and 6.\n";
    DynamicArray<int> arrA(sizeA);
    DynamicArray<int> arrB(sizeB);
 
    for (int i = 0; i < sizeA; i++) arrA.set(i, 10);
    for (int i = 0; i < sizeB; i++) arrB.set(i, i + 1);
    cout << "arrA: " << arrA << "\n";
    cout << "arrB: " << arrB << "\n";
 
    arrA.add(arrB);
    cout << "arrA.add(arrB): " << arrA << "\n";
    cout << "The size of arrA has not changed, size = " << arrA.getSize() << "\n";
    arrA.sub(arrB);
    cout << "arrA.sub(arrB): " << arrA << "\n";
    cout << "\n";
 
    cout << "Part 2: exceptions\n";
    cout << "std::out_of_range (index out of bounds)\n";
    try {
        arr.get(100);
    } catch (const out_of_range& e) {
        cout << "Caught std::out_of_range: " << e.what() << "\n";
    }
 
    cout << "std::invalid_argument (setChecked: value outside [-100, 100])\n";
    try {
        arr.setChecked(0, 500);
    } catch (const invalid_argument& e) {
        cout << "Caught std::invalid_argument: " << e.what() << "\n";
    }
 
    cout << "std::bad_alloc (allocation failure)\n";
    try {
        size_t hugeElem = (static_cast<size_t>(1) << 50);
        int* raw = new int[hugeElem];
        delete[] raw;
    } catch (const bad_alloc& e) {
        cout << "Caught std::bad_alloc " << e.what() << "\n";
    }
    cout << "\n";
 
    cout << "Part 3: templates\n";
    cout << "Task 1\n";
    cout << "Array of integers:\n";
    DynamicArray<int> ints(3);
    ints.setChecked(0, 10); // отдельный сеттер с проверкой
    ints.setChecked(1, 20);
    ints.setChecked(2, 30);
    cout << "ints: " << ints << "\n";

    cout << "Array of strings:\n";
    DynamicArray<string> strings(3);
    strings.set(0, "hello");
    strings.set(1, "dynamic");
    strings.set(2, "array");
    strings.pushBack("templates");
    cout << "strings: " << strings << "\n";
    cout << "\n";
 
    cout << "Task 2: custom operator <<\n";
    cout << "ints: " << ints << "\n";
    cout << "strings: " << strings << "\n";
    cout << "\n";
 
    cout << "Task 3\n";
    DynamicArray<int> p1(3);
    p1.set(0, 0); p1.set(1, 0); p1.set(2, 0);
    DynamicArray<int> p2(3);
    p2.set(0, 3); p2.set(1, 4); p2.set(2, 0);
    cout << "p1 = " << p1 << ", p2 = " << p2 << "\n";
    cout << "distance(p1, p2) = " << distance(p1, p2) << " (expect 5)\n";
 
    cout << "\nstd::invalid_argument (different array sizes)\n";
    DynamicArray<int> p3(2);
    p3.set(0, 1); p3.set(1, 1);
    try {
        distance(p1, p3);
    } catch (const invalid_argument& e) {
        cout << "Caught std::invalid_argument: " << e.what() << "\n";
    }
 
    cout << "\nstd::bad_typeid (non-numeric type T = std::string)\n";
    DynamicArray<string> s1(2);
    s1.set(0, "a"); s1.set(1, "b");
    DynamicArray<string> s2(2);
    s2.set(0, "c"); s2.set(1, "d");
    try {
        distance(s1, s2);
    } catch (const bad_typeid& e) {
        cout << "Caught std::bad_typeid: " << e.what() << "\n";
    }

    return 0;
}
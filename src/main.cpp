#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

int main() {

    cout << "Part 1\n";
    int size = 5, sizeA = 4, sizeB = 6;
    cout << "Task 1\n";
    cout << "Let's take an array of size 5.\n";
    DynamicArray arr(size);
    cout << "New array: ";
    arr.print();

    for (int i = 0; i < size; ++i) {
        arr.set(i, (i + 1) * 10);
    }
    cout << "After completion: ";
    arr.print();
    cout << "arr.get(2) = " << arr.get(2) << "\n";

    std::cout << "Task 2\n";
    DynamicArray copyArr(arr);
    cout << "Copy of the array: ";
    copyArr.print();
    copyArr.set(0, 999 % 101); // меняем копию, чтобы показать независимость
    cout << "The original has not changed: ";
    arr.print();
    cout << "Modified copy: ";
    copyArr.print();
    cout << "\n";

    cout << "Task 3\n";
    cout << "Before pushBack: ";
    arr.print();
    arr.pushBack(77);
    cout << "After pushBack(77): ";
    arr.print();
    cout << "\n";

    cout << "Task 4\n";
    cout << "Let's take 2 arrays of sizes 4 and 6.\n";
    DynamicArray arrA(sizeA);
    DynamicArray arrB(sizeB);

    for (int i = 0; i < sizeA; ++i) arrA.set(i, 10);
    for (int i = 0; i < sizeB; ++i) arrB.set(i, i + 1);
    cout << "arrA: "; arrA.print();
    cout << "arrB: "; arrB.print();

    arrA.add(arrB);
    cout << "arrA.add(arrB): "; arrA.print();
    cout << "The size of arrA has not changed, size = " << sizeA << "\n";
    arrA.subtract(arrB);
    cout << "arrA.subtract(arrB): "; arrA.print();
    cout << "\n";

    cout << "Part 2\n";
    cout << "std::out_of_range (index out of bounds)\n";
    try {
        arr.get(100);
    } catch (const out_of_range& e) {
        cout << "Caught std::out_of_range: " << e.what() << "\n";
    }
    
    cout << "std::invalid_argument (value outside [-100, 100])\n";
    try {
        arr.set(0, 500);
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

    return 0;
}
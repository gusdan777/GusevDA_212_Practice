#include "DynamicArray.h"
#include <iostream>

using namespace std;

int main() {
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

    cout << "Error check:\n";
    arr.set(size + 1, 5);
    arr.set(0, 500);
    arr.get(-1);
    cout << "\n";

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
    arr.pushBack(1000);
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
    std::cout << "arrA.add(arrB): "; arrA.print();
    std::cout << "The size of arrA has not changed, size = " << sizeA << "\n";
    arrA.subtract(arrB);
    std::cout << "arrA.subtract(arrB): "; arrA.print();

    return 0;
}
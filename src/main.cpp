#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// принимает массив по значению (при передаче создаётся копия или происходит перенос)
void takeByValue(DynamicArray<int> a) {
    cout << "  inside function: " << a << ", data address = " << static_cast<const void*>(a.begin()) << "\n";
}

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
#ifdef __SANITIZE_ADDRESS__
    // AddressSanitizer не выбрасывает bad_alloc, а завершает программу, поэтому при -fsanitize=address пропускаем
    cout << "Skipped: AddressSanitizer build (it aborts on huge allocations instead of throwing)\n";
#else
    try {
        size_t hugeElem = (static_cast<size_t>(1) << 50);
        int* raw = new int[hugeElem];
        delete[] raw;
    } catch (const bad_alloc& e) {
        cout << "Caught std::bad_alloc " << e.what() << "\n";
    }
#endif
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
    cout << "\n";

    cout << "Part 4: operators\n";
    cout << boolalpha; // чтобы bool выводился как true/false

    cout << "Task 1: operator[]\n";
    DynamicArray<int> a4(5);
    for (int i = 0; i < 5; i++) {
        a4[i] = (i + 1) * 10;
    }
    cout << "a4 after a4[i] = (i + 1) * 10: " << a4 << "\n";
    cout << "a4[2] = " << a4[2] << "\n";
    a4[2] = 99;
    cout << "After a4[2] = 99: " << a4 << "\n";
    strings[0] = "world";
    cout << "strings[0] = \"world\": " << strings << "\n";

    cout << "std::out_of_range (operator[])\n";
    try {
        a4[10] = 1;
    } catch (const out_of_range& e) {
        cout << "Caught std::out_of_range: " << e.what() << "\n";
    }
    try {
        cout << a4[-1] << "\n";
    } catch (const out_of_range& e) {
        cout << "Caught std::out_of_range: " << e.what() << "\n";
    }
    cout << "\n";

    cout << "Task 2: operator== and operator!=\n";
    DynamicArray<int> e1(3);
    DynamicArray<int> e2(3);
    DynamicArray<int> e3(4);
    for (int i = 0; i < 3; i++) {
        e1[i] = i + 1;
        e2[i] = i + 1;
    }
    for (int i = 0; i < 4; i++) {
        e3[i] = i + 1;
    }
    cout << "e1 = " << e1 << ", e2 = " << e2 << ", e3 = " << e3 << "\n";
    cout << "e1 == e2: " << (e1 == e2) << "\n";
    cout << "e1 != e2: " << (e1 != e2) << "\n";
    cout << "e1 == e3 (different sizes): " << (e1 == e3) << "\n";
    cout << "e1 != e3: " << (e1 != e3) << "\n";
    e2[0] = 50;
    cout << "After e2[0] = 50, e2 = " << e2 << "\n";
    cout << "e1 == e2: " << (e1 == e2) << "\n";
    cout << "e1 != e2: " << (e1 != e2) << "\n";
    cout << "\n";

    cout << "Task 3: operator+= and operator-=\n";
    DynamicArray<int> x(4);
    DynamicArray<int> y(6);
    for (int i = 0; i < 4; i++) x[i] = 10;
    for (int i = 0; i < 6; i++) y[i] = i + 1;
    cout << "x = " << x << ", y = " << y << "\n";

    x += y;
    cout << "x += y: " << x << " (size " << x.getSize() << ", extra elements of y ignored)\n";
    x -= y;
    cout << "x -= y: " << x << "\n";

    y += x;
    cout << "y += x: " << y << " (size " << y.getSize() << ", missing elements of x are zeros)\n";
    y -= x;
    cout << "y -= x: " << y << "\n";

    x += 5;
    cout << "x += 5: " << x << "\n";
    x -= 3;
    cout << "x -= 3: " << x << "\n";

    DynamicArray<string> words(2);
    words[0] = "ab";
    words[1] = "cd";
    words += string("!");
    cout << "words += \"!\": " << words << "\n";
    cout << "\n";

    cout << "Task 4: begin() and end()\n";
    DynamicArray<int> it(5);
    for (int i = 0; i < 5; i++) it[i] = i + 1;
    cout << "it: " << it << "\n";

    cout << "for (const auto& v : it): ";
    for (const auto& v : it) {
        cout << v << " ";
    }
    cout << "\n";

    for (auto& v : it) {
        v = v * 2; // меняем элементы прямо в цикле
    }
    cout << "After for (auto& v : it) v = v * 2: " << it << "\n";

    cout << "for (const auto& w : words): ";
    for (const auto& w : words) {
        cout << w << " ";
    }
    cout << "\n";

    DynamicArray<int> empty(0);
    cout << "Empty array loop (nothing should be printed): ";
    for (const auto& v : empty) {
        cout << v << " ";
    }
    cout << "\n";

    cout << "\n";
    cout << "Part 5: rule of five\n";
    cout << "Task 1: operator=\n";
    DynamicArray<int> r1(3);
    DynamicArray<int> r2(5);
    for (int i = 0; i < 3; i++) r1[i] = i + 1;
    for (int i = 0; i < 5; i++) r2[i] = 10;
    cout << "r1 = " << r1 << ", r2 = " << r2 << "\n";
    r2 = r1;
    cout << "After r2 = r1: r2 = " << r2 << "\n";
    r1[0] = 99;
    cout << "After r1[0] = 99: r1 = " << r1 << ", r2 = " << r2 << " (r2 did not change)\n";
    r2 = r2;
    cout << "After r2 = r2: " << r2 << " (self-assignment is safe)\n";
    DynamicArray<int> r3(1);
    r3 = r2 = r1;
    cout << "After r3 = r2 = r1: r3 = " << r3 << "\n";
    cout << "\n";

    cout << "Task 2: move constructor\n";
    cout << "r1 = " << r1 << ", data address = " << static_cast<const void*>(r1.begin()) << "\n";
    DynamicArray<int> moved(move(r1));
    cout << "After DynamicArray moved(std::move(r1)):\n";
    cout << "  moved = " << moved << ", data address = " << static_cast<const void*>(moved.begin()) << "\n";
    cout << "  r1 size = " << r1.getSize() << " (source is empty)\n";
    cout << "\n";

    cout << "Task 3: move assignment\n";
    DynamicArray<int> target(2);
    target[0] = 7;
    target[1] = 8;
    cout << "target = " << target << "\n";
    target = move(moved);
    cout << "After target = std::move(moved): target = " << target << "\n";
    cout << "  moved size = " << moved.getSize() << " (source is empty)\n";
    DynamicArray<int>& same = target; // вторая ссылка на тот же массив
    target = move(same);
    cout << "After self-move: target = " << target << " (data is not lost)\n";
    cout << "\n";

    cout << "Task 4: copy and move\n";
    DynamicArray<int> big(5);
    for (int i = 0; i < 5; i++) big[i] = i + 1;
    cout << "big = " << big << ", data address = " << static_cast<const void*>(big.begin()) << "\n";

    cout << "Before move (copy constructor):\n";
    takeByValue(big);
    cout << "  big after the call: " << big << " (the address inside is different: data was copied)\n";

    cout << "After move (move constructor):\n";
    takeByValue(move(big));
    cout << "  big after the call: size = " << big.getSize() << " (the address inside is the same: data was moved)\n";

    cout << "Container: vector\n";
    DynamicArray<int> item(3);
    for (int i = 0; i < 3; i++) item[i] = i + 1;
    cout << "item = " << item << ", data address = " << static_cast<const void*>(item.begin()) << "\n";

    vector<DynamicArray<int>> v;
    v.push_back(item); // копия
    cout << "push_back(item): v[0] address = " << static_cast<const void*>(v[0].begin())
         << ", item = " << item << " (data was copied)\n";
    v.push_back(move(item)); // перенос
    cout << "push_back(std::move(item)): v[1] address = " << static_cast<const void*>(v[1].begin())
         << ", item size = " << item.getSize() << " (data was moved)\n";

    return 0;
}
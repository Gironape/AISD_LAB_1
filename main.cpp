#include <iostream>
#include "myset.h"
#include <ctime>
#include <set>
double test_insert1(int size) {
    myset a;
    double ans = 0;
    for (int t = 0; t < 100; ++t) {
        double st = clock();
        for (int i = 0; i < size; ++i) {
            a.insert(rand() % 100000);
        }
        ans += clock() - st;
    }
    return ans / 100.0;
}
double test_insert2(int size) {
    std::set<int>a;
    double ans = 0;
    for (int t = 0; t < 100; ++t) {
        double st = clock();
        for (int i = 0; i < size; ++i) {
            a.insert(rand() % 100000);
        }
        ans += clock() - st;
    }
    return ans / 100.0;
}
double test_find1(int size) {
    myset a;
    for (int i = 0; i < size; ++i) a.insert(rand() % 100000);
    double ans = 0;
    for (int t = 0; t < 100; ++t) {
        double st = clock();
        a.contains(rand() % 100000);
        ans += clock() - st;
    }
    return ans / 100.0;
}
double test_find2(int size) {
    std::set<int> a;
    for (int i = 0; i < size; ++i) a.insert(rand() % 100000);
    double ans = 0;
    for (int t = 0; t < 100; ++t) {
        double st = clock();
        a.count(rand() % 100000);
        ans += clock() - st;
    }
    return ans / 100.0;
}
double test_ins_er1(int size) {
    myset a;
    for (int i = 0; i < size; ++i) {
        a.insert(i % size);
    }
    double ans = 0;
    for (int t = 0; t < 100; ++t) {
        double st = clock();
        int ins = rand() % 50000;
        a.insert(ins);
        a.erase(ins);
        ans += clock() - st;
    }
    return ans / 100.0;
}
double test_ins_er2(int size) {
    std::set<int> a;
    for (int i = 0; i < size; ++i) a.insert(rand() % size);
    double ans = 0;
    for (int t = 0; t < 100; ++t) {
        double st = clock();
        int ins = rand() % 50000;
        a.insert(ins);
        a.erase(ins);
        ans += clock() - st;
    }
    return ans / 100.0;
}
int main(int argc, const char* argv[]) {
    for (int i = 1000; i <= 100000; i *= 10) {
        std::cout << i << "\n";
        std::cout << "insert:\n";
        std::cout << "myset: " << test_insert1(i) << "\n";
        std::cout << "std::set: " << test_insert2(i) << "\n";
        std::cout << "find:\n";
        std::cout << "myset: " << test_find1(i) << "\n";
        std::cout << "std::set: " << test_find2(i) << "\n";
        std::cout << "insert+erase:\n";
        std::cout << "myset: " << test_ins_er1(i) << "\n";
        std::cout << "std::set: " << test_ins_er2(i) << "\n";
    }
    //std::cout<<"1\n";
}

}
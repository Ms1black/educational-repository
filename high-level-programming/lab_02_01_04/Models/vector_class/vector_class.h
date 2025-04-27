#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class MyVector {
private:
    T* data;
    int capacity;
    int length;

    void resize(int new_capacity) {
        T* new_data = new T[new_capacity];
        for (int i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    MyVector() : data(nullptr), capacity(0), length(0) {
        resize(4);
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (length >= capacity) resize(capacity * 2);
        data[length++] = value;
    }

    void removeAt(int index) {
        if (index < 0 || index >= length) throw std::out_of_range("Invalid index");
        for (int i = index; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        --length;
    }

    T& operator[](int index) {
        if (index < 0 || index >= length) throw std::out_of_range("Invalid index");
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= length) throw std::out_of_range("Invalid index");
        return data[index];
    }

    int size() const {
        return length;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        length = 0;
        capacity = 0;
        resize(4);
    }

    void sort(bool (*comp)(const T&, const T&)) {
        for (int i = 0; i < length - 1; ++i) {
            for (int j = i + 1; j < length; ++j) {
                if (comp(data[j], data[i])) {
                    std::swap(data[i], data[j]);
                }
            }
        }
    }

    MyVector<T> filter(bool (*predicate)(const T&)) const {
        MyVector<T> result;
        for (int i = 0; i < length; ++i) {
            if (predicate(data[i])) {
                result.push_back(data[i]);
            }
        }
        return result;
    }

    void printAll(void (*printer)(const T&)) const {
        for (int i = 0; i < length; ++i) {
            printer(data[i]);
        }
    }
};

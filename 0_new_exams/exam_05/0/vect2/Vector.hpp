#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>

// Minimal vector-like template class

template <typename T>
class Vector {
private:
    T* data;
    size_t sz;

public:
    Vector() : data(nullptr), sz(0) {}

    Vector(const Vector& other) : data(nullptr), sz(other.sz) {
        if (sz) {
            data = new T[sz];
            for (size_t i = 0; i < sz; ++i)
                data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            sz = other.sz;
            data = sz ? new T[sz] : nullptr;
            for (size_t i = 0; i < sz; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~Vector() { delete[] data; }

    size_t size() const { return sz; }

    bool empty() const { return sz == 0; }

    void push_back(const T& value) {
        T* new_data = new T[sz + 1];
        for (size_t i = 0; i < sz; ++i)
            new_data[i] = data[i];
        new_data[sz] = value;
        delete[] data;
        data = new_data;
        ++sz;
    }

    void pop_back() {
        if (sz == 0)
            return;
        if (sz == 1) {
            delete[] data;
            data = nullptr;
            sz = 0;
            return;
        }
        T* new_data = new T[sz - 1];
        for (size_t i = 0; i < sz - 1; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        --sz;
    }

    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    T* begin() { return data; }
    T* end() { return data + sz; }
    const T* begin() const { return data; }
    const T* end() const { return data + sz; }
};

#endif // VECTOR_HPP

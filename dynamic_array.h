#pragma once

template<typename T>
class DynamicArray {
public:
    DynamicArray()
        : data(nullptr)
        , size(0) {}

    DynamicArray(const DynamicArray<T>& other) {
        data = new T[other.size];
        size = other.size;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    DynamicArray(T* items, int count) {
        data = new T[count];
        for (int i = 0; i < count; i++) {
            data[i] = items[i];
        }
    }

    DynamicArray(size_t size) : size(size) {
        if (size == 0) {
            data = nullptr;
            return;
        }
        data = new T[size]();
    }

    DynamicArray& operator=(const DynamicArray<T>& other) {
        if (this == &other) {
            return *this;
        }
        if (data) {
            delete[]data;
        }

        data = new T[other.size];
        size = other.size;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    void Resize(size_t new_size) {
        if (new_size == size) return;
        T* new_data = new T[new_size];
        if (new_size > size) {
            for (int i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
        }
        else {
            for (int i = 0; i < new_size; i++) {
                new_data[i] = data[i];
            }  
        }
            

        delete[] data;
        data = new_data;
        size = new_size;
    }

    size_t GetSize() {
        return size;
    }

    void Set(const T& object, size_t index) {
        if (index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        data[index] = object;
    }

    T Get(size_t index) {
        if (index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return data[index];
    }


private:
    T* data;
    size_t size;
};
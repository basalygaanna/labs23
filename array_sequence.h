#pragma once
#include "dynamic_array.h"
#include "sequence.h"


// Предварительное объявление
template<typename T> class ImmutableArraySequence;
template<typename T> class MutableArraySequence;

template<typename T>
class ArraySequence : public Sequence<T> {
protected:
    virtual ArraySequence<T>* AppendInternal(T item) {
        size_t size = array->GetSize();
        array->Resize(size + 1);
        array->Set(item, size);

        return this;
    };

    virtual ArraySequence<T>* PrependInternal(T item) {
        size_t size = array->GetSize();
        array->Resize(size + 1);
        for (int i = size - 1; i >= 0; i--) {
            array->Set(array->Get(i), i + 1);
        }
        array->Set(item, 0);

        return this;
    };

    virtual ArraySequence<T>* InsertAtInternal(T item, int index) {
        size_t size = array->GetSize();
        array->Resize(size + 1);
        for (int i = size - 1; i >= index; i--) {
            array->Set(array->Get(i), i + 1);
        }
        array->Set(item, index);

        return this;
    };

    virtual ArraySequence<T>* Instance() const = 0;

    DynamicArray<T>* array;

public:
    virtual ArraySequence<T>* Clone() const = 0;

    ArraySequence() : array(new DynamicArray<T>()) {}

    ArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}

    ArraySequence(const DynamicArray <T>& other) : array(new DynamicArray<T>(other)) {}

    T GetFirst() const override {
        if (!array) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return array->Get(0);
    }

    T GetLast() const override {
        if (!array) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return array->Get(array->GetSize() - 1);
    }

    T Get(int index) const override {
        return array->Get(index);
    }

    void Set(T item, int index) {
        return array->Set(item, index);
    }

    ArraySequence<T>* Append(T item) override {
        return Instance()->AppendInternal(item);
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 || endIndex >= array->GetSize() || startIndex >= array->GetSize() || startIndex > endIndex) {
            throw std::out_of_range("IndexOutOfRange");
        }

        DynamicArray<T>* subarray = new DynamicArray<T>(endIndex - startIndex + 1);

        for (int i = startIndex; i <= endIndex; ++i) {
            subarray->Set(array->Get(i), i - startIndex);
        }

        if (dynamic_cast<const MutableArraySequence<T>*>(this)) {
            return new MutableArraySequence<T>(*subarray);
        }
        else {
            return new ImmutableArraySequence<T>(*subarray);
        }

        delete subarray;
    }

    int GetLength() const override {
        return array->GetSize();
    }

    ArraySequence<T>* Prepend(T item) override {
        return Instance()->PrependInternal(item);
    }

    ArraySequence<T>* Concat(Sequence<T>* other) override {
        int size = other->GetLength();
        ArraySequence<T>* new_arr = dynamic_cast<ArraySequence<T>*>(this->Clone());
        for (int i = 0; i < size; ++i) {
            new_arr->AppendInternal(other->Get(i));
        }
        return new_arr;
    }

    ArraySequence<T>* InsertAt(T item, int index) override {
        if (index >= this->GetLength() || index < 0) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return Instance()->InsertAtInternal(item, index);
    }

};

template<typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}

    ArraySequence<T>* Instance() const override {
        return const_cast<MutableArraySequence<T>*>(this);
    }

    ArraySequence<T>* Clone() const override {
        return new MutableArraySequence<T>(*this->array);
    }
};

template<typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}

    ArraySequence<T>* Instance() const override {
        return Clone();
    }

    ArraySequence<T>* Clone() const override {
        return new ImmutableArraySequence<T>(*this->array);
    }
};
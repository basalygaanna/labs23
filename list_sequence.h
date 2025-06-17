#pragma once
#include "linked_list.h"
#include "sequence.h"

// Предварительное объявление
template<typename T> class ImmutableListSequence;
template<typename T> class MutableListSequence;

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    virtual ListSequence<T>* AppendInternal(T item) {
        this->list->Append(item);
        return this;
    };

    virtual ListSequence<T>* PrependInternal(T item) {
        this->list->Prepend(item);
        return this;
    };

    virtual ListSequence<T>* InsertAtInternal(T item, int index) {
        this->list->InsertAt(item, index);
        return this;
    };

    virtual ListSequence<T>* Instance() const = 0;

    LinkedList<T>* list;

public:
    virtual ListSequence<T>* Clone() const = 0;

    ListSequence() : list(new LinkedList<T>()) {}

    ListSequence(T* items, int count) : list(new LinkedList<T>(items, count)) {}

    ListSequence(const LinkedList <T>& other) : list(new LinkedList<T>(other)) {}

    T GetFirst() const override {
        if (!list) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return list->GetFirst();
    }

    T GetLast() const override {
        if (!list) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return list->GetLast();
    }

    T Get(int index) const override {
        return list->Get(index);
    }

    ListSequence<T>* Append(T item) override {
        return Instance()->AppendInternal(item);
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 || startIndex >= list->GetLength() || endIndex >= list->GetLength() || startIndex > endIndex) {
            throw std::out_of_range("IndexOutOfRange");
        }
        LinkedList<T>* subList = list->GetSubList(startIndex, endIndex);
        ListSequence<T>* new_list;
        if (dynamic_cast<const ImmutableListSequence<T>*>(this)) {
            new_list = new ImmutableListSequence<T>(*subList);
        }
        else {
            new_list = new MutableListSequence<T>(*subList);
        }

        delete subList;
        return new_list;
    }

    int GetLength() const override {
        return list->GetLength();
    }

    ListSequence<T>* Prepend(T item) override {
        return Instance()->PrependInternal(item);
    }

    ListSequence<T>* Concat(Sequence<T>* other) override {
        int size = other->GetLength();
        ListSequence<T>* new_list = dynamic_cast<ListSequence<T>*>(this->Clone());
        for (int i = 0; i < size; ++i) {
            new_list->AppendInternal(other->Get(i));
        }
        return new_list;
    }

    ListSequence<T>* InsertAt(T item, int index) override {
        if (index >= this->GetLength() || index < 0) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return Instance()->InsertAtInternal(item, index);
    }
};

template<typename T>
class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}

    ListSequence<T>* Instance() const override {
        return const_cast<MutableListSequence<T>*>(this);
    }

    ListSequence<T>* Clone() const override {
        return new MutableListSequence<T>(*this->list);
    }
};

template<typename T>
class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}

    ListSequence<T>* Instance() const override {
        return Clone();
    }

    ListSequence<T>* Clone() const override {
        return new ImmutableListSequence<T>(*this->list);
    }
};
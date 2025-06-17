#pragma once

template<typename T>
class LinkedList {
public:
    void Append(T item) {
        Node* newNode = new Node(item);
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    LinkedList() : head(nullptr), size(0) {}
    LinkedList(T* items, int count) {
        Node* current = head;
        for (int i = 0; i < count; i++) {
            Node* newNode = new Node(items[i]);
            if (head == nullptr) {
                head = newNode;
            }
            else {
                current->next = newNode;
                current = newNode;
            }
            size++;

        }
    }

    LinkedList(const LinkedList& other) : head(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            Append(current->data); 
            current = current->next;
        }
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next; // Сохраняем ссылку на следующий узел
            delete current;             // Освобождаем текущий узел
            current = next;             // Переходим к следующему узлу
        }
    }

    T GetFirst() {
        if (head == nullptr) {
            throw std::out_of_range("IndexOutOfRange");
        }
        return head->data;
    }

    T GetLast() {
        if (head == nullptr) {
            throw std::out_of_range("IndexOutOfRange");
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->data;
    }

    T Get(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    

    LinkedList<T>* GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex) {
            throw std::out_of_range("IndexOutOfRange");
        }
        LinkedList<T>* subList = new LinkedList<T>();

        Node* current = head;
        int currentIndex = 0;

        while (currentIndex < startIndex) {
            current = current->next;
            currentIndex++;
        }

        while (currentIndex <= endIndex) {
            subList->Append(current->data);
            current = current->next;
            currentIndex++;
        }

        return subList;
    }

    int GetLength() {
        return size;
    }

    void Prepend(T item) {
        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }

        Node* newNode = new Node(item);

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }
        
        ++size;
    }

    LinkedList<T>* Concat(LinkedList<T>* list1, LinkedList<T>* list2) {
        LinkedList<T> newList(list1);
        Node* current = list2->head;
        while (current != nullptr) {
            newList->Append(current->data);
            current = current->next;
        }

        return newList;
    }

private:
    class Node {
        friend class LinkedList<T>;
        T data;
        Node* next;
        // Конструктор узла
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t size;
};
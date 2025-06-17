#pragma once
#include "array_sequence.h"
#include <complex>
#include <cmath>
#include <stdexcept>
#include <iostream>

template <typename T>
class SquareMatrix {
private:
    MutableArraySequence<MutableArraySequence<T>> data;
    size_t size;

public:
    // Конструкторы
    SquareMatrix(size_t size) : size(size) {
        for (size_t i = 0; i < size; ++i) {
            MutableArraySequence<T> row(size);
            for (size_t j = 0; j < size; ++j) {
                row.Set(T(0), j);
            }
            data.Append(row);
        }
    }

    SquareMatrix(const ArraySequence<T>& elements) {
        size_t totalElements = elements.GetLength();
        size = static_cast<size_t>(std::sqrt(totalElements));
        if (size * size != totalElements) {
            throw std::invalid_argument("Invalid number of elements for a square matrix");
        }

        for (size_t i = 0; i < size; ++i) {
            MutableArraySequence<T> row(size);
            for (size_t j = 0; j < size; ++j) {
                row.Set(elements.Get(i * size + j), j);
            }
            data.Append(row);
        }
    }

    SquareMatrix(const SquareMatrix& other) : size(other.size) {
        for (size_t i = 0; i < size; ++i) {
            MutableArraySequence<T> row(size);
            for (size_t j = 0; j < size; ++j) {
                row.Set(other.Get(i, j), j);
            }
            data.Append(row);
        }
    }

    // Основные методы
    T Get(size_t row, size_t col) const {
        if (row >= size || col >= size) throw std::out_of_range("Index out of range");
        return data.Get(row).Get(col);
    }

    void Set(size_t row, size_t col, const T& value) {
        if (row >= size || col >= size) {
            throw std::out_of_range("Index out of range");
        }
        data.Get(row).Set(value, col);
    }

    size_t GetSize() const { return size; }

    // Вспомогательный метод для вывода
    void Print() const {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                std::cout << Get(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Обязательные операции из задания
    SquareMatrix operator+(const SquareMatrix& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Matrix sizes must match");
        }
        SquareMatrix result(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                result.Set(i, j, this->Get(i, j) + other.Get(i, j));
            }
        }
        return result;
    }

    SquareMatrix operator*(const T& scalar) const {
        SquareMatrix result(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                result.Set(i, j, this->Get(i, j) * scalar);
            }
        }
        return result;
    }

    double Norm() const {
        double sum = 0.0;
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                T val = this->Get(i, j);
                if constexpr (std::is_same_v<T, std::complex<double>>) {
                    sum += std::norm(val);
                }
                else {
                    sum += val * val;
                }
            }
        }
        return std::sqrt(sum);
    }

    void SwapRows(size_t row1, size_t row2) {
        if (row1 >= size || row2 >= size) throw std::out_of_range("Invalid row index");
        MutableArraySequence<T> temp = data.Get(row1);
        data.Set(data.Get(row2), row1);
        data.Set(temp, row2);
    }

    void MultiplyRow(size_t row, const T& scalar) {
        if (row >= size) throw std::out_of_range("Invalid row index");
        for (size_t j = 0; j < size; ++j) {
            /*this->Set(row, j, data.Get(row).Get(j) * scalar)*/
            data.Get(row).Set(data.Get(row).Get(j) * scalar, j);
        }
    }

    void AddRowToRow(size_t sourceRow, size_t targetRow) {
        if (sourceRow >= size || targetRow >= size) throw std::out_of_range("Invalid row index");
        for (size_t j = 0; j < size; ++j) {
            T newValue = data.Get(targetRow).Get(j) + data.Get(sourceRow).Get(j);
            data.Get(targetRow).Set(newValue, j);
        }
    }

    // Дополнительные операции
    SquareMatrix operator*(const SquareMatrix& other) const {
        if (size != other.size) throw std::invalid_argument("Matrix sizes must match");
        SquareMatrix result(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                T sum = T(0);
                for (size_t k = 0; k < size; ++k) {
                    sum += this->Get(i, k) * other.Get(k, j);
                }
                result.Set(i, j, sum);
            }
        }
        return result;
    }

    SquareMatrix Transpose() const {
        SquareMatrix result(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                result.Set(j, i, this->Get(i, j));
            }
        }
        return result;
    }

    T Determinant() const {
        if (size == 1) return data.Get(0).Get(0);
        if (size == 2) {
            return data.Get(0).Get(0) * data.Get(1).Get(1) -
                data.Get(0).Get(1) * data.Get(1).Get(0);
        }

        T det = T(0);
        for (size_t j = 0; j < size; ++j) {
            SquareMatrix minor(size - 1);
            for (size_t i = 1; i < size; ++i) {
                for (size_t k = 0, l = 0; k < size; ++k) {
                    if (k == j) continue;
                    minor.Set(i - 1, l++, data.Get(i).Get(k));
                }
            }
            T sign = (j % 2 == 0) ? T(1) : T(-1);
            det += sign * data.Get(0).Get(j) * minor.Determinant();
        }
        return det;
    }

    // Функция Map - применяет функцию к каждому элементу матрицы
    template<typename F>
    SquareMatrix<T> Map(F func) const {
        SquareMatrix<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                result.Set(i, j, func(this->Get(i, j)));
            }
        }
        return result;
    }

    // Функция Reduce - сводит матрицу к одному значению
    template<typename F>
    T Reduce(F func, T init) const {
        T result = init;
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                result = func(result, this->Get(i, j));
            }
        }
        return result;
    }

    template<typename P>
    SquareMatrix<T> Where(P predicate) const {
        SquareMatrix<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                T value = this->Get(i, j);
                if (predicate(value)) {
                    result.Set(i, j, value);
                }
                else {
                    result.Set(i, j, T(0)); // или другое значение по умолчанию
                }
            }
        }
        return result;
    }

    
};

// Явные инстанциации для часто используемых типов
template class SquareMatrix<int>;
template class SquareMatrix<double>;
template class SquareMatrix<std::complex<double>>;
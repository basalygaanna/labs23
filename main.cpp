#include <iostream>
#include <exception>
#include <stdlib.h>
#include <cassert>
#include <cmath>
#include "linked_list.h"
#include "dynamic_array.h"
#include "sequence.h"
#include "list_sequence.h"
#include "array_sequence.h"
#include "square_matrix.h"

void static test_mutable_list_sequence() {
    MutableListSequence<int> list1;
    list1.Append(1);
    list1.Append(2);
    list1.Append(3);
    list1.InsertAt(4, 1);
    list1.Prepend(5);
    assert(list1.GetLength() == 5);
    assert(list1.GetFirst() == 5);
    assert(list1.Get(1) == 1);
    assert(list1.Get(2) == 4);
    assert(list1.Get(3) == 2);
    assert(list1.GetLast() == 3);

    ListSequence<int>* sublist = list1.GetSubsequence(1, 3);
    assert(sublist->GetFirst() == 1);
    assert(sublist->Get(1) == 4);
    assert(sublist->GetLast() == 2);

    Sequence<int>* other = new MutableListSequence<int>(list1);
    ListSequence<int>* new_list1 = list1.Concat(other);
    assert(new_list1->GetLength() == 10);

    std::cout << "test_mutable_list_sequence passed :)" << std::endl;
}

void static test_immutable_list_sequence() {
    ImmutableListSequence<int> list2;
    ListSequence<int>* new1_list2 = list2.Append(10);
    ListSequence<int>* new2_list2 = new1_list2->Append(11);
    ListSequence<int>* new3_list2 = new2_list2->Prepend(12);
    ListSequence<int>* new4_list2 = new3_list2->InsertAt(13, 1);
    assert(new4_list2->GetLength() == 4);
    assert(new4_list2->GetFirst() == 12);
    assert(new4_list2->Get(1) == 13);
    assert(new4_list2->Get(2) == 10);
    assert(new4_list2->GetLast() == 11);

    ListSequence<int>* sublist = new4_list2->GetSubsequence(1, 3);
    assert(sublist->GetLength() == 3);
    assert(sublist->GetFirst() == 13);
    assert(sublist->Get(1) == 10);
    assert(sublist->GetLast() == 11);
    delete sublist;

    Sequence<int>* other = new4_list2->Clone();
    ListSequence<int>* new_list = list2.Concat(other);
    assert(new_list->GetLength() == 4);
    delete other;
    delete new_list;

    assert(new1_list2->GetLength() == 1);
    assert(new2_list2->GetLength() == 2);
    assert(new3_list2->GetLength() == 3);

    delete new1_list2;
    delete new2_list2;
    delete new3_list2;
    delete new4_list2;
    std::cout << "test_immutable_list_sequence passed :)" << std::endl;
}

void static test_mutable_array_sequence() {
    MutableArraySequence<int> array1;
    array1.Append(1);
    array1.Append(2);
    array1.Append(3);
    array1.InsertAt(4, 1);
    array1.Prepend(5);
    assert(array1.GetLength() == 5);
    assert(array1.GetFirst() == 5);
    assert(array1.Get(1) == 1);
    assert(array1.Get(2) == 4);
    assert(array1.Get(3) == 2);
    assert(array1.GetLast() == 3);

    ArraySequence<int>* subarray = array1.GetSubsequence(1, 3);
    assert(subarray->GetFirst() == 1);
    assert(subarray->Get(1) == 4);
    assert(subarray->GetLast() == 2);

    Sequence<int>* other = new MutableArraySequence<int>(array1);
    ArraySequence<int>* new_array1 = array1.Concat(other);
    assert(new_array1->GetLength() == 10);

    std::cout << "test_mutable_array_sequence passed :)" << std::endl;
}

void static test_immutable_array_sequence() {
    ImmutableArraySequence<int> array2;
    ArraySequence<int>* new1_array2 = array2.Append(10);
    ArraySequence<int>* new2_array2 = new1_array2->Append(11);
    ArraySequence<int>* new3_array2 = new2_array2->Prepend(12);
    ArraySequence<int>* new4_array2 = new3_array2->InsertAt(13, 1);
    assert(new4_array2->GetLength() == 4);
    assert(new4_array2->GetFirst() == 12);
    assert(new4_array2->Get(1) == 13);
    assert(new4_array2->Get(2) == 10);
    assert(new4_array2->GetLast() == 11);

    ArraySequence<int>* subarray = new4_array2->GetSubsequence(1, 3);
    assert(subarray->GetLength() == 3);
    assert(subarray->GetFirst() == 13);
    assert(subarray->Get(1) == 10);
    assert(subarray->GetLast() == 11);
    delete subarray;

    Sequence<int>* other = new4_array2->Clone();
    ArraySequence<int>* new_array = array2.Concat(other);
    assert(new_array->GetLength() == 4);
    delete other;
    delete new_array;

    assert(new1_array2->GetLength() == 1);
    assert(new2_array2->GetLength() == 2);
    assert(new3_array2->GetLength() == 3);

    delete new1_array2;
    delete new2_array2;
    delete new3_array2;
    delete new4_array2;
    std::cout << "test_immutable_array_sequence passed :)" << std::endl;
}

void static test_square_matrix() {
    MutableArraySequence<int> elements;
    elements.Append(1);
    elements.Append(2);
    elements.Append(3);
    elements.Append(4);
    elements.Append(5);
    elements.Append(6);
    elements.Append(7);
    elements.Append(8);
    elements.Append(9);
    SquareMatrix<int> mat(elements);
    assert(mat.Get(0, 0) == 1);
    assert(mat.Get(0, 1) == 2);
    assert(mat.Get(0, 2) == 3);
    assert(mat.Get(1, 0) == 4);
    assert(mat.Get(1, 1) == 5);
    assert(mat.Get(1, 2) == 6);
    assert(mat.Get(2, 0) == 7);
    assert(mat.Get(2, 1) == 8);
    assert(mat.Get(2, 2) == 9);

    assert(mat.GetSize() == 3);

    auto transposed = mat.Transpose();
    assert(transposed.Get(0, 0) == 1);
    assert(transposed.Get(0, 1) == 4);
    assert(transposed.Get(0, 2) == 7);
    assert(transposed.Get(1, 0) == 2);
    assert(transposed.Get(1, 1) == 5);
    assert(transposed.Get(1, 2) == 8);
    assert(transposed.Get(2, 0) == 3);
    assert(transposed.Get(2, 1) == 6);
    assert(transposed.Get(2, 2) == 9);

    auto sum_mat = mat + transposed;
    assert(sum_mat.Get(0, 0) == 2);
    assert(sum_mat.Get(0, 1) == 6);
    assert(sum_mat.Get(0, 2) == 10);
    assert(sum_mat.Get(1, 0) == 6);
    assert(sum_mat.Get(1, 1) == 10);
    assert(sum_mat.Get(1, 2) == 14);
    assert(sum_mat.Get(2, 0) == 10);
    assert(sum_mat.Get(2, 1) == 14);
    assert(sum_mat.Get(2, 2) == 18);

    assert(round(mat.Norm() * 100) / 100 == 16.88);

    sum_mat.SwapRows(0, 1);
    assert(sum_mat.Get(0, 0) == 6);
    assert(sum_mat.Get(0, 1) == 10);
    assert(sum_mat.Get(0, 2) == 14);
    assert(sum_mat.Get(1, 0) == 2);
    assert(sum_mat.Get(1, 1) == 6);
    assert(sum_mat.Get(1, 2) == 10);

    transposed.MultiplyRow(1, 3);
    assert(transposed.Get(1, 0) == 6);
    assert(transposed.Get(1, 1) == 15);
    assert(transposed.Get(1, 2) == 24);

    transposed.AddRowToRow(0, 2);
    assert(transposed.Get(2, 0) == 4);
    assert(transposed.Get(2, 1) == 10);
    assert(transposed.Get(2, 2) == 16);

    assert(mat.Determinant() == 0);

    auto doubled1 = mat.Map([](int x) { return x * 2; });
    assert(doubled1.Get(0, 0) == 2);
    assert(doubled1.Get(0, 1) == 4);
    assert(doubled1.Get(0, 2) == 6);
    assert(doubled1.Get(1, 0) == 8);
    assert(doubled1.Get(1, 1) == 10);
    assert(doubled1.Get(1, 2) == 12);
    assert(doubled1.Get(2, 0) == 14);
    assert(doubled1.Get(2, 1) == 16);
    assert(doubled1.Get(2, 2) == 18);

    auto doubled2 = mat * 2;
    assert(doubled2.Get(0, 0) == 2);
    assert(doubled2.Get(0, 1) == 4);
    assert(doubled2.Get(0, 2) == 6);
    assert(doubled2.Get(1, 0) == 8);
    assert(doubled2.Get(1, 1) == 10);
    assert(doubled2.Get(1, 2) == 12);
    assert(doubled2.Get(2, 0) == 14);
    assert(doubled2.Get(2, 1) == 16);
    assert(doubled2.Get(2, 2) == 18);

    int sum = mat.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 45);

    auto evenOnly = mat.Where([](int x) { return x % 2 == 0; });
    assert(evenOnly.Get(0, 0) == 0);
    assert(evenOnly.Get(0, 1) == 2);
    assert(evenOnly.Get(0, 2) == 0);
    assert(evenOnly.Get(1, 0) == 4);
    assert(evenOnly.Get(1, 1) == 0);
    assert(evenOnly.Get(1, 2) == 6);
    assert(evenOnly.Get(2, 0) == 0);
    assert(evenOnly.Get(2, 1) == 8);
    assert(evenOnly.Get(2, 2) == 0);

    auto mat_multi = mat * evenOnly;
    assert(mat_multi.Get(0, 0) == 8);
    assert(mat_multi.Get(0, 1) == 26);
    assert(mat_multi.Get(0, 2) == 12);
    assert(mat_multi.Get(1, 0) == 20);
    assert(mat_multi.Get(1, 1) == 56);
    assert(mat_multi.Get(1, 2) == 30);
    assert(mat_multi.Get(2, 0) == 32);
    assert(mat_multi.Get(2, 1) == 86);
    assert(mat_multi.Get(2, 2) == 48);

    std::cout << "test_square_matrix passed :)" << std::endl;

}
    
int main() {
    test_mutable_list_sequence();
    test_immutable_list_sequence();
    test_mutable_array_sequence();
    test_immutable_array_sequence();
    test_square_matrix();

    return 0;





 

}


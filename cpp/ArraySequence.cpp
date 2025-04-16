#include "ArraySequence.h"
#include <stdexcept>
#include "Types.h"

template <class T>
MutableArraySequence<T>::MutableArraySequence() : items(50) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(T* input, int count) : items(input, count) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(DynamicArray<T>& arr) : items(arr) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(const MutableArraySequence<T>& arr) : items(arr.items) {}

template <class T>
T MutableArraySequence<T>::GetFirst() const {
    if (const_cast<DynamicArray<T>&>(items).GetSize() == 0)
        throw std::out_of_range("EMPTY SEQUENCE");
    return const_cast<DynamicArray<T>&>(items).Get(0);
}

template <class T>
T MutableArraySequence<T>::GetLast() const {
    int s = const_cast<DynamicArray<T>&>(items).GetSize();
    if (s == 0)
        throw std::out_of_range("EMPTY SEQUENCE");
    return const_cast<DynamicArray<T>&>(items).Get(s - 1);
}

template <class T>
T MutableArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= const_cast<DynamicArray<T>&>(items).GetSize())
        throw std::out_of_range("INDEX OUT RANGE");
    return const_cast<DynamicArray<T>&>(items).Get(index);
}

template <class T>
int MutableArraySequence<T>::GetLength() const {
    return const_cast<DynamicArray<T>&>(items).GetSize();
}

template <class T>
Sequence<T>* MutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= items.GetSize() || startIndex > endIndex)
        throw std::out_of_range("INDEX OUT RANGE");
    int count = endIndex - startIndex + 1;
    T* subArr = new T[count];
    for (int i = 0; i < count; i++)
        subArr[i] = items.Get(startIndex + i);
    MutableArraySequence<T>* newSeq = static_cast<MutableArraySequence<T>*>(this->Clone());
    newSeq->items = DynamicArray<T>(subArr, count);
    delete[] subArr;
    return newSeq;
}

template <class T>
Sequence<T>* MutableArraySequence<T>::Append(T item) {
    int length = items.GetSize();
    items.Resize(length + 1);
    items.Set(length, item);
    return Instance();
}

template <class T>
Sequence<T>* MutableArraySequence<T>::Prepend(T item) {
    int length = items.GetSize();
    items.Resize(length + 1);
    for (int i = length; i > 0; i--) {
        items.Set(i, items.Get(i - 1));
    }
    items.Set(0, item);
    return Instance();
}

template <class T>
Sequence<T>* MutableArraySequence<T>::InsertAt(T item, int index) {
    int length = items.GetSize();
    if (index < 0 || index > length)
        throw std::out_of_range("INDEX OUT RANGE");
    items.Resize(length + 1);
    for (int i = length; i > index; i--) {
        items.Set(i, items.Get(i - 1));
    }
    items.Set(index, item);
    return Instance();
}

template <class T>
Sequence<T>* MutableArraySequence<T>::Concat(const Sequence<T>* list) const {
    MutableArraySequence<T>* newSeq = static_cast<MutableArraySequence<T>*>(this->Clone());
    for (int i = 0; i < list->GetLength(); i++) {
        newSeq->Append(list->Get(i));
    }
    return newSeq;
}

template <class T>
Sequence<T>* MutableArraySequence<T>::RemoveAt(int index) {
    int length = items.GetSize();
    if (index < 0 || index >= length)
        throw std::out_of_range("INDEX OUT RANGE");
    for (int i = index; i < length - 1; i++) {
        items.Set(i, items.Get(i + 1));
    }
    items.Resize(length - 1);
    return Instance();
}

template <class T>
Sequence<T>* MutableArraySequence<T>::Instance() const {
    return const_cast<MutableArraySequence<T>*>(this);
}

template <class T>
Sequence<T>* MutableArraySequence<T>::Clone() const {
    return new MutableArraySequence<T>(*this);
}

// Реализация для ImmutableArraySequence

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence() : items(50) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(T* input, int count) : items(input, count) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const DynamicArray<T>& arr) : items((DynamicArray<T>&)arr) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& arr) : items(arr.items) {}

template <class T>
T ImmutableArraySequence<T>::GetFirst() const {
    if (const_cast<DynamicArray<T>&>(items).GetSize() == 0)
        throw std::out_of_range("EMPTY SEQUENCE");
    return const_cast<DynamicArray<T>&>(items).Get(0);
}

template <class T>
T ImmutableArraySequence<T>::GetLast() const {
    int s = const_cast<DynamicArray<T>&>(items).GetSize();
    if (s == 0)
        throw std::out_of_range("EMPTY SEQUENCE");
    return const_cast<DynamicArray<T>&>(items).Get(s - 1);
}

template <class T>
T ImmutableArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= const_cast<DynamicArray<T>&>(items).GetSize())
        throw std::out_of_range("INDEX OUT RANGE");
    return const_cast<DynamicArray<T>&>(items).Get(index);
}

template <class T>
int ImmutableArraySequence<T>::GetLength() const {
    return const_cast<DynamicArray<T>&>(items).GetSize();
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= items.GetSize() || startIndex > endIndex)
        throw std::out_of_range("INDEX OUT RANGE");
    int count = endIndex - startIndex + 1;
    T* newArr = new T[count];
    for (int i = 0; i < count; i++)
        newArr[i] = items.Get(startIndex + i);
    ImmutableArraySequence<T>* newSeq = static_cast<ImmutableArraySequence<T>*>(this->Clone());
    newSeq->items = DynamicArray<T>(newArr, count);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::Append(T item) {
    ImmutableArraySequence<T>* newSeq = static_cast<ImmutableArraySequence<T>*>(this->Clone());
    int length = items.GetSize();
    T* newArr = new T[length + 1];
    for (int i = 0; i < length; i++)
        newArr[i] = items.Get(i);
    newArr[length] = item;
    newSeq->items = DynamicArray<T>(newArr, length + 1);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::Prepend(T item) {
    ImmutableArraySequence<T>* newSeq = static_cast<ImmutableArraySequence<T>*>(this->Clone());
    int length = items.GetSize();
    T* newArr = new T[length + 1];
    newArr[0] = item;
    for (int i = 0; i < length; i++)
        newArr[i + 1] = items.Get(i);
    newSeq->items = DynamicArray<T>(newArr, length + 1);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::InsertAt(T item, int index) {
    int length = items.GetSize();
    if (index < 0 || index > length)
        throw std::out_of_range("INDEX OUT RANGE");
    ImmutableArraySequence<T>* newSeq = static_cast<ImmutableArraySequence<T>*>(this->Clone());
    T* newArr = new T[length + 1];
    for (int i = 0; i < index; i++)
        newArr[i] = items.Get(i);
    newArr[index] = item;
    for (int i = index; i < length; i++)
        newArr[i + 1] = items.Get(i);
    newSeq->items = DynamicArray<T>(newArr, length + 1);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::RemoveAt(int index) {
    int length = items.GetSize();
    if (index < 0 || index >= length)
         throw std::out_of_range("INDEX OUT RANGE");
    T* newArr = new T[length - 1];
    for (int i = 0; i < index; i++)
         newArr[i] = items.Get(i);
    for (int i = index + 1; i < length; i++)
         newArr[i - 1] = items.Get(i);
    ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(newArr, length - 1);
    delete[] newArr;
    return newSeq;
}
template <class T>
Sequence<T>* ImmutableArraySequence<T>::Concat(const Sequence<T>* seq) const {
    int length1 = items.GetSize();
    int length2 = seq->GetLength();
    ImmutableArraySequence<T>* newSeq = static_cast<ImmutableArraySequence<T>*>(this->Clone());
    T* newArr = new T[length1 + length2];
    for (int i = 0; i < length1; i++)
        newArr[i] = items.Get(i);
    for (int i = 0; i < length2; i++)
        newArr[length1 + i] = seq->Get(i);
    newSeq->items = DynamicArray<T>(newArr, length1 + length2);
    delete[] newArr;
    return newSeq;
}

// Эксплицитное инстанцирование шаблонов
template class MutableArraySequence<int>;
template class MutableArraySequence<double>;
template class MutableArraySequence<Complex>;
template class MutableArraySequence<std::string>;
template class MutableArraySequence<std::function<int(int)>>;
template class ImmutableArraySequence<int>;
template class ImmutableArraySequence<double>;
template class ImmutableArraySequence<Complex>;
template class ImmutableArraySequence<std::string>;
template class ImmutableArraySequence<std::function<int(int)>>;
template class MutableArraySequence<void*>;
template class ImmutableArraySequence<void*>;
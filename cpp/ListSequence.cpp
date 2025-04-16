#include "ListSequence.h"
#include "Types.h"
#include <stdexcept>
#include "ArraySequence.h"

template <class T>
MutableListSequence<T>::MutableListSequence() : list() {}

template <class T>
MutableListSequence<T>::MutableListSequence(T *items, int count) : list(items, count) {}

template <class T>
MutableListSequence<T>::MutableListSequence(LinkedList<T> &lst) : list(lst) {}

template <class T>
MutableListSequence<T>::MutableListSequence(const MutableListSequence<T> &lst) : list(lst.list) {}

template <class T>
T MutableListSequence<T>::GetFirst() const
{
    return list.GetFirst();
}

template <class T>
T MutableListSequence<T>::GetLast() const
{
    return list.GetLast();
}

template <class T>
T MutableListSequence<T>::Get(int index) const
{
    return list.Get(index);
}

template <class T>
int MutableListSequence<T>::GetLength() const
{
    return list.GetLength();
}

template <class T>
Sequence<T> *MutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const
{
    if (startIndex < 0 || endIndex >= list.GetLength() || startIndex > endIndex)
        throw std::out_of_range("INDEX OUT RANGE");
    int count = endIndex - startIndex + 1;
    T *newArr = new T[count];
    for (int i = 0; i < count; i++)
        newArr[i] = list.Get(startIndex + i);
    MutableListSequence<T> *newSeq = static_cast<MutableListSequence<T> *>(this->Clone());
    newSeq->list = LinkedList<T>(newArr, count);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T> *MutableListSequence<T>::Append(T item)
{
    list.Append(item);
    return Instance();
}

template <class T>
Sequence<T> *MutableListSequence<T>::Prepend(T item)
{
    list.Prepend(item);
    return Instance();
}

template <class T>
Sequence<T> *MutableListSequence<T>::InsertAt(T item, int index)
{
    if (index < 0 || index > list.GetLength())
        throw std::out_of_range("INDEX OUT RANGE");
    list.InsertAt(item, index);
    return Instance();
}

template <class T>
Sequence<T> *MutableListSequence<T>::RemoveAt(int index)
{
    list.RemoveAt(index);
    return Instance();
}

template <class T>
void MutableListSequence<T>::clear()
{
    while (list.GetLength() > 0)
        list.RemoveAt(0);
}

template <class T>
Sequence<T> *MutableListSequence<T>::Concat(const Sequence<T> *seq) const
{
    MutableListSequence<T> *newSeq = static_cast<MutableListSequence<T> *>(this->Clone());
    for (int i = 0; i < seq->GetLength(); i++)
    {
        newSeq->Append(seq->Get(i));
    }
    return newSeq;
}

template <class T>
Sequence<T> *MutableListSequence<T>::Instance() const
{
    return const_cast<MutableListSequence<T> *>(this);
}

template <class T>
Sequence<T> *MutableListSequence<T>::Clone() const
{
    return new MutableListSequence<T>(*this);
}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence() : list() {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(T *items, int count) : list(items, count) {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const LinkedList<T> &lst) : list(const_cast<LinkedList<T> &>(lst)) {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T> &lst) : list(lst.list) {}

template <class T>
T ImmutableListSequence<T>::GetFirst() const
{
    return const_cast<LinkedList<T> &>(list).GetFirst();
}

template <class T>
T ImmutableListSequence<T>::GetLast() const
{
    return const_cast<LinkedList<T> &>(list).GetLast();
}

template <class T>
T ImmutableListSequence<T>::Get(int index) const
{
    return const_cast<LinkedList<T> &>(list).Get(index);
}

template <class T>
int ImmutableListSequence<T>::GetLength() const
{
    return const_cast<LinkedList<T> &>(list).GetLength();
}

template <class T>
Sequence<T> *ImmutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const
{
    if (startIndex < 0 || endIndex >= list.GetLength() || startIndex > endIndex)
        throw std::out_of_range("INDEX OUT RANGE");
    int count = endIndex - startIndex + 1;
    T *newArr = new T[count];
    for (int i = 0; i < count; i++)
        newArr[i] = list.Get(startIndex + i);
    ImmutableListSequence<T> *newSeq = static_cast<ImmutableListSequence<T> *>(this->Clone());
    newSeq->list = LinkedList<T>(newArr, count);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T> *ImmutableListSequence<T>::Append(T item)
{
    ImmutableListSequence<T> *newSeq = static_cast<ImmutableListSequence<T> *>(this->Clone());
    int length = list.GetLength();
    T *newArr = new T[length + 1];
    for (int i = 0; i < length; i++)
        newArr[i] = list.Get(i);
    newArr[length] = item;
    newSeq->list = LinkedList<T>(newArr, length + 1);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T> *ImmutableListSequence<T>::Prepend(T item)
{
    ImmutableListSequence<T> *newSeq = static_cast<ImmutableListSequence<T> *>(this->Clone());
    int length = list.GetLength();
    T *newArr = new T[length + 1];
    newArr[0] = item;
    for (int i = 0; i < length; i++)
        newArr[i + 1] = list.Get(i);
    newSeq->list = LinkedList<T>(newArr, length + 1);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T> *ImmutableListSequence<T>::InsertAt(T item, int index)
{
    int length = list.GetLength();
    if (index < 0 || index > length)
        throw std::out_of_range("INDEX OUT RANGE");
    ImmutableListSequence<T> *newSeq = static_cast<ImmutableListSequence<T> *>(this->Clone());
    T *newArr = new T[length + 1];
    for (int i = 0; i < index; i++)
        newArr[i] = list.Get(i);
    newArr[index] = item;
    for (int i = index; i < length; i++)
        newArr[i + 1] = list.Get(i);
    newSeq->list = LinkedList<T>(newArr, length + 1);
    delete[] newArr;
    return newSeq;
}

template <class T>
Sequence<T> *ImmutableListSequence<T>::RemoveAt(int index)
{
    ImmutableListSequence<T> *newSeq = static_cast<ImmutableListSequence<T> *>(this->Clone());
    newSeq->list.RemoveAt(index);
    return newSeq;
}

template <class T>
Sequence<T> *ImmutableListSequence<T>::Concat(const Sequence<T> *seq) const
{
    int length1 = list.GetLength();
    int length2 = seq->GetLength();
    ImmutableListSequence<T> *newSeq = static_cast<ImmutableListSequence<T> *>(this->Clone());
    T *newArr = new T[length1 + length2];
    for (int i = 0; i < length1; i++)
        newArr[i] = list.Get(i);
    for (int i = 0; i < length2; i++)
        newArr[length1 + i] = seq->Get(i);
    newSeq->list = LinkedList<T>(newArr, length1 + length2);
    delete[] newArr;
    return newSeq;
}

template class MutableListSequence<int>;
template class MutableListSequence<double>;
template class MutableListSequence<Complex>;
template class MutableListSequence<std::string>;
template class MutableListSequence<std::function<int(int)>>;
template class MutableListSequence<MutableArraySequence<int>>;
template class MutableListSequence<MutableArraySequence<double>>;
template class MutableListSequence<MutableArraySequence<Complex>>;
template class MutableListSequence<MutableArraySequence<std::string>>;
template class MutableListSequence<MutableArraySequence<std::function<int(int)>>>;
template class ImmutableListSequence<int>;
template class ImmutableListSequence<double>;
template class ImmutableListSequence<Complex>;
template class ImmutableListSequence<std::string>;
template class ImmutableListSequence<std::function<int(int)>>;
template class MutableListSequence<MutableArraySequence<void *>>;
#include "SegmentedDeque.h"
#include "Types.h"
#include <algorithm>
#include <functional>

template <class T>
SegmentedDeque<T>::SegmentedDeque(int segCap)
    : segmentCapacity(segCap), totalSize(0)
{
    data = new MutableListSequence<MutableArraySequence<T>>();
}

template <class T>
SegmentedDeque<T>::SegmentedDeque(const SegmentedDeque<T> &other)
    : segmentCapacity(other.segmentCapacity), totalSize(other.totalSize)
{
    data = new MutableListSequence<MutableArraySequence<T>>();
    for (int i = 0; i < other.data->GetLength(); i++)
    {
        MutableArraySequence<T> seg = (*other.data)[i];
        data->Append(seg);
    }
}

template <class T>
SegmentedDeque<T>::~SegmentedDeque()
{
    delete data;
}

template <class T>
void SegmentedDeque<T>::push_front(const T &value)
{
    if (data->GetLength() == 0 || (*data)[0].GetLength() >= segmentCapacity)
    {
        data->Prepend(MutableArraySequence<T>());
    }
    (*data)[0].Prepend(value);
    totalSize++;
}

template <class T>
void SegmentedDeque<T>::push_back(const T &value)
{
    if (data->GetLength() == 0 || (*data)[data->GetLength() - 1].GetLength() >= segmentCapacity)
    {
        data->Append(MutableArraySequence<T>());
    }
    (*data)[data->GetLength() - 1].Append(value);
    totalSize++;
}

template <class T>
void SegmentedDeque<T>::pop_front()
{
    if (empty())
        throw std::out_of_range("DEQUE IS EMPTY");
    (*data)[0].RemoveAt(0);
    totalSize--;
    if ((*data)[0].GetLength() == 0)
    {
        data->RemoveAt(0);
    }
}

template <class T>
void SegmentedDeque<T>::pop_back()
{
    if (empty())
        throw std::out_of_range("DEQUE IS EMPTY");
    int lastIndex = data->GetLength() - 1;
    (*data)[lastIndex].RemoveAt((*data)[lastIndex].GetLength() - 1);
    totalSize--;
    if ((*data)[lastIndex].GetLength() == 0)
    {
        data->RemoveAt(lastIndex);
    }
}

template <class T>
T &SegmentedDeque<T>::front()
{
    if (empty())
        throw std::out_of_range("DEQUE IS EMPTY");
    return (*data)[0][0];
}

template <class T>
T &SegmentedDeque<T>::back()
{
    if (empty())
        throw std::out_of_range("DEQUE IS EMPTY");
    int lastSeg = data->GetLength() - 1;
    return (*data)[lastSeg][(*data)[lastSeg].GetLength() - 1];
}

template <class T>
T &SegmentedDeque<T>::operator[](int index)
{
    if (index < 0 || index >= totalSize)
        throw std::out_of_range("INDEX OUT OF RANGE");
    int idx = index;
    for (int i = 0; i < data->GetLength(); i++)
    {
        int segSize = (*data)[i].GetLength();
        if (idx < segSize)
            return (*data)[i][idx];
        idx -= segSize;
    }
    throw std::out_of_range("INDEX OUT OF RANGE");
}

template <class T>
const T &SegmentedDeque<T>::operator[](int index) const
{
    if (index < 0 || index >= totalSize)
        throw std::out_of_range("INDEX OUT OF RANGE");
    int idx = index;
    for (int i = 0; i < data->GetLength(); i++)
    {
        int segSize = (*data)[i].GetLength();
        if (idx < segSize)
            return (*data)[i][idx];
        idx -= segSize;
    }
    throw std::out_of_range("INDEX OUT OF RANGE");
}

template <class T>
int SegmentedDeque<T>::size() const { return totalSize; }

template <class T>
bool SegmentedDeque<T>::empty() const { return totalSize == 0; }

template <class T>
void SegmentedDeque<T>::clear()
{
    data->clear();
    totalSize = 0;
}

template <class T>
SegmentedDeque<T> *SegmentedDeque<T>::Concat(const SegmentedDeque<T> *other) const
{
    SegmentedDeque<T> *result = new SegmentedDeque<T>(segmentCapacity);
    for (int i = 0; i < totalSize; i++)
    {
        result->push_back((*this)[i]);
    }
    for (int i = 0; i < other->totalSize; i++)
    {
        result->push_back((*other)[i]);
    }
    return result;
}

template <class T>
SegmentedDeque<T> *SegmentedDeque<T>::GetSubsequence(int startIndex, int endIndex) const
{
    if (startIndex < 0 || endIndex >= totalSize || startIndex > endIndex)
        throw std::out_of_range("INVALID INDICES");
    SegmentedDeque<T> *sub = new SegmentedDeque<T>(segmentCapacity);
    for (int i = startIndex; i <= endIndex; i++)
    {
        sub->push_back((*this)[i]);
    }
    return sub;
}

template <class T>
void SegmentedDeque<T>::Sort()
{
    if (empty())
        return;
    int n = totalSize;
    T *arr = new T[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = (*this)[i];
    }
    std::sort(arr, arr + n);
    clear();
    for (int i = 0; i < n; i++)
    {
        push_back(arr[i]);
    }
    delete[] arr;
}

template <class T>
SegmentedDeque<T> *SegmentedDeque<T>::Map(T (*func)(T)) const
{
    SegmentedDeque<T> *result = new SegmentedDeque<T>(segmentCapacity);
    for (int i = 0; i < totalSize; i++)
    {
        result->push_back(func((*this)[i]));
    }
    return result;
}

template <class T>
SegmentedDeque<T> *SegmentedDeque<T>::Where(const std::function<bool(T)> &predicate) const
{
    SegmentedDeque<T> *result = new SegmentedDeque<T>(segmentCapacity);
    for (int i = 0; i < totalSize; i++)
    {
        T elem = (*this)[i];
        if (predicate(elem))
            result->push_back(elem);
    }
    return result;
}

template <class T>
T SegmentedDeque<T>::Reduce(T (*func)(T, T), T init) const
{
    T accumulator = init;
    for (int i = 0; i < totalSize; i++)
    {
        accumulator = func(accumulator, (*this)[i]);
    }
    return accumulator;
}

template <class T>
int SegmentedDeque<T>::FindSubsequence(const SegmentedDeque<T> *subseq) const
{
    if (subseq->totalSize == 0 || subseq->totalSize > totalSize)
        return -1;
    for (int i = 0; i <= totalSize - subseq->totalSize; i++)
    {
        bool match = true;
        for (int j = 0; j < subseq->totalSize; j++)
        {
            if ((*this)[i + j] != (*subseq)[j])
            {
                match = false;
                break;
            }
        }
        if (match)
            return i;
    }
    return -1;
}

template <class T>
SegmentedDeque<T> *SegmentedDeque<T>::Merge(const SegmentedDeque<T> *other) const
{
    return Concat(other);
}

template <class T>
T SegmentedDeque<T>::GetFirst() const
{
    if (empty())
        throw std::out_of_range("DEQUE IS EMPTY");
    return (*data)[0][0];
}

template <class T>
T SegmentedDeque<T>::GetLast() const
{
    if (empty())
        throw std::out_of_range("DEQUE IS EMPTY");
    int lastSeg = data->GetLength() - 1;
    return (*data)[lastSeg][(*data)[lastSeg].GetLength() - 1];
}

template <class T>
T SegmentedDeque<T>::Get(int index) const
{
    return (*this)[index];
}

template <class T>
int SegmentedDeque<T>::GetLength() const
{
    return totalSize;
}

template <class T>
Sequence<T> *SegmentedDeque<T>::Append(T item)
{
    push_back(item);
    return this;
}

template <class T>
Sequence<T> *SegmentedDeque<T>::Prepend(T item)
{
    push_front(item);
    return this;
}

template <class T>
Sequence<T> *SegmentedDeque<T>::InsertAt(T item, int index)
{
    if (index < 0 || index > totalSize)
        throw std::out_of_range("INDEX OUT OF RANGE");
    SegmentedDeque<T> *newDeque = new SegmentedDeque<T>(segmentCapacity);
    for (int i = 0; i < index; i++)
    {
        newDeque->push_back((*this)[i]);
    }
    newDeque->push_back(item);
    for (int i = index; i < totalSize; i++)
    {
        newDeque->push_back((*this)[i]);
    }
    return newDeque;
}

template <class T>
Sequence<T> *SegmentedDeque<T>::Concat(const Sequence<T> *list) const
{
    const SegmentedDeque<T> *other = dynamic_cast<const SegmentedDeque<T> *>(list);
    if (other == nullptr)
        throw std::runtime_error("INVALID TYPE FOR CONCATENATION");
    return Concat(other);
}

template <class T>
Sequence<T> *SegmentedDeque<T>::RemoveAt(int index)
{
    if (index < 0 || index >= totalSize)
        throw std::out_of_range("INDEX OUT OF RANGE");
    SegmentedDeque<T> *newDeque = new SegmentedDeque<T>(segmentCapacity);
    for (int i = 0; i < totalSize; i++)
    {
        if (i != index)
            newDeque->push_back((*this)[i]);
    }
    return newDeque;
}

template <>
void SegmentedDeque<FunctionPtr>::Sort() {}
template <>
int SegmentedDeque<FunctionPtr>::FindSubsequence(const SegmentedDeque<FunctionPtr> *subseq) const
{
    return -1;
}
template <>
FunctionPtr SegmentedDeque<FunctionPtr>::Reduce(FunctionPtr (*func)(FunctionPtr, FunctionPtr), FunctionPtr init) const
{
    throw std::runtime_error("REDUCE NOT SUPPORTED FOR FUNCTIONTYPE");
}

template class SegmentedDeque<int>;
template class SegmentedDeque<double>;
template class SegmentedDeque<Complex>;
template class SegmentedDeque<std::string>;
template class SegmentedDeque<void *>;
template class SegmentedDeque<std::function<int(int)>>;

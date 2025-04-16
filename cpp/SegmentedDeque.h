#pragma once
#include "ListSequence.h"
#include "ArraySequence.h"
#include "Sequence.h"
#include <stdexcept>
#include <functional>

template <class T>
class SegmentedDeque : public Sequence<T>
{
private:
    MutableListSequence<MutableArraySequence<T>> *data;
    int segmentCapacity;
    int totalSize;

public:
    SegmentedDeque(int segmentCapacity = 16);
    SegmentedDeque(const SegmentedDeque<T> &other);
    ~SegmentedDeque();
    void push_front(const T &value);
    void push_back(const T &value);
    void pop_front();
    void pop_back();
    T &front();
    T &back();
    T &operator[](int index);
    const T &operator[](int index) const;
    int size() const;
    bool empty() const;
    void clear();
    SegmentedDeque<T> *Concat(const SegmentedDeque<T> *other) const;
    virtual SegmentedDeque<T> *GetSubsequence(int startIndex, int endIndex) const override;
    void Sort();
    SegmentedDeque<T> *Map(T (*func)(T)) const;
    SegmentedDeque<T> *Where(const std::function<bool(T)> &predicate) const;
    T Reduce(T (*func)(T, T), T init) const;
    int FindSubsequence(const SegmentedDeque<T> *subseq) const;
    SegmentedDeque<T> *Merge(const SegmentedDeque<T> *other) const;
    virtual T GetFirst() const override;
    virtual T GetLast() const override;
    virtual T Get(int index) const override;
    virtual int GetLength() const override;
    virtual Sequence<T> *Append(T item) override;
    virtual Sequence<T> *Prepend(T item) override;
    virtual Sequence<T> *InsertAt(T item, int index) override;
    virtual Sequence<T> *Concat(const Sequence<T> *list) const override;
    virtual Sequence<T> *RemoveAt(int index) override;
};

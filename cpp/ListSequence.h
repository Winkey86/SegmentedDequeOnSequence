#pragma once
#include "Sequence.h"
#include "LinkedList.h"
#include <stdexcept>

template <class T>
class MutableListSequence : public Sequence<T>
{
private:
    LinkedList<T> list;

public:
    MutableListSequence();
    MutableListSequence(T *items, int count);
    MutableListSequence(LinkedList<T> &lst);
    MutableListSequence(const MutableListSequence<T> &lst);
    virtual T GetFirst() const override;
    virtual T GetLast() const override;
    virtual T Get(int index) const override;
    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) const override;
    virtual int GetLength() const override;
    virtual Sequence<T> *Append(T item) override;
    virtual Sequence<T> *Prepend(T item) override;
    virtual Sequence<T> *InsertAt(T item, int index) override;
    virtual Sequence<T> *Concat(const Sequence<T> *seq) const override;
    virtual Sequence<T> *RemoveAt(int index) override;
    virtual void clear();
    virtual Sequence<T> *Instance() const;
    virtual Sequence<T> *Clone() const;
    T &operator[](int index)
    {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return list[index];
    }
    const T &operator[](int index) const
    {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return list[index];
    }
};

template <class T>
class ImmutableListSequence : public Sequence<T>
{
private:
    LinkedList<T> list;

public:
    ImmutableListSequence();
    ImmutableListSequence(T *items, int count);
    ImmutableListSequence(const LinkedList<T> &lst);
    ImmutableListSequence(const ImmutableListSequence<T> &lst);
    virtual T GetFirst() const override;
    virtual T GetLast() const override;
    virtual T Get(int index) const override;
    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) const override;
    virtual int GetLength() const override;
    virtual Sequence<T> *Append(T item) override;
    virtual Sequence<T> *Prepend(T item) override;
    virtual Sequence<T> *InsertAt(T item, int index) override;
    virtual Sequence<T> *Concat(const Sequence<T> *seq) const override;
    virtual Sequence<T> *RemoveAt(int index) override;
    T &operator[](int index)
    {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return list[index];
    }
    const T &operator[](int index) const
    {
        if (index < 0 || index >= GetLength())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return list[index];
    }
    virtual Sequence<T> *Instance() const { return Clone(); }
    virtual Sequence<T> *Clone() const { return new ImmutableListSequence<T>(*this); }
};

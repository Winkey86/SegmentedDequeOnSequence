#pragma once
#include <stdexcept>

template <class T>
class DynamicArray
{
private:
    T *data;
    int cnt;
    int capacity;

public:
    DynamicArray(int size);
    DynamicArray(T *items, int count);
    DynamicArray(const DynamicArray<T> &dynamicArray);
    ~DynamicArray();
    DynamicArray<T> &operator=(const DynamicArray<T> &other)
    {
        if (this != &other)
        {
            delete[] data;
            cnt = other.cnt;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < cnt; i++)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    T Get(int index) const;
    int GetSize() const;
    void Set(int index, const T &value);
    void Resize(int newSize);
    T &operator[](int index)
    {
        if (index < 0 || index >= GetSize())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return data[index];
    }
    const T &operator[](int index) const
    {
        if (index < 0 || index >= GetSize())
            throw std::out_of_range("INDEX OUT OF RANGE");
        return data[index];
    }
};

#pragma once
#include <memory>
#if __cplusplus <= 201103L
namespace std
{
    template <typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args &&...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif
#include "SegmentedDeque.h"
#include "Types.h"
#include <map>
#include <sstream>
#include <functional>
#include <ostream>

class BaseDequeWrapper
{
public:
    virtual ~BaseDequeWrapper() = default;
    virtual void push_front(void *value) = 0;
    virtual void push_back(void *value) = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual void *front() = 0;
    virtual void *back() = 0;
    virtual void print(std::ostream &out) const = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual void sort() = 0;
    virtual std::unique_ptr<BaseDequeWrapper> concat(BaseDequeWrapper *other) = 0;
    virtual std::unique_ptr<BaseDequeWrapper> where(const std::function<bool(void *)> &predicate) = 0;
    virtual std::unique_ptr<BaseDequeWrapper> map(const std::string &operation) = 0;
    virtual std::unique_ptr<BaseDequeWrapper> merge(BaseDequeWrapper *other) = 0;
    virtual Type *getType() = 0;
};

template <typename T>
class DequeWrapper : public BaseDequeWrapper
{
private:
    SegmentedDeque<T> deque;
    Type *type;

public:
    DequeWrapper(Type *t) : type(t) {}
    DequeWrapper(SegmentedDeque<T> *d, Type *t) : deque(std::move(*d)), type(t) { delete d; }
    DequeWrapper(SegmentedDeque<T> &&d, Type *t) : deque(std::move(d)), type(t) {}

    void push_front(void *value) override
    {
        deque.push_front(*static_cast<T *>(value));
    }

    void push_back(void *value) override
    {
        deque.push_back(*static_cast<T *>(value));
    }

    void pop_front() override { deque.pop_front(); }
    void pop_back() override { deque.pop_back(); }
    void *front() override { return &deque.front(); }
    void *back() override { return &deque.back(); }

    virtual void print(std::ostream &out) const override
    {
        for (int i = 0; i < deque.size(); ++i)
        {
            type->print((void *)(&deque[i]), out);
            out << " ";
        }
        out << "\n";
    }

    int size() override { return deque.size(); }
    void clear() override { deque.clear(); }

    void sort() override { deque.Sort(); }

    std::unique_ptr<BaseDequeWrapper> concat(BaseDequeWrapper *other) override
    {
        auto otherDeque = static_cast<DequeWrapper<T> *>(other);
        SegmentedDeque<T> *result = deque.Concat(&otherDeque->deque);
        return std::make_unique<DequeWrapper<T>>(result, type);
    }

    std::unique_ptr<BaseDequeWrapper> where(const std::function<bool(void *)> &predicate) override
    {
        SegmentedDeque<T> *result = deque.Where([&predicate](T item)
                                                { return predicate(static_cast<void *>(&item)); });
        return std::make_unique<DequeWrapper<T>>(result, type);
    }

    Type *getType() override { return type; }

    std::unique_ptr<BaseDequeWrapper> map(const std::string &operation) override
    {
        SegmentedDeque<T> newDeque;
        for (int i = 0; i < deque.size(); ++i)
        {
            T element = deque[i];
            type->mult(&element, operation);
            newDeque.push_back(element);
        }
        return std::make_unique<DequeWrapper<T>>(std::move(newDeque), type);
    }

    std::unique_ptr<BaseDequeWrapper> merge(BaseDequeWrapper *other) override
    {
        auto otherDeque = static_cast<DequeWrapper<T> *>(other);
        SegmentedDeque<T> *result = deque.Merge(&otherDeque->deque);
        return std::make_unique<DequeWrapper<T>>(result, type);
    }
};

class MenuDeque
{
private:
    std::map<std::string, std::unique_ptr<BaseDequeWrapper>> deques;
    std::string activeDeque;

    void *parseValue(const std::string &s, Type *type);
    bool parsePredicate(const std::string &op, void *refValue, void *item);

public:
    void processCommand(const std::string &line, std::ostream &out);
};

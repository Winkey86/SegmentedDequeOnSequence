#pragma once
#include <string>
#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>

class Type
{
public:
    virtual ~Type() = default;
    virtual void sum(void *el1, void *el2, void *result) = 0;
    virtual void print(void *el, std::ostream &out) const = 0;
    virtual size_t size() const = 0;
    virtual void *mult(void *element, const std::string &scal) const = 0;
};

class IntType : public Type
{
public:
    void sum(void *el1, void *el2, void *result) override;
    void print(void *el, std::ostream &out) const override;
    size_t size() const override { return sizeof(int); }
    void *mult(void *element, const std::string &scal) const override;
};

class DoubleType : public Type
{
public:
    void sum(void *el1, void *el2, void *result) override;
    void print(void *el, std::ostream &out) const override;
    size_t size() const override { return sizeof(double); }
    void *mult(void *element, const std::string &scal) const override;
};
struct Complex
{
    double real;
    double imag;
};

inline bool operator<(const Complex &a, const Complex &b)
{
    return std::sqrt(a.real * a.real + a.imag * a.imag) < std::sqrt(b.real * b.real + b.imag * b.imag);
}

inline bool operator==(const Complex &a, const Complex &b)
{
    const double eps = 1e-9;
    return std::fabs(a.real - b.real) < eps && std::fabs(a.imag - b.imag) < eps;
}
inline bool operator!=(const Complex &a, const Complex &b)
{
    return !(a == b);
}

class ComplexType : public Type
{
public:
    void sum(void *el1, void *el2, void *result) override;
    void print(void *el, std::ostream &out) const override;
    size_t size() const override { return sizeof(Complex); }
    void *mult(void *element, const std::string &scal) const override;
};

class StringType : public Type
{
public:
    void sum(void *el1, void *el2, void *result) override;
    void descartes_mult(void *el1, void *el2, std::vector<std::string> &result);
    void print(void *el, std::ostream &out) const override;
    size_t size() const override { return sizeof(std::string); }
    void *mult(void *element, const std::string &scal) const override;
};

// using==typedef
using FunctionPtr = std::function<int(int)>;

class FunctionType : public Type
{
private:
    std::vector<FunctionPtr> functions;

public:
    void sum(void *el1, void *el2, void *result) override {}
    FunctionPtr &operator[](size_t index);
    void print(void *el, std::ostream &out) const override;
    size_t size() const override { return sizeof(FunctionPtr); }
    void add_function(FunctionPtr func);
    void *mult(void *element, const std::string &scal) const override
    {
        throw std::runtime_error("Multiplication operation not supported for FunctionType");
    }
};

class PersonType : public Type
{
public:
    void sum(void *el1, void *el2, void *result) override {}
    void print(void *el, std::ostream &out) const override;
    size_t size() const override { return sizeof(std::string); }
    void *mult(void *element, const std::string &scal) const override
    {
        throw std::runtime_error("Multiplication operation not supported for PersonType");
    }
};

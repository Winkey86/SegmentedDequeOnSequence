#include "Types.h"
#include <iostream>
#include <stdexcept>
#include <ostream>

void IntType::sum(void *el1, void *el2, void *result)
{
    *static_cast<int *>(result) = *static_cast<int *>(el1) + *static_cast<int *>(el2);
}

void IntType::print(void *el, std::ostream &out) const
{
    out << *static_cast<int *>(el);
}

void *IntType::mult(void *element, const std::string &scal) const
{
    int *val = static_cast<int *>(element);
    int f = std::stoi(scal);
    *val = (*val) * f;
    return val;
}

void DoubleType::sum(void *el1, void *el2, void *result)
{
    *static_cast<double *>(result) = *static_cast<double *>(el1) + *static_cast<double *>(el2);
}

void DoubleType::print(void *el, std::ostream &out) const
{
    out << *static_cast<double *>(el);
}

void *DoubleType::mult(void *element, const std::string &scal) const
{
    double *d = static_cast<double *>(element);
    double f = std::stod(scal);
    *d = (*d) * f;
    return d;
}

void ComplexType::sum(void *el1, void *el2, void *result)
{
    Complex *a = static_cast<Complex *>(el1);
    Complex *b = static_cast<Complex *>(el2);
    Complex *res = static_cast<Complex *>(result);
    res->real = a->real + b->real;
    res->imag = a->imag + b->imag;
}

void ComplexType::print(void *el, std::ostream &out) const
{
    Complex *c = static_cast<Complex *>(el);
    out << "(" << c->real << " + " << c->imag << "i)";
}

void *ComplexType::mult(void *element, const std::string &scal) const
{
    double f = std::stod(scal);
    Complex *c = static_cast<Complex *>(element);
    c->real *= f;
    c->imag *= f;
    return c;
}

void StringType::sum(void *el1, void *el2, void *result)
{
    std::string *a = static_cast<std::string *>(el1);
    std::string *b = static_cast<std::string *>(el2);
    *static_cast<std::string *>(result) = *a + *b;
}

void StringType::descartes_mult(void *el1, void *el2, std::vector<std::string> &result)
{
    std::string *str1 = static_cast<std::string *>(el1);
    std::string *str2 = static_cast<std::string *>(el2);
    for (char c1 : *str1)
    {
        for (char c2 : *str2)
        {
            result.push_back(std::string(1, c1) + c2);
        }
    }
}

void StringType::print(void *el, std::ostream &out) const
{
    out << *static_cast<std::string *>(el);
}

void *StringType::mult(void *element, const std::string &scal) const
{
    int times = std::stoi(scal);
    std::string *str = static_cast<std::string *>(element);
    std::string result;
    for (int i = 0; i < times; i++)
    {
        result += *str;
    }
    *str = result;
    return str;
}

FunctionPtr &FunctionType::operator[](size_t index)
{
    return functions[index];
}

void FunctionType::print(void *el, std::ostream &out) const
{
    auto ptr = static_cast<FunctionPtr *>(el);
    out << "Function:" << ptr->target_type().name();
}

void FunctionType::add_function(FunctionPtr func)
{
    functions.push_back(func);
}

void PersonType::print(void *el, std::ostream &out) const
{
    out << *static_cast<std::string *>(el);
}

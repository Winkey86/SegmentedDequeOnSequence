#include "SegDeqMenu.h"
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <iostream>

void *MenuDeque::parseValue(const std::string &s, Type *type)
{
    if (dynamic_cast<IntType *>(type))
    {
        int *val = new int;
        *val = std::stoi(s);
        return val;
    }
    else if (dynamic_cast<DoubleType *>(type))
    {
        double *val = new double;
        *val = std::stod(s);
        return val;
    }
    else if (dynamic_cast<StringType *>(type))
    {
        std::string *val = new std::string(s);
        return val;
    }
    else if (dynamic_cast<ComplexType *>(type))
    {
        size_t comma = s.find(',');
        if (comma == std::string::npos)
            throw std::runtime_error("INVALID COMPLEX FORMAT. EXPECTED FORMAT: REAL,IMAG");
        Complex *c = new Complex;
        c->real = std::stod(s.substr(0, comma));
        c->imag = std::stod(s.substr(comma + 1));
        return c;
    }
    else if (dynamic_cast<FunctionType *>(type))
    {
        using FunctionPtr = std::function<int(int)>;
        FunctionPtr *fp = new FunctionPtr;
        if (s == "inc1")
            *fp = [](int x)
            { return x + 1; };
        else if (s == "inc2")
            *fp = [](int x)
            { return x + 2; };
        else if (s == "inc3")
            *fp = [](int x)
            { return x + 3; };
        else
            throw std::runtime_error("UNKNOWN FUNCTION NAME: " + s);
        return fp;
    }
    else if (dynamic_cast<PersonType *>(type))
    {
        std::string *person = new std::string(s);
        return person;
    }
    throw std::runtime_error("UNSUPPORTED TYPE");
}

bool MenuDeque::parsePredicate(const std::string &op, void *refValue, void *item)
{
    int refVal = *static_cast<int *>(refValue);
    int itemVal = *static_cast<int *>(item);
    if (op == "==")
        return itemVal == refVal;
    if (op == ">")
        return itemVal > refVal;
    if (op == "<")
        return itemVal < refVal;
    throw std::runtime_error("UNKNOWN PREDICATE OPERATION");
}

void MenuDeque::processCommand(const std::string &line, std::ostream &out)
{
    std::cout << "[SEGDEQMENU] PROCESSING COMMAND: " << line << std::endl;

    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    try
    {
        if (cmd == "CREATE")
        {
            std::string name, typeStr;
            iss >> name >> typeStr;
            if (typeStr == "INT")
                deques[name] = std::make_unique<DequeWrapper<int>>(new IntType());
            else if (typeStr == "DOUBLE")
                deques[name] = std::make_unique<DequeWrapper<double>>(new DoubleType());
            else if (typeStr == "STRING")
                deques[name] = std::make_unique<DequeWrapper<std::string>>(new StringType());
            else if (typeStr == "COMPLEX")
                deques[name] = std::make_unique<DequeWrapper<Complex>>(new ComplexType());
            else if (typeStr == "FUNCTION")
                deques[name] = std::make_unique<DequeWrapper<FunctionPtr>>(new FunctionType());
            else if (typeStr == "PERSON")
                deques[name] = std::make_unique<DequeWrapper<std::string>>(new PersonType());
            else
                throw std::runtime_error("UNKNOWN TYPE: " + typeStr);

            activeDeque = name;
            out << "DEQUE '" << name << "' CREATED.\n";
            std::cout << "[SEGDEQMENU] CREATED DEQUE '" << name << "' OF TYPE " << typeStr << std::endl;
        }
        else if (cmd == "SELECT")
        {
            std::string name;
            iss >> name;
            if (deques.find(name) == deques.end())
                throw std::runtime_error("DEQUE NOT FOUND");
            activeDeque = name;
            out << "SELECTED DEQUE: " << name << "\n";
            std::cout << "[SEGDEQMENU] SELECTED DEQUE: " << name << std::endl;
        }
        else if (cmd == "LIST")
        {
            out << "CREATED DEQUES:" << "\n";
            for (auto &pair : deques)
            {
                out << "  " << pair.first << "\n";
            }
            std::cout << "[SEGDEQMENU] LIST EXECUTED" << std::endl;
        }
        else if (cmd == "PUSH_FRONT")
        {
            std::string value;
            iss >> value;
            auto &dq = deques[activeDeque];
            void *parsed = parseValue(value, dq->getType());
            dq->push_front(parsed);
            if (dynamic_cast<IntType *>(dq->getType()))
                delete static_cast<int *>(parsed);
            else if (dynamic_cast<DoubleType *>(dq->getType()))
                delete static_cast<double *>(parsed);
            else if (dynamic_cast<StringType *>(dq->getType()))
                delete static_cast<std::string *>(parsed);
            else if (dynamic_cast<ComplexType *>(dq->getType()))
                delete static_cast<Complex *>(parsed);
            else if (dynamic_cast<FunctionType *>(dq->getType()))
                delete static_cast<std::function<int(int)> *>(parsed);
            else if (dynamic_cast<PersonType *>(dq->getType()))
                delete static_cast<std::string *>(parsed);

            out << "PUSHED TO FRONT: ";
            dq->getType()->print(dq->front(), out);
            out << "\n";
            std::cout << "[SEGDEQMENU] PUSH_FRONT EXECUTED WITH VALUE: " << value << std::endl;
        }
        else if (cmd == "PUSH_BACK")
        {
            std::string value;
            iss >> value;
            auto &dq = deques[activeDeque];
            void *parsed = parseValue(value, dq->getType());
            dq->push_back(parsed);
            if (dynamic_cast<IntType *>(dq->getType()))
                delete static_cast<int *>(parsed);
            else if (dynamic_cast<DoubleType *>(dq->getType()))
                delete static_cast<double *>(parsed);
            else if (dynamic_cast<StringType *>(dq->getType()))
                delete static_cast<std::string *>(parsed);
            else if (dynamic_cast<ComplexType *>(dq->getType()))
                delete static_cast<Complex *>(parsed);
            else if (dynamic_cast<FunctionType *>(dq->getType()))
                delete static_cast<std::function<int(int)> *>(parsed);
            else if (dynamic_cast<PersonType *>(dq->getType()))
                delete static_cast<std::string *>(parsed);

            out << "PUSHED TO BACK: ";
            dq->getType()->print(dq->back(), out);
            out << "\n";
            std::cout << "[SEGDEQMENU] PUSH_BACK EXECUTED WITH VALUE: " << value << std::endl;
        }
        else if (cmd == "POP_FRONT")
        {
            auto &dq = deques[activeDeque];
            out << "POPPED FROM FRONT: ";
            dq->getType()->print(dq->front(), out);
            out << "\n";
            dq->pop_front();
            std::cout << "[SEGDEQMENU] POP_FRONT EXECUTED" << std::endl;
        }
        else if (cmd == "POP_BACK")
        {
            auto &dq = deques[activeDeque];
            out << "POPPED FROM BACK: ";
            dq->getType()->print(dq->back(), out);
            out << "\n";
            dq->pop_back();
            std::cout << "[SEGDEQMENU] POP_BACK EXECUTED" << std::endl;
        }
        else if (cmd == "PRINT")
        {
            out << "DEQUE CONTENTS: ";
            deques[activeDeque]->print(out);
            std::cout << "[SEGDEQMENU] PRINT EXECUTED" << std::endl;
        }
        else if (cmd == "SORT")
        {
            deques[activeDeque]->sort();
            out << "DEQUE SORTED.\n";
            std::cout << "[SEGDEQMENU] SORT EXECUTED" << std::endl;
        }
        else if (cmd == "CONCAT")
        {
            std::string otherName;
            iss >> otherName;
            if (deques.find(otherName) == deques.end())
                throw std::runtime_error("DEQUE NOT FOUND: " + otherName);
            auto newDeque = deques[activeDeque]->concat(deques[otherName].get());
            std::string newName = activeDeque + "_CONCAT";
            deques[newName] = std::move(newDeque);
            out << "CONCATENATED " << activeDeque << " WITH " << otherName << " INTO " << newName << "\n";
            std::cout << "[SEGDEQMENU] CONCAT EXECUTED: " << activeDeque << " CONCAT " << otherName << std::endl;
        }
        else if (cmd == "WHERE")
        {
            std::string op, value;
            iss >> op >> value;
            auto &dq = deques[activeDeque];
            void *parsed = parseValue(value, dq->getType());
            auto newDeque = dq->where([this, op, parsed](void *item)
                                      { return this->parsePredicate(op, parsed, item); });
            std::string newName = activeDeque + "_FILTERED";
            deques[newName] = std::move(newDeque);
            if (dynamic_cast<IntType *>(dq->getType()))
                delete static_cast<int *>(parsed);
            else if (dynamic_cast<DoubleType *>(dq->getType()))
                delete static_cast<double *>(parsed);
            else if (dynamic_cast<StringType *>(dq->getType()))
                delete static_cast<std::string *>(parsed);
            else if (dynamic_cast<ComplexType *>(dq->getType()))
                delete static_cast<Complex *>(parsed);
            else if (dynamic_cast<FunctionType *>(dq->getType()))
                delete static_cast<std::function<int(int)> *>(parsed);
            else if (dynamic_cast<PersonType *>(dq->getType()))
                delete static_cast<std::string *>(parsed);
            out << "FILTER APPLIED. NEW DEQUE: " << newName << "\n";
            std::cout << "[SEGDEQMENU] WHERE EXECUTED WITH OPERATION: " << op << " VALUE: " << value << std::endl;
        }
        else if (cmd == "MAP")
        {
            std::string operation;
            iss >> operation;
            auto newDeque = deques[activeDeque]->map(operation);
            std::string newName = activeDeque + "_MAPPED";
            deques[newName] = std::move(newDeque);
            out << "MAPPED WITH OPERATION: " << operation << ". NEW DEQUE: " << newName << "\n";
            std::cout << "[SEGDEQMENU] MAP EXECUTED WITH OPERATION: " << operation << std::endl;
        }
        else if (cmd == "MERGE")
        {
            std::string otherName;
            iss >> otherName;
            if (deques.find(otherName) == deques.end())
                throw std::runtime_error("DEQUE NOT FOUND: " + otherName);
            auto newDeque = deques[activeDeque]->merge(deques[otherName].get());
            std::string newName = activeDeque + "_MERGED";
            deques[newName] = std::move(newDeque);
            out << "MERGED " << activeDeque << " WITH " << otherName << " INTO " << newName << "\n";
            std::cout << "[SEGDEQMENU] MERGE EXECUTED WITH DEQUE: " << otherName << std::endl;
        }
        else
        {
            throw std::runtime_error("UNKNOWN COMMAND: " + cmd);
        }
    }
    catch (const std::exception &e)
    {
        out << "ERROR: " << e.what() << "\n";
        std::cerr << "[SEGDEQMENU] ERROR WHILE PROCESSING COMMAND: " << e.what() << std::endl;
    }
}
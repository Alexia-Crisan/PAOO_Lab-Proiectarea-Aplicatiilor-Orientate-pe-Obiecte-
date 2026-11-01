#pragma once
#include <iostream>

// Item 10: Have assignment operators return a reference to *this.
// Item 11: Handle assignment to self in operator=.

class Widget
{
private:
    int *data;
    int priority;

public:
    explicit Widget(int val = 0, int prio = 0)
        : data(new int(val)), priority(prio) {}

    ~Widget() { delete data; }

    Widget(const Widget &rhs)
        : data(new int(*rhs.data)), priority(rhs.priority) {}

    Widget &operator=(const Widget &rhs)
    {
        if (this == &rhs)
            return *this; // Item 11: Self-assignment guard

        int *pOld = data;
        data = new int(*rhs.data);
        delete pOld;

        priority = rhs.priority;

        return *this; // Item 10: Return *this
    }

    Widget &operator+=(const Widget &rhs)
    {
        priority += rhs.priority;
        return *this;
    }

    int getValue() const { return data ? *data : 0; }

    void print(const std::string &name = "") const
    {
        std::cout << "[Widget] " << name << " -> Value: " << (data ? *data : 0)
                  << ", Priority: " << priority << "\n";
    }
};

// Item 12: Copy all parts of an object.

class Base
{
private:
    int baseData;

public:
    explicit Base(int v = 0) : baseData(v) {}
    Base(const Base &rhs) : baseData(rhs.baseData) {}

    Base &operator=(const Base &rhs)
    {
        baseData = rhs.baseData;
        return *this;
    }

    int getBaseData() const { return baseData; }
};

class Derived : public Base
{
private:
    int derivedData;

public:
    Derived(int b, int d) : Base(b), derivedData(d) {}

    Derived(const Derived &rhs)
        : Base(rhs), derivedData(rhs.derivedData) {}

    Derived &operator=(const Derived &rhs)
    {
        Base::operator=(rhs);
        derivedData = rhs.derivedData;
        return *this;
    }

    int getderivedData() const { return derivedData; }

    void print() const
    {
        std::cout << "[Item 12] Derived -> BaseData: " << getBaseData()
                  << ", DerivedData: " << derivedData << "\n";
    }
};
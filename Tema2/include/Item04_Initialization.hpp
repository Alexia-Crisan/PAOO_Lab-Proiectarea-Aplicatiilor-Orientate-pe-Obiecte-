#pragma once
#include <iostream>
#include <string>

// ===========================================================
// Item 4: Make sure that objects are initialized before they're used.
// ===========================================================

class Noisy
{
    std::string text;

public:
    Noisy() : text("(gol)") { std::cout << "      Noisy: constructor implicit\n"; }
    explicit Noisy(const std::string &t) : text(t) { std::cout << "      Noisy: constructor cu valoare\n"; }
    Noisy(const Noisy &other) : text(other.text) { std::cout << "      Noisy: copy constructor\n"; }

    Noisy &operator=(const Noisy &rhs)
    {
        text = rhs.text;
        std::cout << "      Noisy: operator= (atribuire)\n";
        return *this;
    }
};

// STIL GRESIT: atribuire in corpul constructorului
class UninitializedExample
{
    Noisy name;
    int value;

public:
    UninitializedExample(const Noisy &n, int v)
    {
        name = n;
        value = v;
    }
};

// STIL CORECT: lista de initializare. Fiecare membru e construit direct cu valoarea finala
class ProperlyInitializedExample
{
    Noisy name;
    int value;

public:
    ProperlyInitializedExample(const Noisy &n, int v)
        : name(n), value(v) {}

    int getValue() const { return value; }
};

#pragma once
#include <iostream>
#include <string>

// Item 4: Make sure that objects are initialized before they're used.

class UninitializedExample
{
    std::string name;
    int value;

public:
    UninitializedExample(const std::string &n, int v)
    {
        name = n;
        value = v;
    }
};

class ProperlyInitializedExample
{
    std::string name;
    int value;

public:
    ProperlyInitializedExample(const std::string &n, int v)
        : name(n), value(v) {}

    void print() const
    {
        std::cout << "[Item 4] Name: " << name << ", Value: " << value << "\n";
    }
};

// Solving non-local static initialization order fiasco across translation units:
// Wrap non-local static objects inside functions (Meyers' Singleton pattern).
class FileSystem
{
public:
    void log() const { std::cout << "[Item 4] FileSystem accessed safely.\n"; }
};

inline FileSystem &tfs()
{
    static FileSystem fs;
    return fs;
}
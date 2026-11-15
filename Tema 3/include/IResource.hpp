#pragma once
#include <cstddef>
#include <iostream>
#include <string>

namespace resources
{

    inline void info(const std::string &msg)
    {
        std::cout << "   [resources] " << msg << "\n";
    }

    inline void printArray(const int *data, std::size_t size)
    {
        if (data == nullptr || size == 0)
        {
            std::cout << "(gol)";
            return;
        }
        std::cout << "[";
        for (std::size_t i = 0; i < size; ++i)
        {
            std::cout << data[i] << (i + 1 < size ? " " : "");
        }
        std::cout << "]";
    }

    class IResource
    {
    public:
        virtual ~IResource() = default;

        virtual void use() const = 0;
        virtual std::string name() const = 0;
        virtual std::string copyPolicy() const = 0;

        virtual void describe() const
        {
            std::cout << "   " << name() << " [politica de copiere: " << copyPolicy() << "]\n";
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const IResource &r)
    {
        return os << r.name();
    }

}
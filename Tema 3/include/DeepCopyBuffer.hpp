#pragma once
#include <stdexcept>
#include "IResource.hpp"

namespace resources
{

    // Item 14, COPIE ADANCA. Fiecare copie are propriul array;
    // modificarea unei copii nu o afecteaza pe cealalta.
    class DeepCopyBuffer : public IResource
    {
    private:
        int *data;
        std::size_t size;

    public:
        explicit DeepCopyBuffer(std::size_t n, int fill = 0)
            : data(new int[n]), size(n)
        {
            for (std::size_t i = 0; i < size; ++i)
            {
                data[i] = fill;
            }
            std::cout << "   [DeepCopyBuffer] constructor: " << size << " elemente\n";
        }

        ~DeepCopyBuffer() override
        {
            std::cout << "   [DeepCopyBuffer] destructor: delete[] (" << size << " elemente)\n";
            delete[] data;
        }

        // Copy constructor
        DeepCopyBuffer(const DeepCopyBuffer &other)
            : data(new int[other.size]), size(other.size)
        {
            for (std::size_t i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
            std::cout << "   [DeepCopyBuffer] copy constructor\n";
        }

        // Copy assignment
        DeepCopyBuffer &operator=(const DeepCopyBuffer &rhs)
        {
            std::cout << "   [DeepCopyBuffer] copy assignment\n";
            if (this == &rhs)
            {
                std::cout << "   [DeepCopyBuffer] autoasignare - nu fac nimic\n";
                return *this;
            }

            int *newData = new int[rhs.size];
            for (std::size_t i = 0; i < rhs.size; ++i)
            {
                newData[i] = rhs.data[i];
            }
            delete[] data;
            data = newData;
            size = rhs.size;

            return *this;
        }

        // Move constructor
        DeepCopyBuffer(DeepCopyBuffer &&other) noexcept
            : data(other.data), size(other.size)
        {
            other.data = nullptr;
            other.size = 0;
            std::cout << "   [DeepCopyBuffer] move constructor\n";
        }

        // Move assignment
        DeepCopyBuffer &operator=(DeepCopyBuffer &&rhs) noexcept
        {
            std::cout << "   [DeepCopyBuffer] move assignment\n";
            if (this != &rhs)
            {
                delete[] data;
                data = rhs.data;
                size = rhs.size;
                rhs.data = nullptr;
                rhs.size = 0;
            }
            return *this;
        }

        // operator[]: acces la elemente
        int &operator[](std::size_t i)
        {
            if (i >= size)
            {
                throw std::out_of_range("index in afara limitelor");
            }
            return data[i];
        }

        const int &operator[](std::size_t i) const
        {
            if (i >= size)
            {
                throw std::out_of_range("index in afara limitelor");
            }
            return data[i];
        }

        void use() const override
        {
            std::cout << "   [DeepCopyBuffer] contine: ";
            printArray(data, size);
            std::cout << "\n";
        }

        std::string name() const override { return "DeepCopyBuffer"; }
        std::string copyPolicy() const override { return "copie adanca"; }
    };

}
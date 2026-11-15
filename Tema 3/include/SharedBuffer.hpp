#pragma once
#include <memory>
#include <stdexcept>
#include "IResource.hpp"

namespace resources
{

    // Item 14, NUMARARE DE REFERINTE (reference counting).
    // Toate copiile PARTAJEAZA acelasi array. Memoria se elibereaza
    // abia cand dispare ULTIMUL proprietar. Se ocupa std::shared_ptr.
    class SharedBuffer : public IResource
    {
    private:
        std::shared_ptr<int[]> data;
        std::size_t size;

    public:
        explicit SharedBuffer(std::size_t n, int fill = 0)
            : data(new int[n]), size(n)
        {
            for (std::size_t i = 0; i < size; ++i)
            {
                data[i] = fill;
            }
            std::cout << "   [SharedBuffer] constructor: " << size << " elemente\n";
        }

        ~SharedBuffer() override
        {
            std::cout << "   [SharedBuffer] destructor (use_count inainte = "
                      << data.use_count() << ")\n";
        }

        // Copy constructor
        SharedBuffer(const SharedBuffer &other)
            : data(other.data), size(other.size)
        {
            std::cout << "   [SharedBuffer] copy constructor\n";
        }

        // Copy assignment
        SharedBuffer &operator=(const SharedBuffer &rhs)
        {
            std::cout << "   [SharedBuffer] copy assignment\n";
            data = rhs.data;
            size = rhs.size;
            return *this;
        }

        // Move constructor
        SharedBuffer(SharedBuffer &&other) noexcept
            : data(std::move(other.data)), size(other.size)
        {
            other.size = 0;
            std::cout << "   [SharedBuffer] move constructor\n";
        }

        // Move assignment
        SharedBuffer &operator=(SharedBuffer &&rhs) noexcept
        {
            std::cout << "   [SharedBuffer] move assignment\n";
            if (this != &rhs)
            {
                data = std::move(rhs.data);
                size = rhs.size;
                rhs.size = 0;
            }
            return *this;
        }

        int &operator[](std::size_t i)
        {
            if (i >= size)
            {
                throw std::out_of_range("index in afara limitelor");
            }
            return data[i];
        }

        void use() const override
        {
            std::cout << "   [SharedBuffer] contine: ";
            printArray(data.get(), size);
            std::cout << "\n";
        }

        std::string name() const override { return "SharedBuffer"; }
        std::string copyPolicy() const override { return "partajare (reference counting)"; }

        // Suprascriem functia virtuala describe()
        void describe() const override
        {
            IResource::describe();
            std::cout << "      use_count = " << data.use_count() << "\n";
        }

        long useCount() const { return data.use_count(); }
    };

}